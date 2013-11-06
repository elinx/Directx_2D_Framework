#include "DirectSound.h"

CDirectSound::CDirectSound()
	:
	m_ipDirectSound(NULL),
	m_pDSPrimaryBuffer(NULL),
	m_pDSSecondaryBuffer1(NULL)
{
}
CDirectSound::~CDirectSound()
{
	m_pDSSecondaryBuffer1->Stop();
	if (m_ipDirectSound != NULL)
	{
		m_ipDirectSound->Release();
		m_ipDirectSound = NULL;
	}	
	// an error happens below
// 	if (m_pDSSecondaryBuffer1 != NULL)
// 	{
// 		m_pDSSecondaryBuffer1->Release();
// 		m_pDSSecondaryBuffer1 = NULL;
// 	}
// 	if (m_pDSPrimaryBuffer != NULL)
// 	{
// 		m_pDSPrimaryBuffer->Release();
// 		m_pDSPrimaryBuffer = NULL;
// 	}

}
bool CDirectSound::InitDirectSound(HWND hwnd)
{
	// create direct sound main interface
	if(FAILED(DirectSoundCreate8(NULL, &m_ipDirectSound, NULL)))
	{
		MessageBox(hwnd,
			L"DirectSoundCreate8 failed!",
			L"ERROR",
			MB_OK);
		return false;
	}
	// set the cooperative level with other program
	if (FAILED(m_ipDirectSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY)))
	{
		MessageBox(hwnd,
			L"SetCooperativeLevel failed!",
			L"ERROR",
			MB_OK);
		return false;
	}
	// create main audio buffer
	DSBUFFERDESC	dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	dsbd.dwBufferBytes = 0;
	dsbd.lpwfxFormat = NULL;
	if (FAILED(m_ipDirectSound->CreateSoundBuffer(&dsbd, &m_pDSPrimaryBuffer, NULL)))
	{
		MessageBox(hwnd,
			L"CreateSoundBuffer PrimaryBuffer failed!",
			L"ERROR",
			MB_OK);
		return false;
	}

	// set re-play format
	WAVEFORMATEX	wfex;
	ZeroMemory(&wfex, sizeof(WAVEFORMATEX));
	wfex.wFormatTag = WAVE_FORMAT_PCM;
	wfex.nChannels  = 2;			// single channel
	wfex.nSamplesPerSec = 24000;	//22050hz
	wfex.wBitsPerSample = 16;		// 16bits
	wfex.nBlockAlign = (wfex.wBitsPerSample / 8) * wfex.nChannels;
	wfex.nAvgBytesPerSec = wfex.nSamplesPerSec * wfex.nBlockAlign;
	wfex.cbSize = 0;
	if (FAILED(m_pDSPrimaryBuffer->SetFormat(&wfex)))
	{
		MessageBox(hwnd,
			L"Set PrimaryBuffer Format failed!",
			L"ERROR",
			MB_OK);
		return false;
	}
	return true;
}

bool CDirectSound::LoadWaveFile(std::wstring filePath, unsigned char** waveData, unsigned long* WaveDataLen)
{
	FILE* fp;

	// open the file in binary read only mode
	int r = _wfopen_s(&fp, filePath.c_str(), L"rb");
	if (r)// zero if successful
	{
		return false;
	}
	// read the header of the wave file
	int count = fread(&m_sWaveHeader, sizeof(WaveHeaderType), 1, fp);
	if(count != 1)
	{
		return false;
	}
	// Check that the chunk ID is the RIFF format.
	if((m_sWaveHeader.chunkId[0] != 'R') || (m_sWaveHeader.chunkId[1] != 'I') || 
		(m_sWaveHeader.chunkId[2] != 'F') || (m_sWaveHeader.chunkId[3] != 'F'))
	{
		return false;
	}

	// Check that the file format is the WAVE format.
	if((m_sWaveHeader.format[0] != 'W') || (m_sWaveHeader.format[1] != 'A') ||
		(m_sWaveHeader.format[2] != 'V') || (m_sWaveHeader.format[3] != 'E'))
	{
		return false;
	}

	// Check that the sub chunk ID is the fmt format.
	if((m_sWaveHeader.subChunkId[0] != 'f') || (m_sWaveHeader.subChunkId[1] != 'm') ||
		(m_sWaveHeader.subChunkId[2] != 't') || (m_sWaveHeader.subChunkId[3] != ' '))
	{
		return false;
	}

	// Check that the audio format is WAVE_FORMAT_PCM.
	if(m_sWaveHeader.audioFormat != WAVE_FORMAT_PCM)
	{
		return false;
	}

	// Check that the wave file was recorded in stereo format.
	if(m_sWaveHeader.numChannels != 2)
	{
		return false;
	}

	// Check that the wave file was recorded at a sample rate of 44.1 KHz.
	if(m_sWaveHeader.sampleRate != 24000)
	{
		return false;
	}

	// Ensure that the wave file was recorded in 16 bit format.
	if(m_sWaveHeader.bitsPerSample != 16)
	{
		return false;
	}

	// Check for the data chunk header.
	if((m_sWaveHeader.dataChunkId[0] != 'd') || (m_sWaveHeader.dataChunkId[1] != 'a') ||
		(m_sWaveHeader.dataChunkId[2] != 't') || (m_sWaveHeader.dataChunkId[3] != 'a'))
	{
		return false;
	}

	// Move to the beginning of the wave data which starts at the end of the data chunk header.
	fseek(fp, sizeof(WaveHeaderType), SEEK_SET);

	*WaveDataLen = m_sWaveHeader.dataSize;
	// Create a buffer to hold the wave file data.
	*waveData = new unsigned char[m_sWaveHeader.dataSize];
	if(!waveData)
	{
		return false;
	}

	// Read in the wave file data into the newly created buffer.
	count = fread(*waveData, 1, m_sWaveHeader.dataSize, fp);
	if(count != m_sWaveHeader.dataSize)
	{
		return false;
	}

	// Close the file once done reading.
	int error = fclose(fp);
	if(error != 0)
	{
		return false;
	}

	return true;
}

bool CDirectSound::CreateSecdaryBuffer(unsigned long WaveDataLen)
{
	LPDIRECTSOUNDBUFFER tempBuffer;

	// Set the wave format of secondary buffer that this wave file will be loaded onto.
	WAVEFORMATEX	wfex;
	ZeroMemory(&wfex, sizeof(WAVEFORMATEX));
	wfex.wFormatTag = WAVE_FORMAT_PCM;
	wfex.nChannels  = 2;			// single channel
	wfex.nSamplesPerSec = 24000;	//24000hz
	wfex.wBitsPerSample = 16;		// 16bits
	wfex.nBlockAlign = (wfex.wBitsPerSample / 8) * wfex.nChannels;
	wfex.nAvgBytesPerSec = wfex.nSamplesPerSec * wfex.nBlockAlign;

	// create main audio buffer
	DSBUFFERDESC	dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_CTRLVOLUME;
	dsbd.dwBufferBytes = WaveDataLen;
	dsbd.lpwfxFormat = &wfex;

	if (FAILED(m_ipDirectSound->CreateSoundBuffer(&dsbd, &tempBuffer, NULL)))
	{
		return false;
	}
	// Test the buffer format against the direct sound 8 interface and create the secondary buffer.
	if (FAILED(tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&m_pDSSecondaryBuffer1)))
	{
		tempBuffer->Release();
		tempBuffer = NULL;
		return false;
	}

	tempBuffer->Release();
	tempBuffer = NULL;
	return true;
}
bool CDirectSound::LoadWaveDataToSecondaryBuffer(unsigned char* waveData, unsigned long WaveDataLen)
{
	unsigned long  bufferSize;
	unsigned char* bufferPtr;

	// Lock the secondary buffer to write wave data into it.
	int result = m_pDSSecondaryBuffer1->Lock(0, WaveDataLen, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
	if(FAILED(result))
	{
		return false;
	}

	// Copy the wave data into the buffer.
	memcpy(bufferPtr, waveData, WaveDataLen);

	// Unlock the secondary buffer after the data has been written to it.
	result = m_pDSSecondaryBuffer1->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
	if(FAILED(result))
	{
		return false;
	}
	return true;
}
bool CDirectSound::LoadWaveData(std::wstring filePath)
{
	unsigned char* tempWaveData = NULL;
	unsigned long  WaveDataLen ;

	this->LoadWaveFile(filePath, &tempWaveData, &WaveDataLen);// get the wave audio data and data length
	CreateSecdaryBuffer(WaveDataLen);
	LoadWaveDataToSecondaryBuffer(tempWaveData, WaveDataLen);

	delete tempWaveData;

	return true;
}
void CDirectSound::SetVolume()
{
	m_pDSSecondaryBuffer1->SetVolume(DSBVOLUME_MAX);
}
void CDirectSound::StartToPlay()
{
	SetVolume();
	m_pDSSecondaryBuffer1->Play(0, 0, 0);
}
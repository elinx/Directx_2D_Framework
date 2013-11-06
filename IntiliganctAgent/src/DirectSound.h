#pragma once

#include <dsound.h>
#include <string>
#include <iostream>

#pragma comment(lib, "DSound.lib")

struct WaveHeaderType
{
	char chunkId[4];
	unsigned long chunkSize;
	char format[4];
	char subChunkId[4];
	unsigned long subChunkSize;
	unsigned short audioFormat;
	unsigned short numChannels;
	unsigned long sampleRate;
	unsigned long bytesPerSecond;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
	char dataChunkId[4];
	unsigned long dataSize;
};

class CDirectSound
{
public:
	CDirectSound();
	~CDirectSound();

	bool InitDirectSound(HWND hwnd);
	bool LoadWaveData(std::wstring filePath);
	void SetVolume();
	void StartToPlay();

private:
	// read the wave file; return the data and the length of the data
	bool LoadWaveFile(std::wstring filePath, 
			unsigned char** waveData, unsigned long* WaveDataLen);
	bool CreateSecdaryBuffer(unsigned long WaveDataLen);	
	bool LoadWaveDataToSecondaryBuffer(unsigned char* waveData, unsigned long WaveDataLen);
private:
	LPDIRECTSOUND8			m_ipDirectSound;
	LPDIRECTSOUNDBUFFER		m_pDSPrimaryBuffer;
	LPDIRECTSOUNDBUFFER8	m_pDSSecondaryBuffer1;

	WaveHeaderType			m_sWaveHeader;
};
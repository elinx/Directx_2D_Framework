#pragma	once

#include <Windows.h>

class CFrameChecker
{
public:
	CFrameChecker()
		:
	m_countsPerSecond(0.0f),
	m_counterStart(0),
	m_frameCount(0),
	m_fps(0),
	m_frameTimeOld(0),
	m_frameTime(0.0f)
	{
		
	}
	~CFrameChecker() {}
	void	StartTimer()
	{
		LARGE_INTEGER frequencyCount;
		QueryPerformanceFrequency(&frequencyCount);	// Note here is frequency not counter.

		m_countsPerSecond = double(frequencyCount.QuadPart);	// save the counter.

		QueryPerformanceCounter(&frequencyCount);
		m_counterStart = frequencyCount.QuadPart;	// start timer, record the start counter.
	}
	void	ResetTimer()
	{
		CFrameChecker();
	}
	/*
		Get the time in seconds since the StartTimer()
		function was last called, which is the value 
		the GetTime() function returns.
	*/
	double	GetTime()
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		return (currentTime.QuadPart-m_counterStart)/ m_countsPerSecond;
	}
	double GetFramePerSecend()
	{
		return 1.0f / GetTime();
	}
	double	GetFrametime()
	{
		LARGE_INTEGER currentTime;
		__int64 tickCount;
		QueryPerformanceCounter(&currentTime);

		tickCount = currentTime.QuadPart-m_frameTimeOld;
		m_frameTimeOld = currentTime.QuadPart;

		if(tickCount < 0.0f)
			tickCount = 0;

		return float(tickCount) / m_countsPerSecond;
	}
private:
	double	m_countsPerSecond;
	__int64 m_counterStart;
	int		m_frameCount;
	int		m_fps;
	__int64 m_frameTimeOld;
	double	m_frameTime;
};
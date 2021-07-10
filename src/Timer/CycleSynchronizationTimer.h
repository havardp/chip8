#pragma once
#include <thread>
#include <chrono>

struct CycleSynchronizationTimer
{
private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::microseconds actual_time_per_cycle;
public:
	CycleSynchronizationTimer(int wanted_cycles_per_second);
	~CycleSynchronizationTimer();
};

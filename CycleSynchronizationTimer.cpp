#include "CycleSynchronizationTimer.h"
constexpr auto MICROSECONDS_PER_SECONDS = 1000000;

CycleSynchronizationTimer::CycleSynchronizationTimer(int wanted_cycles_per_second)
{
	start = std::chrono::steady_clock::now();
	actual_time_per_cycle = std::chrono::microseconds(MICROSECONDS_PER_SECONDS / wanted_cycles_per_second);
}

CycleSynchronizationTimer::~CycleSynchronizationTimer()
{
	end = std::chrono::steady_clock::now();
	auto duration_of_cycle_in_microseconds = std::chrono::duration_cast<std::chrono::microseconds>((end - start));

	if (duration_of_cycle_in_microseconds < actual_time_per_cycle)
	{
		std::this_thread::sleep_for(actual_time_per_cycle - duration_of_cycle_in_microseconds);
	}
}
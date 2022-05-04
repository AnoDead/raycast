#pragma once
 
#include <chrono> 

using namespace std::chrono;

class Timer
{
private:

	using clock_t = high_resolution_clock;
	
	time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}
	
	void reset()
	{
		m_beg = clock_t::now();
	}
	
	double elapsed() const
	{ 
		return duration_cast<milliseconds>(clock_t::now() - m_beg).count();
	}
};

double timeStamp(){
    static Timer timer;
    double time = timer.elapsed();
    timer.reset();
    return time;
}

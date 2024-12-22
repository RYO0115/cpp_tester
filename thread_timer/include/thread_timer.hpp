
#ifndef THREAD_TIMER_HPP
#define THREAD_TIMER_HPP
#include <stdio.h>
#include <chrono>
#include <thread>

class ThreadTimer
{
private:
    std::chrono::system_clock::time_point _timer_start, _rap_start, _now;
    int _sleep_nano_time;


public:
    ThreadTimer(int hz=1){
        
        SetLoopRate(hz);
    }
    ~ThreadTimer(){}

    void SetLoopRate(int hz)
    {
        _sleep_nano_time = 1000 * 1000 * 1000 / hz;
        std::cout<<_sleep_nano_time<<std::endl;
    }

    void Start()
    {
        _timer_start = std::chrono::system_clock::now();
        _rap_start = std::chrono::system_clock::now();
    }

    void Reset()
    {
        _rap_start = std::chrono::system_clock::now();
    }

    int GetMilliSecRapTime()
    {
        _now = std::chrono::system_clock::now();
        return((int)std::chrono::duration_cast<std::chrono::milliseconds>(_now - _rap_start).count());
    }

    int GetMicroSecRapTime()
    {
        _now = std::chrono::system_clock::now();
        return((int)std::chrono::duration_cast<std::chrono::microseconds>(_now - _rap_start).count());
    }

    int GetNanoSecRapTime()
    {
        _now = std::chrono::system_clock::now();
        return((int)std::chrono::duration_cast<std::chrono::nanoseconds>(_now - _rap_start).count());
    }

    int GetMilliSecTotalTime()
    {
        _now = std::chrono::system_clock::now();
        return((int)std::chrono::duration_cast<std::chrono::milliseconds>(_now - _timer_start).count());
    }

    int GetMicroSecTotalTime()
    {
        _now = std::chrono::system_clock::now();
        return((int)std::chrono::duration_cast<std::chrono::microseconds>(_now - _timer_start).count());
    }

    int GetNanoSecTotalTime()
    {
        _now = std::chrono::system_clock::now();
        return((int)std::chrono::duration_cast<std::chrono::nanoseconds>( _now - _timer_start).count());
    }

    void Sleep()
    {
        int time = GetNanoSecRapTime();
        int diff_time = _sleep_nano_time - time;

        if(diff_time > 0)
        {
            //usleep(diff_time);
            std::this_thread::sleep_for(std::chrono::nanoseconds(diff_time));
        }
        _rap_start = std::chrono::system_clock::now();
    }
};

#endif /* THREAD_TIMER_HPP */
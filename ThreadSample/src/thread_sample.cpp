
#include "thread_sample.hpp"


void SampleThread::_Main(void)
{
    const int sleep_msec = 100;
    while(!_stop_loop)
    {
        _UpdateData();
        std::this_thread::sleep_for(std::chrono::microseconds(sleep_msec));
    }
}

void SampleThread::_UpdateData(void)
{
    std::lock_guard<std::mutex> lock(_main_mutex);
    _counter++;
    _value += _counter;

    if(_counter > 100) _counter = 0;
}

void SampleThread::_StopLoop(void)
{
    _stop_loop = true;
}

void SampleThread::GenerateThread(void)
{
    _main_thread = std::thread(&SampleThread::_Main, this);
}

void SampleThread::CloseThread(void)
{
    _StopLoop();
    _main_thread.join();
}

int  SampleThread::GetCounter(void)
{
    return(_counter);
}

int SampleThread::GetValue(void)
{
    return(_value);
}

void SampleThread::ResetValue(const int &value)
{
    std::lock_guard<std::mutex> lock(_main_mutex);
    _value = value;
}
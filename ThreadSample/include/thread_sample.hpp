#include <thread>
#include <chrono>
#include <mutex>

#include <functional>
#include <iostream>

class SampleThread
{
private:
    std::thread _main_thread;
    std::mutex _main_mutex;

    int _counter;
    int _value;
    bool _stop_loop;

    void _StopLoop(void);
    void _Main(void);
    void _UpdateData(void);

public:
    SampleThread() : _counter(0), _value(0), _stop_loop(false)
    {

    }
    ~SampleThread() {}

    void GenerateThread(void);
    void CloseThread(void);


    int GetCounter(void);
    int GetValue(void);
    void ResetValue(const int &value);


};



#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include <chrono>

#include "thread_timer.hpp"

int main(void)
{
    std::chrono::system_clock::time_point start, end;
    /*
    int second;
    int microsecond;
    int nanosecond;

    start = std::chrono::system_clock::now();

    usleep(500100);

    end = std::chrono::system_clock::now();

    int time = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

    std::cout<<time<<std::endl;
    */

   ThreadTimer timer(100);

   timer.Start();

    start = std::chrono::system_clock::now();
    for(int i=0; i<100; i++)
    {
        timer.Sleep();
    }
    end = std::chrono::system_clock::now();
    int time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    std::cout<<time<<std::endl;

    return(0);
}
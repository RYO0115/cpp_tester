#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx_;
uint32_t count_;
uint32_t count0_;
bool flag_;

bool thread1_finish_, thread2_finish_;


#define COUNTING_TIME 50
#define PROCESS_LIMIT_TIME 10000 //[msec]
#define READING_RES 10

void add_count()
{
	//std::cout<<"Count:"<<count_<<std::endl;
	std::lock_guard<std::mutex> lock(mtx_);
	if(count_ - count0_ != 0)
		printf("\nCount:%d -> %d\n", count0_, count_);

	count_++;
	//if(count_%READING_RES == 0)
	//{
	//	flag_ = true;
	//}
}

void Thread1()
{
	int hz = 1000;
	if(hz > 1000 || hz < 1) return;

	double process_time = 1000 / (double)hz;

	std::chrono::system_clock::time_point start, now_0, now;
	start = std::chrono::system_clock::now();
	now_0 = std::chrono::system_clock::now();
	now = std::chrono::system_clock::now();
	double now_process_time = std::chrono::duration_cast<std::chrono::milliseconds>(now-now_0).count();// to milliseconds
	double total_process_time = 0;
	//for(int i=0; i<COUNTING_TIME; i++)
	while(total_process_time < PROCESS_LIMIT_TIME)
	{
		while(now_process_time < process_time)
		{
			now = std::chrono::system_clock::now();
			now_process_time = std::chrono::duration_cast<std::chrono::milliseconds>(now-now_0).count();// to milliseconds

		}

		add_count();
		count0_ = count_;
		now_0 = std::chrono::system_clock::now();
		now = std::chrono::system_clock::now();
		total_process_time = std::chrono::duration_cast<std::chrono::milliseconds>(now-start).count();// to milliseconds
		//std::cout<<std::endl<<"Now process_time::"<<now_process_time<<"Total::"<<total_process_time<<std::endl;
		printf("\nThread1::Now process_time:%.2lf[ms], Total time:: %.2lf[ms]\n", now_process_time, total_process_time);
		now_process_time = std::chrono::duration_cast<std::chrono::milliseconds>(now-now_0).count();// to milliseconds
	}


	thread1_finish_ = true;
	std::cout<<"Thread1 Finish"<<std::endl;
}

bool check_count()
{
	
	std::lock_guard<std::mutex> lock(mtx_);
	std::cout<<flag_;
	if(flag_)
	{
		std::cout<<"\tCheck Count:"<<count_<<std::endl;
		flag_ = false;
	}
	else{
	}
	std::cout<<std::endl;
	//return(flag);
}

void Thread2( )
{
	
	int hz = 100;
	if(hz > 1000 || hz < 1) return;

	double process_time = 1000 / (double)hz;

	std::chrono::system_clock::time_point start, now_0, now;
	start = std::chrono::system_clock::now();
	now_0 = std::chrono::system_clock::now();
	now = std::chrono::system_clock::now();
	double now_process_time = std::chrono::duration_cast<std::chrono::milliseconds>(now-now_0).count();// to milliseconds
	double total_process_time = 0;
	while(total_process_time < PROCESS_LIMIT_TIME)
	//for(int i=0; i<10; i++)
	{
		while(now_process_time < process_time)
		{
			now = std::chrono::system_clock::now();
			now_process_time = std::chrono::duration_cast<std::chrono::milliseconds>(now-now_0).count();// to milliseconds

		}

		add_count();
		now_0 = std::chrono::system_clock::now();
		now = std::chrono::system_clock::now();
		total_process_time = std::chrono::duration_cast<std::chrono::milliseconds>(now-start).count();// to milliseconds
		//std::cout<<std::endl<<"Now process_time::"<<now_process_time<<"Total::"<<total_process_time<<std::endl;
		printf("\n >>>>>>> Thread2::Now process_time:%.2lf[ms], Total time:: %.2lf[ms]\n", now_process_time, total_process_time);
		now_process_time = std::chrono::duration_cast<std::chrono::milliseconds>(now-now_0).count();// to milliseconds
	}

	thread2_finish_ = true;
	std::cout<<"Thread2 Finish"<<std::endl;
}

#include <unistd.h>


void main1()
{

	
	count_ = 0;
	count0_ = 0;
	flag_ = false;
	thread1_finish_ = false;
	thread2_finish_ = false;

	std::thread th0(Thread1);
	std::thread th1(Thread2);

	th0.detach();
	th1.detach();


	while(!thread1_finish_ || !thread2_finish_)
	{
		//printf("\r(%d,%d)", thread1_finish_, thread2_finish_);
		//cout<<"Thread1:"<<thread1_finish_<<",  Thread2:"<<thread2_finish_<<endl;
	}
	
	//std::this_thread::sleep_for(std::chrono::seconds(10));
	std::cout<<"Count:"<<count_<<std::endl;
}




int main()
{
	main1();

	return(0);
}

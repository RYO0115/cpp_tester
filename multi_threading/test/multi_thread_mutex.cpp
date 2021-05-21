#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx_;
uint32_t count_;
bool flag_;

bool thread1_finish_, thread2_finish_;


#define COUNTING_TIME 1000000
#define READING_RES 10

void add_count()
{
	//std::cout<<"Count:"<<count_<<std::endl;
	std::lock_guard<std::mutex> lock(mtx_);
	count_++;
	if(count_%READING_RES == 0)
	{
		flag_ = true;
	}
}

void Thread1()
{
	for(int i=0; i<COUNTING_TIME; i++)
	{
		//mtx_.lock();
		add_count();


		//mtx_.unlock();
	}

	//thread1_finish_ = true;
}

bool check_count()
{
	
	std::lock_guard<std::mutex> lock(mtx_);
	std::cout<<flag_;
	if(flag_)
	{
		std::cout<<"\tCheck Count:"<<count_;
		flag_ = false;
	}
	else{
	}
	std::cout<<std::endl;
	//return(flag);
}

void Thread2()
{
	for(int i=0; i<10; i++)
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
		std::cout<<"\t"<<i<<":";
		check_count();
	}
	//thread2_finish_ = true;
}

#include <unistd.h>

int main()
{
	count_ = 0;
	flag_ = false;
	thread1_finish_ = false;
	thread2_finish_ = false;

	std::thread th0(Thread1);
	std::thread th1(Thread2);

	th0.detach();
	th1.detach();


	//while(!thread1_finish_ && !thread2_finish_){};
	
	std::this_thread::sleep_for(std::chrono::seconds(5));

	std::cout<<"Count:"<<count_<<std::endl;

	return(0);
}



#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 	// socket close
#include <arpa/inet.h> 	//inet_aton

#include <sys/ioctl.h>
#include <netdb.h>
#include <ifaddrs.h>

#include <chrono>
#include <thread>
#include <mutex>

#define BUFFER_SIZE  2048

#define POINT_BUFFER_LIMIT 100
#define SINGLE_POINT_DATA_SIZE 4

std::mutex mtx_;
bool data_set_flag_ = false;
uint8_t buf_[BUFFER_SIZE];

void ReceivePacket(struct sockaddr_in addr)
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	bind(sock, (struct sockaddr *)&addr, sizeof(addr));

	uint8_t tmp_buf[BUFFER_SIZE];
	uint8_t* p = tmp_buf;

	int point_num = 0;
	int point_limit = POINT_BUFFER_LIMIT;
	int point_size = SINGLE_POINT_DATA_SIZE;
	int point_id = 1;

    while(1)
    {
	    recv( sock, tmp_buf, sizeof(tmp_buf), 0);
		memcpy( p, tmp_buf, point_size);
		p += point_size;
		point_num++;

		if(point_num > point_limit)
		{
			printf("Receive Func:PointLimit\n");
			std::lock_guard<std::mutex> lock(mtx_);
			memset(buf_, 0 , sizeof(buf_));
			memcpy(buf_, tmp_buf, point_num * point_size);
	    	memset(tmp_buf, 0, sizeof(tmp_buf));
			p = tmp_buf;
			point_num = 0;
			data_set_flag_ = true;
		}

    }

    close(sock);

}

void PointPurseMain( int hz )
{
	std::chrono::system_clock::time_point start, now;
	start = std::chrono::system_clock::now();
	now = std::chrono::system_clock::now();
	double now_process_time = std::chrono::duration_cast<std::chrono::milliseconds>(now-start).count();// to milliseconds

	double process_target_time = 1000 / (double)hz;
	int process_time = 0;

	int point_num = POINT_BUFFER_LIMIT;
	int point_size = SINGLE_POINT_DATA_SIZE;
	int point_id;

	while(1)
	{

		std::lock_guard<std::mutex> lock(mtx_);
		if(data_set_flag_)
		{

			for(int i=0; i<point_num; i++)
			{
				point_id = i;
				printf("Main Thread:%d of points are set!! %d th point is (%d, %d, %d, %d)\n", 
						point_num,
						point_id,
						buf_[0 + point_size * point_id], 
						buf_[1 + point_size * point_id], 
						buf_[2 + point_size * point_id], 
						buf_[3 + point_size * point_id]);


			}
			data_set_flag_ = false;
		}

		now = std::chrono::system_clock::now();
		now_process_time = std::chrono::duration_cast<std::chrono::milliseconds>(now-start).count();
		process_time = (int)(process_target_time - now_process_time);

		if(process_time > 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(process_time));
			start = std::chrono::system_clock::now();
		}
		

	}

}

int main(void)
{
	//int sock;
	struct sockaddr_in addr;

	//sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = INADDR_ANY;


	std::thread th1(ReceivePacket,addr);
	std::thread th2(PointPurseMain, 20);
	th1.join();
	th2.join();

	//ReceivePacket(addr);
	//int id, x, y, z;
    return(0);

}


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

#define BUFFER_SIZE  2048

int main(void)
{
	int sock;
	struct sockaddr_in addr;

	//sock = socket(AF_INET, SOCK_DGRAM, 0);
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = INADDR_ANY;

	//bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	bind(sock, (struct sockaddr *)&addr, sizeof(addr));

	//char buf[BUFFER_SIZE];
	uint8_t tmp_buf[BUFFER_SIZE];
	uint8_t buf[BUFFER_SIZE];
	uint8_t* p = buf;

	int point_num = 0;
	int point_limit = 100;
	int point_size = 4;
	int point_id = 1;
	bool data_set_flag = false;


	//int id, x, y, z;

    while(1)
    {
	    memset(buf, 0, sizeof(tmp_buf));
	    recv( sock, tmp_buf, sizeof(tmp_buf), 0);
		//id = tmp_buf[0];
		//x = tmp_buf[1];
		//y = tmp_buf[2];
		//z = tmp_buf[3];
		//printf("(id,x,y,z)=(%d,%d,%d,%d)\n", id, x, y, z);
		memcpy( p, tmp_buf, point_size);
		p += point_size;
		point_num++;

		if(point_num > point_limit)
		{
			memset(buf, 0 , sizeof(buf));
			memcpy(buf, tmp_buf, point_num * point_size);
			data_set_flag = true;

			printf("%d of points are set!! %d th point is (%d, %d, %d, %d)\n", 
					point_num,
					point_id,
					buf[0 + point_size * point_id], 
					buf[1 + point_size * point_id], 
					buf[2 + point_size * point_id], 
					buf[3 + point_size * point_id]);

			p = tmp_buf;
			point_num = 0;
		}




	    //printf("sock1:%s\n",buf);

    }


    close(sock);

    return(0);

}
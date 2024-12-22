#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <map>
#include <string>

//#include "map_sample_class.hpp"

void Test1 (void){std::cout<<"Test1"<<std::endl;}
void Test2 (void){std::cout<<"Test2"<<std::endl;}

typedef struct{
    float x;
    float y;
    float z;
    float roll;
    float pitch;
    float yaw;
}SensorPosition;

void ShowSensorPosition(const SensorPosition& pos)
{
    std::cout<<"//------------------//"<<std::endl;
    std::cout<<"  x = "<<pos.x<<std::endl;
    std::cout<<"  y = "<<pos.y<<std::endl;
    std::cout<<"  z = "<<pos.z<<std::endl;
    std::cout<<"  roll = "<<pos.roll<<std::endl;
    std::cout<<"  pitch = "<<pos.pitch<<std::endl;
    std::cout<<"  yaw = "<<pos.yaw<<std::endl;
    std::cout<<"//------------------//"<<std::endl;
}



int main(void)
{
    //MapSample mp;

    //std::cout<<mp.PurseData(1,5)<<std::endl;

    std::map<int, std::string> test;

    test[0x01] = "100";
    test[0x02] = "200";
    std::cout<<test[0x01]<<":"<<test[0x02]<<std::endl;


    std::map<int, int> test2[3];

    test2[0][0x01] = 10;
    test2[1][0x02] = 20;
    test2[2][0x03] = 30;

    std::cout<<test2[0][0x01]<<std::endl;
    std::cout<<test2[1][0x02]<<std::endl;
    std::cout<<test2[2][0x03]<<std::endl;

    std::map<int, std::map<int, std::string> > test3;


    test3[1][1] = "sensor_1";
    test3[2][1] = "sensor_2_1";
    test3[2][0] = "sensor_2_0";
    test3[2][2] = "sensor_2_2";

    std::cout<<"Test3"<<std::endl;
    std::cout<<test[1][1]<<std::endl;
    std::cout<<test[2][0]<<std::endl;
    std::cout<<test[2][1]<<std::endl;
    std::cout<<test[2][2]<<std::endl;

    std::map<std::pair<int,int>, SensorPosition> test4;

    typedef enum
    {
        UNKNOWN     = -1,
        VERSION_1   = 1,
        VERSION_2   = 2
    } SystemVersion;

    typedef enum
    {
        RIGHT = 0,
        LEFT = 1,
        CENTER = 2,
        FAR_RIGHT = 3,
        FAR_LEFT = 4
    } SensorPositionId;


    SensorPosition sensor_pos_right, sensor_pos_left, sensor_pos_center;

    sensor_pos_right.x = 10;
    sensor_pos_right.y = -1;
    sensor_pos_right.z = 3;
    sensor_pos_right.roll = 0;
    sensor_pos_right.pitch = 10;
    sensor_pos_right.yaw = -45;

    sensor_pos_left.x = 10;
    sensor_pos_left.y = 1;
    sensor_pos_left.z = 3;
    sensor_pos_left.roll = 0;
    sensor_pos_left.pitch = 10;
    sensor_pos_left.yaw = 45;

    sensor_pos_center.x = 10;
    sensor_pos_center.y = 0;
    sensor_pos_center.z = 3;
    sensor_pos_center.roll = 0;
    sensor_pos_center.pitch = 5;
    sensor_pos_center.yaw = 0;

    test4[std::pair<int,int>(SystemVersion::VERSION_1, SensorPositionId::RIGHT)] = sensor_pos_right;
    test4[std::pair<int,int>(SystemVersion::VERSION_1, SensorPositionId::LEFT)] = sensor_pos_left;
    test4[std::pair<int,int>(SystemVersion::VERSION_2, SensorPositionId::CENTER)] = sensor_pos_center;


    std::cout<<"Test4"<<std::endl;

    std::cout<<"Version1 Right:"<<std::endl;
    ShowSensorPosition(test4[std::pair<int,int>(SystemVersion::VERSION_1, SensorPositionId::RIGHT)]);
    std::cout<<"Version1 Left:"<<std::endl;
    ShowSensorPosition(test4[std::pair<int,int>(SystemVersion::VERSION_1, SensorPositionId::LEFT)]);
    std::cout<<"Version2 Center:"<<std::endl;
    ShowSensorPosition(test4[std::pair<int,int>(SystemVersion::VERSION_2, SensorPositionId::CENTER)]);

    


    return(0);
}

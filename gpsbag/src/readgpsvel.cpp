#include <ros/ros.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Header.h>
#include <geometry_msgs/TwistStamped.h>
#include <string.h>
#include <sstream>

using namespace std;

class Subscribe
{
private:
    ros::NodeHandle nh;
    ros::Subscriber sub;

public:
    Subscribe()
    {
        sub = nh.subscribe("/vehicle/gps/vel",1000,&Subscribe::mycallback, this);

    }

    void mycallback(const geometry_msgs::TwistStamped& message)
    {
        float data[6]={0,0,0,0,0,0};
        float timestamp;
        data[0]=message.twist.linear.x;
        data[1]=message.twist.linear.y;
        data[2]=message.twist.linear.z;
        data[3]=message.twist.angular.x;
        data[4]=message.twist.angular.y;
        data[5]=message.twist.angular.z;
        timestamp = message.header.stamp.nsec;

        ofstream datawrite("/home/yidong/catkin_ws/src/gpsbag/src/trafficdata/gpsdata.txt",
                           ios::app);
        if(!datawrite.is_open())
        {
            cout<<"Cannot Open Text File."<<endl;
        }
        else
        {
            cout<<"Open Successfully!"<<endl;
            datawrite<<timestamp<<" "<<data[0]<<" "<<data[1]<<" "<<data[2]<<" "<<data[3]<<" "<<data[4]<<" "
                             <<data[5]<<endl;
        }

        datawrite.close();


    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "readgpsvel");

    Subscribe readgpsvel;

    ros::Rate loop_rate(10);
    ros::spin();

    return 0;
}

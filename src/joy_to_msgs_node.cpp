#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"

geometry_msgs::Twist twist;

void joyCallback(const sensor_msgs::Joy& msg)
{
    twist.linear.x = msg.axes[1];
    twist.angular.z = msg.axes[0];
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "joy_to_msgs");
    ros::NodeHandle n;

    ros::Subscriber joy_sub = n.subscribe("joy", 1000, joyCallback);

    ros::Publisher twist_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

    ros::Rate loop_rate(10);

    while(ros::ok())
    {
        //std::stringstream ss;

        twist_pub.publish(twist);

        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}

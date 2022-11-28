#include "odom_to_pose/odom_to_pose.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, " odom_to_pose");
    ros::NodeHandle odom_to_pose_nh;

    OdomToPose otp;

    ros::Rate loop_rate(1);
    while (ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
#include "elevation_mapping/odom_to_pose.hpp"

int main(int argc, char **argv)
{
    ros::init(argc, argv, " odom_to_pose");
    ros::NodeHandle odom_to_pose_nh;

    odomtopose value;
    OdomSubscriber sub;
    PosePublisher pub;

    ros::Rate r(1);
    while(ros::ok())
    {
        sub.odom_trans_set(value);
        pub.pose_trans_pub(value);

        r.sleep();
        ros::spinOnce();
    }
    return 0;
}
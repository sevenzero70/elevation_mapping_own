#ifndef _ODOM_POSE
#define _ODOM_POSE

#include <ros/ros.h>
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"

using namespace std;

// class OdomSubscriber
// {
// private:
//     // 订阅odom句柄
//     ros::NodeHandle odom_nh;
//     ros::Subscriber odom_sub;

// public:
//     geometry_msgs::PoseWithCovarianceStamped tmp_pose;

//     // 构造函数
//     OdomSubscriber();
//     // 回调函数
//     void odom_callback(const nav_msgs::Odometry::ConstPtr &odom);
//     // // 访问处理后的数据
//     void odom_trans_set(odomtopose &pose);
// };

// class PosePublisher
// {
// private:
//     geometry_msgs::PoseWithCovarianceStamped posemsg;
//     // 将订阅的部分odom作为pose发布
//     ros::NodeHandle pose_nh;
//     ros::Publisher pose_pub;

// public:
//     PosePublisher();
//     void pose_trans_pub(odomtopose &pose);
// };

class OdomToPose
{
private:
    ros::NodeHandle odom_sub_nh;
    ros::NodeHandle pose_pub_nh;
    ros::Subscriber odom_sub;
    ros::Publisher pose_pub;

public:
    geometry_msgs::PoseWithCovarianceStamped pose_cov;
    OdomToPose();
    void odom_sub_callback(const nav_msgs::Odometry::ConstPtr &odom);
    void pose_cov_pub();
};
#endif
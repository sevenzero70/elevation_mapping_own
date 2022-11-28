#include "odom_to_pose/odom_to_pose.h"

OdomToPose::OdomToPose()
{
    this->odom_sub = this->odom_sub_nh.subscribe("/rtabmap/odom", 1000, &OdomToPose::odom_sub_callback, this);
    this->pose_pub = this->pose_pub_nh.advertise<geometry_msgs::PoseWithCovarianceStamped>("pose", 1000);
};

void OdomToPose::odom_sub_callback(const nav_msgs::Odometry::ConstPtr &odom)
{
    this->pose_cov.pose = odom->pose;
    this->pose_cov.header = odom->header;
    pose_cov_pub();
}
void OdomToPose::pose_cov_pub() { this->pose_pub.publish(this->pose_cov); }
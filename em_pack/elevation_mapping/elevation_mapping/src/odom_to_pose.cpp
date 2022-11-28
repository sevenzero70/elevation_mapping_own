/*

/pose msgs:
std_msgs/Header header
  uint32 seq
  time stamp
  string frame_id
geometry_msgs/PoseWithCovariance pose
  geometry_msgs/Pose pose
    geometry_msgs/Point position
      float64 x
      float64 y
      float64 z
    geometry_msgs/Quaternion orientation
      float64 x
      float64 y
      float64 z
      float64 w
  float64[36] covariance

/odom msgs
std_msgs/Header header
  uint32 seq
  time stamp
  string frame_id
string child_frame_id
geometry_msgs/PoseWithCovariance pose
  geometry_msgs/Pose pose
    geometry_msgs/Point position
      float64 x
      float64 y
      float64 z
    geometry_msgs/Quaternion orientation
      float64 x
      float64 y
      float64 z
      float64 w
  float64[36] covariance
geometry_msgs/TwistWithCovariance twist
  geometry_msgs/Twist twist
    geometry_msgs/Vector3 linear
      float64 x
      float64 y
      float64 z
    geometry_msgs/Vector3 angular
      float64 x
      float64 y
      float64 z
  float64[36] covariance


*/

# include  "elevation_mapping/odom_to_pose.hpp"

OdomSubscriber::OdomSubscriber()
{
    this->odom_sub = this->odom_nh.subscribe("/rtabmap/odom", 1000, &OdomSubscriber::odom_callback, this);
}

void OdomSubscriber::odom_callback(const nav_msgs::Odometry::ConstPtr & odom)
{
    this->tmp_header = odom->header;
    this->tmp_pose = odom->pose;
}

void OdomSubscriber::odom_trans_set(odomtopose & pose)
{
    pose.header = this->tmp_header;
    pose.pose = this->tmp_pose;
}

PosePublisher::PosePublisher()
{
    this->pose_pub = this->pose_nh.advertise<geometry_msgs::PoseWithCovarianceStamped>("pose", 1000);
}

void PosePublisher::pose_trans_pub(odomtopose & pose)
{
    posemsg.header = pose.header;
    posemsg.pose = pose.pose;
    this->pose_pub.publish(this->posemsg);
}


# 'ETH' 中存储 elevation_mapping 相关的代码工程

# 1 kindr

    git clone https://github.com/anybotics/kindr.git
    cd kindr
    mkdir build
    cd build
    cmake ..
    sudo make install

# 2 Grid Map

    sudo apt-get install ros-melodic-grid-map

# 3 kindr_ros

    git clone https://github.com/ANYbotics/kindr_ros.git

# 4 pcl

    git clone https://github.com/PointCloudLibrary/pcl.git

    sudo apt-get update
    sudo apt-get install git build-essential linux-libc-dev
    sudo apt-get install cmake cmake-gui
    sudo apt-get install libusb-1.0-0-dev libusb-dev libudev-dev
    sudo apt-get install mpi-default-dev openmpi-bin openmpi-common
    sudo apt-get install libflann1.8 libflann-dev
    sudo apt-get install libeigen3-dev（这个需要自己下载正确版本安装）
    sudo apt-get install libboost-all-dev
    sudo apt-get install libvtk6-dev libvtk6-java libvtk6-jni libvtk6-qt-dev
    sudo apt-get install libqhull* libgtest-dev
    sudo apt-get install freeglut3-dev pkg-config
    sudo apt-get install libxmu-dev libxi-dev
    sudo apt-get install mono-complete
    sudo apt-get install openjdk-8-jdk openjdk-8-jre

    mkdir release
    cd release
    cmake ..
    make
    sudo make install

# 5 turtlebot3

    sudo apt install ros-melodic-turtlebot3*
    建立新的工作空间
    git clone https://github.com/ROBOTIS-GIT/turtlebot3_msgs.git
    git clone https://github.com/ROBOTIS-GIT/turtlebot3.git
    git clone https://github.com/ROBOTIS-GIT/turtlebot3_simulations.git
    编译

# else

- 安装过程中可能会有其他 package 的缺失
  sudo apt-get install ros-melodic-eigen-conversions
  sudo apt-get install ros-melodic-tf-conversions
  sudo apt-get install ros-melodic-trajectory-msgs

# 测试

roslaunch elevation_mapping_demos turtlesim3_waffle_demo.launch
export TURTLEBOT3_MODEL=waffle
roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch

- em_ws 是成功编译 elevation_mapping elevation_mapping_demo kindr kindr_ros 这四个 package 的 workspace。因为在编译当中可能会出现两个情况：
  1 创建 elevation_mapping_demo 失败
  2 找不到 kindr_ros 头文件
  对于 1，因为 git clone 之后是一个文件夹 elevation_mapping，有子文件 elevation_mapping 和 elevation_mapping_demo，所以尝试把这两个单独放出来（但是后面他又没有这个问题了，非常奇妙，直接 catkin_make 就可以了，找到原因了：之前不知道为什么自己把 eleation_mapping 根目录下创建了一个 package.xml，让他认为这是一个 package）
  对于 2，同理，尝试把 kindr_ros 的 include 放进 elevation_mapping 的 include 里

# 在 em_ws1.0 中运行

- 根据上述经验 em_ws1.0 成功编译。
  对于 2，其实就是目录问题，git clone 之后多了一个目录，让他找不到相应的文件，需要把里面的真正的 package 目录放出来

- 在经过测试之后发现，tf 加载失败了，rviz 中加载出来的模型是一个空白的 stl；之后发现可能是 python 版本的问题，然后将 elevation_mapping_demo/scripts 中第一行改为 python2.7（我的 python 是 2.7）重新 catkin_make

- 然后将 Fixed Frame 从 odom 换成 base_fooprint，因为 odom does not exist；但是存在从 wheel_left_link 到 base_footprint 不存在，于是在 launch 文件中添加<node name="joint_state_publisher" pkg="joint_state_publisher" type="joint_state_publisher" ></node>

- ！！！！！！重要 ！！！！！！ 建于问题一直解决不了，思索着换一个方向思考，会不会不是模型加载的问题，可可能是因为什么因为什么原因导致 robot 的控制失败
  解决方法：https://blog.csdn.net/renmengqisheng/article/details/120650563
  确实是因为自己少安装了一个 package……

# rtab-map+realsense+elevation_mapping

## RGB and depth sensor

D415/D435

> $ roslaunch realsense2_camera rs_camera.launch align_depth:=true

D435i/L515

> /#/ ISSUE: Use unite_imu_method:="copy" if imu topics keep stopping
> $ roslaunch realsense2_camera rs_camera.launch \

    align_depth:=true \
    unite_imu_method:="linear_interpolation" \
    enable_gyro:=true \
    enable_accel:=true

> $ rosrun imu_filter_madgwick imu_filter_node \

    _use_mag:=false \
    _publish_tf:=false \
    _world_frame:="enu" \
    /imu/data_raw:=/camera/imu \
    /imu/data:=/rtabmap/imu

## Mapping node

D415/D435

> $ roslaunch rtabmap_ros rtabmap.launch rviz:=true rtabmapviz:=false\
    rtabmap_args:="--delete_db_on_start" \
    depth_topic:=/camera/aligned_depth_to_color/image_raw \
    rgb_topic:=/camera/color/image_raw \
    camera_info_topic:=/camera/color/camera_info \
    approx_sync:=false

D435i

> $roslaunch rtabmap_ros rtabmap.launch rviz:=true rtabmapviz:=false\
    rtabmap_args:="--delete_db_on_start --Optimizer/GravitySigma 0.3" \
    depth_topic:=/camera/aligned_depth_to_color/image_raw \
    rgb_topic:=/camera/color/image_raw \
    camera_info_topic:=/camera/color/camera_info \
    approx_sync:=false \
    wait_imu_to_init:=true \
    imu_topic:=/rtabmap/imu

## realsense_demo.launch

> roslaunch elevation_mapping_demos realsense_demo.launch

_注意_
1、elevation_mapping 订阅了三个话题：\

- \points ==> \camera\color\depth\points
- \tf ：由于 rtab_map 提供的 tf 格式为[tf2_msgs/TFMessage](http://docs.ros.org/en/api/tf2_msgs/html/msg/TFMessage.html)；elevation_mapping 实际需要的 tf 格式为[tf/tfMessage](http://docs.ros.org/en/api/tf/html/msg/tfMessage.html) \
  还有一种可能 ，查看 rqtgraph 之后发现没有 baselink 到 cameralink 的 tf， 因为现在测试时机体就是 camera，所以将机体坐标改为 camera_link，解决问题！
  （但是，rtabmap 提供的 tf 只有 odom 到 camera_link，若增加 base，没有 odom 到 base 的 tf，当然也有可能是电脑没有反应过来）
- \pose：增加一个\odom_to_pose 的节点，将 rtab_map 提供的\rtabmap\odom 转换为\pose

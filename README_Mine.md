# 'ETH' 中存储elevation_mapping相关的代码工程
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
* 安装过程中可能会有其他package的缺失	
	sudo apt-get install ros-melodic-eigen-conversions
	sudo apt-get install ros-melodic-tf-conversions
	sudo apt-get install ros-melodic-trajectory-msgs

# 测试
roslaunch elevation_mapping_demos turtlesim3_waffle_demo.launch
export TURTLEBOT3_MODEL=waffle
roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch


* em_ws是成功编译elevation_mapping elevation_mapping_demo kindr kindr_ros 这四个package的workspace。因为在编译当中可能会出现两个情况：
1 创建elevation_mapping_demo失败
2 找不到kindr_ros头文件
对于1，因为git clone之后是一个文件夹elevation_mapping，有子文件elevation_mapping和elevation_mapping_demo，所以尝试把这两个单独放出来（但是后面他又没有这个问题了，非常奇妙，直接catkin_make就可以了，找到原因了：之前不知道为什么自己把eleation_mapping根目录下创建了一个package.xml，让他认为这是一个package）
对于2，同理，尝试把kindr_ros的include放进elevation_mapping的include里

# 在em_ws1.0中运行
* 根据上述经验em_ws1.0成功编译。
对于2，其实就是目录问题，git clone之后多了一个目录，让他找不到相应的文件，需要把里面的真正的package目录放出来

* 在经过测试之后发现，tf加载失败了，rviz中加载出来的模型是一个空白的stl；之后发现可能是python版本的问题，然后将elevation_mapping_demo/scripts中第一行改为python2.7（我的python是2.7）重新catkin_make

* 然后将Fixed Frame从odom换成base_fooprint，因为odom does not exist；但是存在从wheel_left_link到base_footprint不存在，于是在launch文件中添加<node name="joint_state_publisher" pkg="joint_state_publisher" type="joint_state_publisher" ></node>

* ！！！！！！重要 ！！！！！！ 建于问题一直解决不了，思索着换一个方向思考，会不会不是模型加载的问题，可可能是因为什么因为什么原因导致robot的控制失败
解决方法：https://blog.csdn.net/renmengqisheng/article/details/120650563
确实是因为自己少安装了一个package……





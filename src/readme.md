## odom_tf_package主要节点功能介绍

### pointxyz_pointxyzrgb_node
將pointxyz的点云消息转为pointxyzrgb的消息格式
用法：

rosrun odom_tf_package pointxyz_pointxyzrgb_node

### point_trans_node
將雷达坐标系下的点云信息转为全局坐标系 用法：

rosrun odom_tf_package point_trans_node /home/user/Data/lrx_work/free-space/dataset/pose/poses/00.txt


00.txt为GPS提供的绝对位姿转到相机坐标系下的坐标


## octomap_mapping 使用

为了使用启用octomap的颜色支持，需要通过安装源码来安装octomap-server

开启颜色支持需要以下几步：

1.编辑OctomapServer.h文件，打开COLOR_OCTOMAP_SERVER 宏的注释


2.在launch文件中禁用height_map，启用colored_map

> param name = "height_map" value = "false" />

> param name = "colored_map" value = "true" />

3.改动octomapserver.cpp文件中m_octree->averageNodeColor，可以设置制定的颜色

注意：要求输入的点云信息必须具有rgb信息，即pointxyzrgb格式

使用：roslaunch octomap_server octomap_mapping.launch 

roslaunch transport.launch可以将输入但image_raw_compressed文件转为image_raw文件

## publish_point 使用
目的：将.pcd文件转为ros点云消息并发布出来
rosrun publish_point creat_point_node


#include <ros/ros.h>
#include <pcl/point_cloud.h>
//msgs type and conversion
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
//pcd io
#include <pcl/io/pcd_io.h>
//point types
#include <pcl/point_types.h>
#include <octomap/octomap.h> 
#include <octomap/OcTree.h>
#include <octomap_ros/conversions.h>
#include <octomap_msgs/Octomap.h>
#include <octomap_msgs/conversions.h>

ros::Subscriber sub;
ros::Publisher pub;
octomap::OcTree *tree;

void call_back(const sensor_msgs::PointCloud2ConstPtr& input)
{
//Convert the sensor_msgs/PointCloud2 data to pcl/PointCloud
  pcl::PointCloud<pcl::PointXYZ> cloud;
  pcl::fromROSMsg (*input, cloud);//cloud is the output
  std::cout<<input->header.stamp.nsec<<std::endl;
  tree = new octomap::OcTree(0.05);
  for(auto p:cloud.points){
    tree->updateNode(octomap::point3d(p.x,p.y,p.z),true);
  }
  tree->updateInnerOccupancy();

  octomap_msgs::Octomap octomap_msg;
  octomap_msgs::binaryMapToMsg(*tree,octomap_msg);
  octomap_msg.header.frame_id="world";
  octomap_msg.header.stamp=ros::Time::now();
  octomap_msg.id=1;
  std::cout<<"octomap size:"<<octomap_msg.data.size()<<std::endl;
  
  pub.publish(octomap_msg);

  
 

};

int main(int argc,char** argv)
{
// Initialize ROS
  ros::init (argc, argv, "point2oct");
  ros::NodeHandle nh;
  
  pub = nh.advertise<octomap_msgs::Octomap>("octomap",1);
  sub = nh.subscribe("cloud",1,call_back);
  ros::spin ();
  return 0;
}


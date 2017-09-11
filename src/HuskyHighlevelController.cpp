#include "husky_highlevel_controller/HuskyHighlevelController.hpp"

namespace husky_highlevel_controller {

	HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle) :
	  nodeHandle_(nodeHandle)
	{
	  // Welcome
	  HuskyHighlevelController::Welcome();

	  // Subscriptions
	  HuskyHighlevelController::subscription_gen();
	}

	HuskyHighlevelController::~HuskyHighlevelController()
	{
		
	}
	void HuskyHighlevelController::Welcome(){
		ROS_INFO_STREAM("Starting: "<<ros::this_node::getName());
	}
	void HuskyHighlevelController::subscription_gen(){
		if (!nodeHandle_.getParam("scan_subscriber_topic_name", sub_topic_name)) {ROS_ERROR("Could not find topic parameter!"); }
		if (!nodeHandle_.getParam("scan_subscriber_queue_size", queue_size)) {ROS_ERROR("Could not find topic parameter!"); }
		sub_scan_ = nodeHandle_.subscribe(sub_topic_name, queue_size,&HuskyHighlevelController::scanCallback,this);
	}
	void HuskyHighlevelController::scanCallback(const sensor_msgs::LaserScan &scan){

	  float minn=10000;

	  for(int i=0;i<floor((scan.angle_max-scan.angle_min)/scan.angle_increment);i++){
	        if(minn>scan.ranges[i]){
	          minn = scan.ranges[i];
	        }
	      }
    ROS_INFO_STREAM("Minimum laser distance (m): "<<minn);

	  //vector<int> vec (scan.ranges, scan.ranges + sizeof(scan.ranges) / sizeof(scan.ranges[0]) )
    //ROS_INFO_STREAM("Minimum laser distance (m): "<<*std::min_element(scan.ranges, scan.ranges + sizeof(scan.ranges) / sizeof(scan.ranges[0])) <<"\n");

	  //ROS_INFO_STREAM("Minimum laser distance (m): "<<*std::min_element(scan.ranges,scan.ranges+floor((scan.angle_max-scan.angle_min)/scan.angle_increment))<<"\n");
	}
	
} /* namespace */

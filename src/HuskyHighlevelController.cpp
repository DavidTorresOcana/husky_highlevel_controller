#include "husky_highlevel_controller/HuskyHighlevelController.hpp"

namespace husky_highlevel_controller {

	HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle) :
	  nodeHandle_(nodeHandle)
	{
		
	}

	HuskyHighlevelController::~HuskyHighlevelController()
	{
		
	}
	void HuskyHighlevelController::Welcome(){
		ROS_INFO_STREAM("Starting: "<<ros::this_node::getNamespace());
	}
	void HuskyHighlevelController::subscription_gen(){
		if (!nodeHandle_.getParam("scan_subscriber_topic_name", sub_topic_name)) {ROS_ERROR("Could not find topic parameter!"); }
		if (!nodeHandle_.getParam("scan_subscriber_queue_size", queue_size)) {ROS_ERROR("Could not find topic parameter!"); }
		sub_scan_ = nodeHandle_.subscribe(sub_topic_name,queue_size,&HuskyHighlevelController::scanCallback,this);
	}
	void HuskyHighlevelController::scanCallback(const sensor_msgs::LaserScan &scan){
		ROS_INFO_STREAM("Minimum laser distance (m): ", scan.range_min);
	}
	
} /* namespace */

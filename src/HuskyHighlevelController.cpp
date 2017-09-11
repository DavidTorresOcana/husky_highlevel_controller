#include "husky_highlevel_controller/HuskyHighlevelController.hpp"

namespace husky_highlevel_controller {

	HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle) :
	  nodeHandle_(nodeHandle)
	{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> f83d14b439d5949fb872e7cf050755dae7be901e
	  // Welcome
	  HuskyHighlevelController::Welcome();

	  // Subscriptions
	  HuskyHighlevelController::subscription_gen();
<<<<<<< HEAD

=======
=======
		
>>>>>>> 9302b2d401ece18f8849567e3fb895c1cb6b6d41
>>>>>>> f83d14b439d5949fb872e7cf050755dae7be901e
	}

	HuskyHighlevelController::~HuskyHighlevelController()
	{
		
	}
	void HuskyHighlevelController::Welcome(){
<<<<<<< HEAD
		ROS_INFO_STREAM("Starting: "<<ros::this_node::getName());
=======
<<<<<<< HEAD
		ROS_INFO_STREAM("Starting: "<<ros::this_node::getName());
=======
		ROS_INFO_STREAM("Starting: "<<ros::this_node::getNamespace());
>>>>>>> 9302b2d401ece18f8849567e3fb895c1cb6b6d41
>>>>>>> f83d14b439d5949fb872e7cf050755dae7be901e
	}
	void HuskyHighlevelController::subscription_gen(){
		if (!nodeHandle_.getParam("scan_subscriber_topic_name", sub_topic_name)) {ROS_ERROR("Could not find topic parameter!"); }
		if (!nodeHandle_.getParam("scan_subscriber_queue_size", queue_size)) {ROS_ERROR("Could not find topic parameter!"); }
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> f83d14b439d5949fb872e7cf050755dae7be901e
		sub_scan_ = nodeHandle_.subscribe(sub_topic_name, queue_size,&HuskyHighlevelController::scanCallback,this);
	}
	void HuskyHighlevelController::scanCallback(const sensor_msgs::LaserScan &scan){

		  float minn=10000;

<<<<<<< HEAD
		  for(int i=0;i<floor((scan.angle_max-scan.angle_min)/scan.angle_increment);i++){
				if(minn>scan.ranges[i]){
				  minn = scan.ranges[i];
				}
			  }
		ROS_INFO_STREAM("Minimum laser distance (m): "<<minn);
=======
	  //vector<int> vec (scan.ranges, scan.ranges + sizeof(scan.ranges) / sizeof(scan.ranges[0]) )
    //ROS_INFO_STREAM("Minimum laser distance (m): "<<*std::min_element(scan.ranges, scan.ranges + sizeof(scan.ranges) / sizeof(scan.ranges[0])) <<"\n");

	  //ROS_INFO_STREAM("Minimum laser distance (m): "<<*std::min_element(scan.ranges,scan.ranges+floor((scan.angle_max-scan.angle_min)/scan.angle_increment))<<"\n");
=======
		sub_scan_ = nodeHandle_.subscribe(sub_topic_name,queue_size,&HuskyHighlevelController::scanCallback,this);
	}
	void HuskyHighlevelController::scanCallback(const sensor_msgs::LaserScan &scan){
		ROS_INFO_STREAM("Minimum laser distance (m): ", scan.range_min);
>>>>>>> 9302b2d401ece18f8849567e3fb895c1cb6b6d41
>>>>>>> f83d14b439d5949fb872e7cf050755dae7be901e
	}
	
} /* namespace */

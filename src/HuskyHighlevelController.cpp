#include "husky_highlevel_controller/HuskyHighlevelController.hpp"

namespace husky_highlevel_controller {

	HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle) :
	  nodeHandle_(nodeHandle)
	{

	  // Welcome
	  HuskyHighlevelController::Welcome();
	  // Load parameters from server
      HuskyHighlevelController::Load_param();
	  // Subscriptions
	  HuskyHighlevelController::subscription_gen();
	  // Publishers
    HuskyHighlevelController::publishers_gen();
    // Services
    HuskyHighlevelController::services_gen();

	}

	HuskyHighlevelController::~HuskyHighlevelController()
	{
		
	}
	void HuskyHighlevelController::Welcome(){
		  ROS_INFO_STREAM("Starting: "<<ros::this_node::getName());
	}
	void HuskyHighlevelController::Load_param(){
	    if (!nodeHandle_.getParam("scan_subscriber_topic_name", sub_topic_name)) {ROS_ERROR("Could not find topic parameter!"); }
      if (!nodeHandle_.getParam("scan_subscriber_queue_size", queue_size)) {ROS_ERROR("Could not find topic parameter!"); }
      if (!nodeHandle_.getParam("angular_ctrl_p_gain", ang_p_gain)) {ROS_ERROR("Could not find topic parameter!"); }
      if (!nodeHandle_.getParam("linear_ctrl_vel", lin_vel)) {ROS_ERROR("Could not find topic parameter!"); }
  }
	void HuskyHighlevelController::subscription_gen(){

      sub_scan_ = nodeHandle_.subscribe(sub_topic_name, queue_size,&HuskyHighlevelController::scanCallback,this);
	}
	void HuskyHighlevelController::publishers_gen(){
      pub_vel_cmd_ = nodeHandle_.advertise<geometry_msgs::Twist>("/cmd_vel",10);
      vis_pub = nodeHandle_.advertise<visualization_msgs::Marker>("/visualization_marker", 0 );
	 }
	void HuskyHighlevelController::scanCallback(const sensor_msgs::LaserScan &scan){
		  min_range=10000;

		  for(int i=0;i<floor((scan.angle_max-scan.angle_min)/scan.angle_increment);i++){
          if(min_range>scan.ranges[i]){
            min_range = scan.ranges[i];
            ang_min = scan.angle_min + scan.angle_increment*i;
          }
			  }
		  //ROS_INFO_STREAM("Minimum laser distance (m): "<<min_range);

		  // Relative position to the pillar x = min_range*cos(ang_min), y = min_range*sin(ang_min)
		  x_pillar = min_range*cos(ang_min);
		  y_pillar = min_range*sin(ang_min);
		  ROS_INFO_STREAM("\n x = "<<x_pillar<<"\n y = "<<y_pillar);

		  // Execute the control loop
		  HuskyHighlevelController::control_2_target();

		  // Publish the marker of the obstacle
		  marker.header.frame_id = "base_laser";
		  marker.header.stamp = ros::Time();
		  marker.ns = "Pillar";
		  marker.id = 0;
		  marker.type = visualization_msgs::Marker::SPHERE;
		  marker.action = visualization_msgs::Marker::ADD;
		  marker.pose.position.x = x_pillar;
		  marker.pose.position.y = y_pillar;
		  marker.pose.position.z = 0;
		  marker.scale.x = 1;
		  marker.scale.y = 1;
		  marker.scale.z = 10;
		  marker.color.a = 1.0; // Don't forget to set the alpha!
		  marker.color.r = 0.0;
		  marker.color.g = 1.0;
		  marker.color.b = 0.0;

		  // Publish marker positions, with diferent method
		  /*marker.header.frame_id = "odom";

		  try {
		    transformStamped = tfBuffer.lookupTransform("base_laser","odom", ros::Time(0));
		  }
		  catch (tf2::TransformException &exception) {
		    ROS_WARN("%s", exception.what());
		    ros::Duration(1.0).sleep();
		    continue;
		  }
		  ang2rob = atan2(transformStamped.transform.translation.y, transformStamped.transform.translation.x);
		  r2rob = sqrt(transformStamped.transform.translation.y*transformStamped.transform.translation.y+ transformStamped.transform.translation.x* transformStamped.transform.translation.x);

		  marker.pose.position.x = r2rob*cos(ang2rob)+min_range*cos(ang_min+ang2rob);
		  marker.pose.position.y = r2rob*sin(ang2rob)+min_range*sin(ang_min+ang2rob);
*/
		  vis_pub.publish( marker );
	}

  void HuskyHighlevelController::control_2_target(){
      // Compute vel command to hit the pillar
      msg_vel_cmd_.linear.x = lin_vel;
      msg_vel_cmd_.angular.z =  ang_p_gain*(0-ang_min);

      if(!start_stop_flag){ // If  Stop has been commanded
        msg_vel_cmd_.linear.x = 0.0;
        msg_vel_cmd_.angular.z = 0.0;
      }
      // Publish the command
      pub_vel_cmd_.publish(msg_vel_cmd_);

  }
  void HuskyHighlevelController::services_gen()
  {
    service_start_stop = nodeHandle_.advertiseService("husky_start_stop", &HuskyHighlevelController::srv_action_start_stop,this);
  }
  bool HuskyHighlevelController::srv_action_start_stop(std_srvs::SetBool::Request &request, std_srvs::SetBool::Response &response)
  {
      try{
        // if true means Start/resume the robot
        if(request.data){  start_stop_flag = true; }
        else{  start_stop_flag = false; }
        response.success = true;
      }
      catch(...){
        ROS_WARN("Impossible to execute Start-Stop service");
        ros::Duration(1.0).sleep();
        response.success = false;
        //continue;
      }

      ROS_INFO("request: %i", request.data );
      ROS_INFO(" sending back response: [%i]", response.success);
      return true;
  }
} /* namespace */

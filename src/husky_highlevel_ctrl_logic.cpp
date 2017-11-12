#include <ros/ros.h>
#include <std_srvs/SetBool.h>
#include <sensor_msgs/LaserScan.h>
#include "husky_highlevel_controller/HuskyHighlevelController.hpp"

// Global to file variables
float min_range, ang_min;
ros::ServiceClient client_2_start_stop;
std_srvs::SetBool srvc_husky_start_stop;

// Predefinitions
void HLC_safety_stop();

void laserscan_safety(const sensor_msgs::LaserScan &scan){
  min_range=10000;

  for(int i=0;i<floor((scan.angle_max-scan.angle_min)/scan.angle_increment);i++){
      if(min_range>scan.ranges[i]){
        min_range = scan.ranges[i];
        ang_min = scan.angle_min + scan.angle_increment*i;
      }
    }
  //ROS_INFO_STREAM("Minimum laser distance (m): "<<min_range);

  // High Level control logic: Choose behaviour
  HLC_safety_stop();

}

void HLC_safety_stop(){
  static bool stopped = false; // Flag that indicates if robot is stopped

  // Safety routine: stop the robot if it is too close to something
  if(min_range<1.0 && !stopped){
        srvc_husky_start_stop.request.data = false;
        if (client_2_start_stop.call(srvc_husky_start_stop)) {
          ROS_INFO("Success?: %d", srvc_husky_start_stop.response.success);
          stopped = true;
        }
        else { ROS_ERROR("Failed to call service add_two_ints"); }
    }
    else if(stopped && min_range>=1.0){
        srvc_husky_start_stop.request.data = true;
        if (client_2_start_stop.call(srvc_husky_start_stop)) {
            ROS_INFO("Success?: %d", srvc_husky_start_stop.response.success);
            stopped = false;
        }
        else { ROS_ERROR("Failed to call service add_two_ints"); }
    }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "husky_highlevel_ctrl_logic");
  ros::NodeHandle nh;

  // Subsriptions
  ros::Subscriber sub_scan = nh.subscribe("/scan", 200,laserscan_safety);

  // Services clients
  client_2_start_stop = nh.serviceClient<std_srvs::SetBool>("/husky_highlevel_controller/husky_start_stop");

  ros::spin();

  return 0;
}

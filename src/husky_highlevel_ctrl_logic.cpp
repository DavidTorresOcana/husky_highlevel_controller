#include <ros/ros.h>
#include <std_srvs/SetBool.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/Imu.h>
#include "husky_highlevel_controller/HuskyHighlevelController.hpp"

// Global to file variables
float min_range, ang_min;
ros::ServiceClient client_2_start_stop;
std_srvs::SetBool srvc_husky_start_stop;

// Functions Prototypes
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
  if(min_range<1.0){
    HLC_safety_stop();
  }

}

void HLC_safety_stop(){
  // Safety routine: stop the robot if it is too close to something
  srvc_husky_start_stop.request.data = false;
  if (client_2_start_stop.call(srvc_husky_start_stop)) {
    ROS_INFO("Success?: %d", srvc_husky_start_stop.response.success);
  }
  else { ROS_ERROR("Failed to call service add_two_ints"); }

}

void imu_crash_safety(const sensor_msgs::Imu &imu_data){
  //IMU logic for crash detection
  ROS_INFO("IMU accelerations: X: %f, Y: %f , Z: %f ",imu_data.linear_acceleration.x,
                         imu_data.linear_acceleration.y,imu_data.linear_acceleration.z);
  if( abs(imu_data.linear_acceleration.x)>3.0 || abs(imu_data.linear_acceleration.y)>3.0 ){
      HLC_safety_stop();
  }

}

int main(int argc, char **argv)
{
  bool crash_stop,obstacle_proximity_stop;
  ros::init(argc, argv, "husky_highlevel_ctrl_logic");
  ros::NodeHandle nh;

  // Load parameters from server
  if (!nh.getParam("/husky_highlevel_controller/safety_control/obstacle_proximity_stop", obstacle_proximity_stop)) {ROS_ERROR("Could not find topic parameter safety_control/obstacle_proximity_stop"); }
  if (!nh.getParam("/husky_highlevel_controller/safety_control/crash_stop", crash_stop)) {ROS_ERROR("Could not find topic parameter safety_control/crash_stop"); }

  // Subscriptions
  ros::Subscriber sub_imu, sub_scan;

  if(obstacle_proximity_stop==true){
    sub_scan = nh.subscribe("/scan", 200,laserscan_safety);
  }
  if(crash_stop==true){
    sub_imu = nh.subscribe("/imu/data", 200,imu_crash_safety);
  }

  // Services clients
  client_2_start_stop = nh.serviceClient<std_srvs::SetBool>("/husky_highlevel_controller/husky_start_stop");

  ros::spin();

  return 0;
}

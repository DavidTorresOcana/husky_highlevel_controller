#include <ros/ros.h>
#include <roscpp_tutorials/TwoInts.h>
#include <std_srvs/SetBool.h>

bool action(std_srvs::SetBool::Request &request,
         std_srvs::SetBool::Response &response)
{
  response.success = request.data;

  ROS_INFO("request: %i", request.data );
  ROS_INFO(" sending back response: [%i]", response.success);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "husky_highlevel_ctrl_services");
  ros::NodeHandle nh;
  ros::ServiceServer service =
  nh.advertiseService("husky_start_stop", action);
  ros::spin();

  return 0;
}

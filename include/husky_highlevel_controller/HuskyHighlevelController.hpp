#pragma once

#include <ros/ros.h>
#include "std_msgs/String.h"
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <std_srvs/SetBool.h>

namespace husky_highlevel_controller {

/*!
 * Class containing the Husky Highlevel Controller
 */
	class HuskyHighlevelController {
		private:
			ros::NodeHandle nodeHandle_;

			ros::Subscriber sub_scan_;

			ros::Publisher pub_vel_cmd_;
			geometry_msgs::Twist msg_vel_cmd_;
			ros::Publisher vis_pub;
			visualization_msgs::Marker marker;

			/*tf2_ros::Buffer tfBuffer;
      tf2_ros::TransformListener tfListener(tfBuffer);
      geometry_msgs::TransformStamped transformStamped;
			 */

			ros::ServiceServer service_start_stop;

			std::string sub_topic_name;
			int queue_size;
			bool start_stop_flag=true; // True means can move. false means Stop!
			float min_range, ang_min, x_pillar, y_pillar, ang_p_gain,lin_vel,ang2rob,r2rob;
		public:
			/*!
			 * Constructor.
			 */
			HuskyHighlevelController(ros::NodeHandle& nodeHandle);

			/*!
			 * Destructor.
			 */
			virtual ~HuskyHighlevelController();
			/*!
			 * Welcome.
			 */
			virtual void Welcome();
			/*!
			 * Subscriptions.
			 */
			virtual void subscription_gen();
			/*!
			 * Callback subscriber.
			 */
			virtual void scanCallback(const sensor_msgs::LaserScan &scan);
			/*!
       * Publishers.
       */
      virtual void publishers_gen();
      /*!
       * Load parameters.
       */
      virtual void Load_param();
      /*!
       * Control loop function.
       */
      virtual void control_2_target();
      /*!
       * Services creation.
       */
      virtual void services_gen();
      /*!
       * Services Start-stop action.
       */
      virtual bool srv_action_start_stop(std_srvs::SetBool::Request &request, std_srvs::SetBool::Response &response);

	};

} /* namespace */

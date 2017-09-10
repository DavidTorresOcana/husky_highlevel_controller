#pragma once

#include <ros/ros.h>
#include "std_msgs/String.h"
#include <sensor_msgs/LaserScan.h>

namespace husky_highlevel_controller {

/*!
 * Class containing the Husky Highlevel Controller
 */
	class HuskyHighlevelController {
		private:
			ros::NodeHandle nodeHandle_;
			ros::Subscriber sub_scan_;
			std::string sub_topic_name;
			int queue_size;
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


	};

} /* namespace */

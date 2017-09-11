#pragma once

#include <ros/ros.h>
#include "std_msgs/String.h"
#include <sensor_msgs/LaserScan.h>
<<<<<<< HEAD

=======
<<<<<<< HEAD
#include <algorithm>
#include <iostream>
#include <vector>
=======
>>>>>>> 9302b2d401ece18f8849567e3fb895c1cb6b6d41
>>>>>>> f83d14b439d5949fb872e7cf050755dae7be901e

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

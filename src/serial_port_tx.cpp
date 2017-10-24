#include <string>
#include <iostream>
#include <cstdio>
#include "ros/ros.h"

#include "serial_port.h"

#include "std_msgs/String.h"
#include <sstream>


using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

//string result;

//serial::Serial my_serial; 
static serial_Node::serial_Node* my_serial;

void chatterCallBack(const std_msgs::String::ConstPtr& msg) {
    // ROS_INFO("I heard: [%s]", msg->data.c_str());
    my_serial->write(msg->data.c_str());
}

int main(int argc, char **argv) {
	ros::init(argc , argv, "serial_port_tx");
	ros::NodeHandle nh;
	ros::Subscriber serial0_rx = nh.subscribe("uart1_tx", 1000, chatterCallBack);
	ros::Rate loop_rate(10);
	my_serial = serial_Node::serial_Node::getInstance();
	my_serial->initSerial();

	ros::spin();
	// while(ros::ok()) {
	// 	std_msgs::String msg;
	// 	std::stringstream ss;
	// 	if(openSerial()==true) run(argc, argv);
	// 	ss<<result;
	// 	msg.data = ss.str();
	// 	serial0_tx.publish(msg);
	// 	ros::spinOnce();
	// 	loop_rate.sleep();

	// } 
	::ros::shutdown();
	//return 0;
  // try {
  //   return run(argc, argv);
  // } catch (exception &e) {
  //   cerr << "Unhandled Exception: " << e.what() << endl;
  // }
}

#include "serial_port.h"
#include <iostream>
#include <cstdio>
#include "ros/ros.h"
// OS Specific sleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "serial/serial.h"

#include "std_msgs/String.h"
#include <sstream>


using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

//string result;

serial::Serial my_serial; 

// serial_Node::serial_Node(){

// }


// serial_Node::serial_Node(const serial_Node&){

// }


// serial_Node& serial_Node::operator=(const serial_Node&){

// }

//在此处初始化
serial_Node::serial_Node* serial_Node::serial_Node::m_serial_Node = new serial_Node();
serial_Node::serial_Node* serial_Node::serial_Node::getInstance(){
	return serial_Node::serial_Node::m_serial_Node;
}

void my_sleep(unsigned long milliseconds) {
#ifdef _WIN32
      Sleep(milliseconds); // 100 ms
#else
      usleep(milliseconds*1000); // 100 ms
#endif
}

void enumerate_ports()
{
	vector<serial::PortInfo> devices_found = serial::list_ports();

	vector<serial::PortInfo>::iterator iter = devices_found.begin();

	while( iter != devices_found.end() )
	{
		serial::PortInfo device = *iter++;

		printf( "(%s, %s, %s)\n", device.port.c_str(), device.description.c_str(),
     device.hardware_id.c_str() );
	}
}

// void print_usage()
// {
// 	cerr << "Usage: test_serial {-e|<serial port address>} ";
//     cerr << "<baudrate> [test string]" << endl;
// }

bool serial_Node::serial_Node::openSerial()
{
	if(my_serial.isOpen())
		return true; 
	my_serial.open();
	return my_serial.isOpen();
}

void serial_Node::serial_Node::initSerial()
{
	if(!my_serial.isOpen()) {
		my_serial.setPort("/dev/ttyUSB0");
	 	serial::Timeout::simpleTimeout(1000);
	 	serial::Timeout timeout	= serial::Timeout::simpleTimeout(1000);
	 	my_serial.setTimeout(timeout);
	 	my_serial.setBaudrate (115200);
	 	while(openSerial() == false) {
	 		ROS_INFO("Serial port is not connected, trying to open agin...");
	 	}
	}

}

void serial_Node::serial_Node::readline(std::string &buffer) {
  my_serial.readline(buffer);
}

void serial_Node::serial_Node::write(const std::string &data) {
	my_serial.write(data);
}

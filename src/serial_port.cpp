#include <string>
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

string result;

serial::Serial my_serial; 

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

bool openSerial()
{
	if(my_serial.isOpen())
		return true; 
	my_serial.open();
	return my_serial.isOpen();
}

void connectSerial() {

	
}

void initSerial()
{
	my_serial.setPort("/dev/ttyUSB0");
 	serial::Timeout::simpleTimeout(1000);
 	serial::Timeout timeout	= serial::Timeout::simpleTimeout(1000);
 	my_serial.setTimeout(timeout);
 	my_serial.setBaudrate (115200);
 	while(openSerial() == false) {
 		ROS_INFO("Serial port is not connected, trying to open agin...");
 	}
}

int run(int argc, char **argv)
{
//   if(argc < 2) {
// 	  print_usage();
//     return 0;
//   }

//   // Argument 1 is the serial port or enumerate flag
//   string port(argv[1]);

//   if( port == "-e" ) {
// 	  enumerate_ports();
// 	  return 0;
//   }
//   else if( argc < 3 ) {
// 	  print_usage();
// 	  return 1;
//   }

//   // Argument 2 is the baudrate
//   unsigned long baud = 0;
// #if defined(WIN32) && !defined(__MINGW32__)
//   sscanf_s(argv[2], "%lu", &baud);
// #else
//   sscanf(argv[2], "%lu", &baud);
// #endif

  // port, baudrate, timeout in milliseconds
 // serial::Serial my_serial(port, baud, serial::Timeout::simpleTimeout(1000));

  // cout << "Is the serial port open?";
   if(my_serial.isOpen())
   {
   		//cout << " Yes." << endl;
   	 	my_serial.readline(result);
   }
   //else {
   	//	cout << " No." << endl;
   //}
  //   cout << " Yes." << endl;
  // else
  //   cout << " No." << endl;

  // Get the Test string
  // int count = 0;
  // string test_string;
  // if (argc == 4) {
  //   test_string = argv[3];
  // } else {
  //   test_string = "Testing.";
  // }

  //xx
   //my_serial.setTimeout(serial::Timeout::max(), 50, 0, 50, 0);
    //size_t bytes_wrote = my_serial.write(test_string);
    
    //cout << result.length() << ", String read: " << result << endl;

   //source
  // Test the timeout, there should be 1 second between prints
  // cout << "Timeout == 1000ms, asking for 1 more byte than written." << endl;
  // while (count < 10) {
  //   size_t bytes_wrote = my_serial.write(test_string);

  //   string result = my_serial.read(test_string.length()+1);

  //   cout << "Iteration: " << count << ", Bytes written: ";
  //   cout << bytes_wrote << ", Bytes read: ";
  //   cout << result.length() << ", String read: " << result << endl;

  //   count += 1;
  // }

  // // Test the timeout at 250ms
  // my_serial.setTimeout(serial::Timeout::max(), 250, 0, 250, 0);
  // count = 0;
  // cout << "Timeout == 250ms, asking for 1 more byte than written." << endl;
  // while (count < 10) {
  //   size_t bytes_wrote = my_serial.write(test_string);

  //   string result = my_serial.read(test_string.length()+1);

  //   cout << "Iteration: " << count << ", Bytes written: ";
  //   cout << bytes_wrote << ", Bytes read: ";
  //   cout << result.length() << ", String read: " << result << endl;

  //   count += 1;
  // }

  // // Test the timeout at 250ms, but asking exactly for what was written
  // count = 0;
  // cout << "Timeout == 250ms, asking for exactly what was written." << endl;
  // while (count < 10) {
  //   size_t bytes_wrote = my_serial.write(test_string);

  //   string result = my_serial.read(test_string.length());

  //   cout << "Iteration: " << count << ", Bytes written: ";
  //   cout << bytes_wrote << ", Bytes read: ";
  //   cout << result.length() << ", String read: " << result << endl;

  //   count += 1;
  // }

  // // Test the timeout at 250ms, but asking for 1 less than what was written
  // count = 0;
  // cout << "Timeout == 250ms, asking for 1 less than was written." << endl;
  // while (count < 10) {
  //   size_t bytes_wrote = my_serial.write(test_string);

  //   string result = my_serial.read(test_string.length()-1);

  //   cout << "Iteration: " << count << ", Bytes written: ";
  //   cout << bytes_wrote << ", Bytes read: ";
  //   cout << result.length() << ", String read: " << result << endl;

  //   count += 1;
  // }

  return 0;
}

void chatterCallBack(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv) {
	ros::init(argc , argv, "serial_port");
	ros::NodeHandle nh ;
	ros::Publisher serial0_tx = nh.advertise<std_msgs::String>("uart1_tx",1000);
	ros::Subscriber serial0_rx = n.subscribe("uart1_tx", 1000, chatterCallBack);
	ros::Rate loop_rate(10);
	initSerial();
	while(ros::ok()) {
		std_msgs::String msg;
		std::stringstream ss;
		if(openSerial()==true) run(argc, argv);
		ss<<result;
		msg.data = ss.str();
		serial0_tx.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();

	} 
	::ros::shutdown();
	//return 0;
  // try {
  //   return run(argc, argv);
  // } catch (exception &e) {
  //   cerr << "Unhandled Exception: " << e.what() << endl;
  // }
}

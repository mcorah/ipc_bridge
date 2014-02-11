#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <std_msgs/Empty.h>
#include <ipc_bridge/msgs/std_msgs_Empty.h>

#define NAMESPACE std_msgs
#define NAME Empty

ros::Publisher pub;
NAMESPACE::NAME out_msg;

void callback(const ipc_bridge::NAMESPACE::NAME &msg)
{
  pub.publish(out_msg);
}

#include <ipc_bridge/subscriber.h>

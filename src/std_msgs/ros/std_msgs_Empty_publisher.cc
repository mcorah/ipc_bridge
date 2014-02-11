#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <std_msgs/Empty.h>
#include <ipc_bridge/msgs/std_msgs_Empty.h>

#define NAMESPACE std_msgs
#define NAME Empty

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{
  p->Publish(out_msg);
}

#include <ipc_bridge/publisher.h>

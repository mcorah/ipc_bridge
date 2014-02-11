#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <nav_msgs/Path.h>
#include <ipc_bridge/msgs/nav_msgs_Path.h>

#define NAMESPACE nav_msgs
#define NAME Path

ros::Publisher pub;
NAMESPACE::NAME out_msg;

unsigned int frame_id_prior_size = 0;

void callback(const ipc_bridge::NAMESPACE::NAME &msg)
{
  out_msg.header.seq = msg.header.seq;
  out_msg.header.stamp = ros::Time(msg.header.stamp);
  if (msg.header.frame_id != 0)
    out_msg.header.frame_id = std::string(msg.header.frame_id);
  else
    out_msg.header.frame_id = std::string("");

  out_msg.poses.resize(msg.poses_length);
  for (unsigned int i = 0; i < msg.poses_length; i++)
    {
      out_msg.poses[i].header.seq = msg.header.seq;
      out_msg.poses[i].header.stamp = ros::Time(msg.header.stamp);
      if (msg.poses[i].header.frame_id != 0)
        out_msg.poses[i].header.frame_id = std::string(msg.poses[i].header.frame_id);
      else
        out_msg.poses[i].header.frame_id = std::string("");

      out_msg.poses[i].pose.position.x = msg.poses[i].pose.position.x;
      out_msg.poses[i].pose.position.y = msg.poses[i].pose.position.y;
      out_msg.poses[i].pose.position.z = msg.poses[i].pose.position.z;

      out_msg.poses[i].pose.orientation.x = msg.poses[i].pose.orientation.x;
      out_msg.poses[i].pose.orientation.y = msg.poses[i].pose.orientation.y;
      out_msg.poses[i].pose.orientation.z = msg.poses[i].pose.orientation.z;
      out_msg.poses[i].pose.orientation.w = msg.poses[i].pose.orientation.w;
    }

  pub.publish(out_msg);
}

#include <ipc_bridge/subscriber.h>

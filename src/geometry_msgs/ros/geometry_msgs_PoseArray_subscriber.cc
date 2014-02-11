/*
ipc_bridge: ROS-MATLAB interface via CMU's IPC
Copyright (C) 2014  Nathan Michael

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include <ros/ros.h>
#include <ipc_bridge/ipc_bridge.h>

#include <geometry_msgs/PoseArray.h>
#include <ipc_bridge/msgs/geometry_msgs_PoseArray.h>

#define NAMESPACE geometry_msgs
#define NAME PoseArray

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
      out_msg.poses[i].position.x = msg.poses[i].position.x;
      out_msg.poses[i].position.y = msg.poses[i].position.y;
      out_msg.poses[i].position.z = msg.poses[i].position.z;

      out_msg.poses[i].orientation.x = msg.poses[i].orientation.x;
      out_msg.poses[i].orientation.y = msg.poses[i].orientation.y;
      out_msg.poses[i].orientation.z = msg.poses[i].orientation.z;
      out_msg.poses[i].orientation.w = msg.poses[i].orientation.w;
    }

  pub.publish(out_msg);
}

#include <ipc_bridge/subscriber.h>

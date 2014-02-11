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

#include <nav_msgs/Path.h>
#include <ipc_bridge/msgs/nav_msgs_Path.h>

#define NAMESPACE nav_msgs
#define NAME Path

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

unsigned int frame_id_prior_size = 0;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{
  out_msg.header.seq = msg->header.seq;
  out_msg.header.stamp = msg->header.stamp.toSec();

  if (strlen(msg->header.frame_id.c_str()) != frame_id_prior_size)
    {
      if (out_msg.header.frame_id != 0)
        delete[] out_msg.header.frame_id;

      out_msg.header.frame_id =
        new char[strlen(msg->header.frame_id.c_str()) + 1];
      strcpy(out_msg.header.frame_id, msg->header.frame_id.c_str());
      frame_id_prior_size = strlen(msg->header.frame_id.c_str());
    }

  out_msg.poses_length = msg->poses.size();
  out_msg.poses = new geometry_msgs_PoseStamped[out_msg.poses_length];

  for (unsigned int i = 0; i < msg->poses.size(); ++i)
    {
      out_msg.poses[i].header.seq = msg->poses[i].header.seq;
      out_msg.poses[i].header.stamp = msg->poses[i].header.stamp.toSec();

      out_msg.poses[i].header.frame_id =
        new char[strlen(msg->poses[i].header.frame_id.c_str()) + 1];
      strcpy(out_msg.poses[i].header.frame_id, msg->poses[i].header.frame_id.c_str());

      out_msg.poses[i].pose.position.x = msg->poses[i].pose.position.x;
      out_msg.poses[i].pose.position.y = msg->poses[i].pose.position.y;
      out_msg.poses[i].pose.position.z = msg->poses[i].pose.position.z;

      out_msg.poses[i].pose.orientation.x = msg->poses[i].pose.orientation.x;
      out_msg.poses[i].pose.orientation.y = msg->poses[i].pose.orientation.y;
      out_msg.poses[i].pose.orientation.z = msg->poses[i].pose.orientation.z;
      out_msg.poses[i].pose.orientation.w = msg->poses[i].pose.orientation.w;
    }

  p->Publish(out_msg);

  if (out_msg.poses != 0)
    {
      for (unsigned int i = 0; i < out_msg.poses_length; i++)
        delete [] out_msg.poses[i].header.frame_id;
      delete [] out_msg.poses;
    }
  out_msg.poses = 0;
}

#include <ipc_bridge/publisher.h>

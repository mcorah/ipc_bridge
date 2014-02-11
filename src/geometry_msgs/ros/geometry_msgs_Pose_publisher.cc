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

#include <geometry_msgs/Pose.h>
#include <ipc_bridge/msgs/geometry_msgs_Pose.h>

#define NAMESPACE geometry_msgs
#define NAME Pose

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{
  out_msg.position.x = msg->position.x;
  out_msg.position.y = msg->position.y;
  out_msg.position.z = msg->position.z;

  out_msg.orientation.x = msg->orientation.x;
  out_msg.orientation.y = msg->orientation.y;
  out_msg.orientation.z = msg->orientation.z;
  out_msg.orientation.w = msg->orientation.w;

  p->Publish(out_msg);
}

#include <ipc_bridge/publisher.h>

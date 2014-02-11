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

#include <geometry_msgs/Twist.h>
#include <ipc_bridge/msgs/geometry_msgs_Twist.h>

#define NAMESPACE geometry_msgs
#define NAME Twist

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{
  out_msg.linear.x = msg->linear.x;
  out_msg.linear.y = msg->linear.y;
  out_msg.linear.z = msg->linear.z;

  out_msg.angular.x = msg->angular.x;
  out_msg.angular.y = msg->angular.y;
  out_msg.angular.z = msg->angular.z;

  p->Publish(out_msg);
}

#include <ipc_bridge/publisher.h>

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

#include <sensor_msgs/Imu.h>
#include <ipc_bridge/msgs/sensor_msgs_Imu.h>

#define NAMESPACE sensor_msgs
#define NAME Imu

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

unsigned int prior_size = 0;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{
  out_msg.header.seq = msg->header.seq;
  out_msg.header.stamp = msg->header.stamp.toSec();

  if (strlen(msg->header.frame_id.c_str()) != prior_size)
    {
      if (out_msg.header.frame_id != 0)
        delete[] out_msg.header.frame_id;

      out_msg.header.frame_id =
        new char[strlen(msg->header.frame_id.c_str()) + 1];
      strcpy(out_msg.header.frame_id, msg->header.frame_id.c_str());
      prior_size = strlen(msg->header.frame_id.c_str());
    }

  out_msg.orientation.x = msg->orientation.x;
  out_msg.orientation.y = msg->orientation.y;
  out_msg.orientation.z = msg->orientation.z;
  out_msg.orientation.w = msg->orientation.w;

  out_msg.angular_velocity.x = msg->angular_velocity.x;
  out_msg.angular_velocity.y = msg->angular_velocity.y;
  out_msg.angular_velocity.z = msg->angular_velocity.z;

  out_msg.linear_acceleration.x = msg->linear_acceleration.x;
  out_msg.linear_acceleration.y = msg->linear_acceleration.y;
  out_msg.linear_acceleration.z = msg->linear_acceleration.z;

  std::copy(msg->orientation_covariance.begin(),
            msg->orientation_covariance.end(),
            out_msg.orientation_covariance);

  std::copy(msg->angular_velocity_covariance.begin(),
            msg->angular_velocity_covariance.end(),
            out_msg.angular_velocity_covariance);

  std::copy(msg->linear_acceleration_covariance.begin(),
            msg->linear_acceleration_covariance.end(),
            out_msg.linear_acceleration_covariance);

  p->Publish(out_msg);
}

#include <ipc_bridge/publisher.h>

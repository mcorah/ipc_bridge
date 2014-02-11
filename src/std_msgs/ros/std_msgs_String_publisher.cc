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

#include <std_msgs/String.h>
#include <ipc_bridge/msgs/std_msgs_String.h>

#define NAMESPACE std_msgs
#define NAME String

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

unsigned int data_prior_size = 0;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{
  if (strlen(msg->data.c_str()) != data_prior_size)
    {
      if (out_msg.data != 0)
        delete[] out_msg.data;

      out_msg.data = new char[strlen(msg->data.c_str()) + 1];
      strcpy(out_msg.data, msg->data.c_str());
      data_prior_size = strlen(msg->data.c_str());
    }

  p->Publish(out_msg);
}

#include <ipc_bridge/publisher.h>

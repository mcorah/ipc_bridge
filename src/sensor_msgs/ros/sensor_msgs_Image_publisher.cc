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

#include <sensor_msgs/Image.h>
#include <ipc_bridge/msgs/sensor_msgs_Image.h>

#define NAMESPACE sensor_msgs
#define NAME Image

ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME> *p;
ipc_bridge::NAMESPACE::NAME out_msg;

unsigned int data_prior_length = 0;
unsigned int frame_id_prior_length = 0;
unsigned int encoding_prior_length = 0;

void callback(const NAMESPACE::NAME::ConstPtr &msg)
{
  out_msg.header.seq = msg->header.seq;
  out_msg.header.stamp = msg->header.stamp.toSec();
  if (strlen(msg->header.frame_id.c_str()) != frame_id_prior_length)
    {
      delete[] out_msg.header.frame_id;
      out_msg.header.frame_id =
        new char[strlen(msg->header.frame_id.c_str()) + 1];
      frame_id_prior_length = strlen(msg->header.frame_id.c_str());
    }
  strcpy(out_msg.header.frame_id, msg->header.frame_id.c_str());

  out_msg.height = msg->height;
  out_msg.width = msg->width;
  if (strlen(msg->encoding.c_str()) != encoding_prior_length)
    {
      delete[] out_msg.encoding;
      out_msg.encoding =
        new char[strlen(msg->encoding.c_str()) + 1];
      encoding_prior_length = strlen(msg->encoding.c_str());
    }
  strcpy(out_msg.encoding, msg->encoding.c_str());
  out_msg.is_bigendian = msg->is_bigendian;
  out_msg.step = msg->step;
  out_msg.data_length = msg->data.size();
  if (out_msg.data_length > 0)
    {
      if (out_msg.data_length != data_prior_length)
        {
          delete[] out_msg.data;
          out_msg.data = new unsigned char[out_msg.data_length];
          data_prior_length = out_msg.data_length;
        }
      std::copy(msg->data.begin(), msg->data.end(), out_msg.data);
    }

  p->Publish(out_msg);
}

#include <ipc_bridge/publisher.h>

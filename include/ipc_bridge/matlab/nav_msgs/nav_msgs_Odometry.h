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
#ifndef IPC_BRIDGE_MATLAB_NAV_MSGS_ODOMETRY
#define IPC_BRIDGE_MATLAB_NAV_MSGS_ODOMETRY
#include <ipc_bridge/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/nav_msgs_Odometry.h>

#include <ipc_bridge/matlab/rosgraph_msgs/rosgraph_msgs_Header.h>
#include <ipc_bridge/matlab/geometry_msgs/geometry_msgs_PoseWithCovariance.h>
#include <ipc_bridge/matlab/geometry_msgs/geometry_msgs_TwistWithCovariance.h>

namespace ipc_bridge_matlab
{
  namespace nav_msgs
  {
    namespace Odometry
    {
      static mxArray* ProcessMessage(const ipc_bridge::nav_msgs::Odometry &msg)
      {
        const char *fields[] = {"header",
                                "child_frame_id",
                                "pose",
                                "twist"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        mxSetField(out, 0, "header",
                   ipc_bridge_matlab::Header::ProcessMessage(msg.header));

      if (msg.child_frame_id == 0)
        {
          char buf[1] = "";
          mxSetField(out, 0, "child_frame_id", mxCreateString(buf));
        }
      else
        {
          char buf[strlen(msg.child_frame_id) + 1];
          strcpy(buf, msg.child_frame_id);
          mxSetField(out, 0, "child_frame_id", mxCreateString(buf));
        }

        mxSetField(out, 0, "pose",
                   ipc_bridge_matlab::geometry_msgs::PoseWithCovariance::ProcessMessage(msg.pose));
        mxSetField(out, 0, "twist",
                   ipc_bridge_matlab::geometry_msgs::TwistWithCovariance::ProcessMessage(msg.twist));

        return out;
      }

      static int ProcessArray(const mxArray *a,
                              ipc_bridge::nav_msgs::Odometry &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "header");
        ipc_bridge_matlab::Header::ProcessArray(field, msg.header);

        field = mxGetField(a, 0, "child_frame_id");

        int buflen = 128;
        char buf[buflen];
        mxGetString(field, buf, buflen);
        if (strlen(buf) > 0)
          {
            msg.child_frame_id = new char[strlen(buf) + 1];
            strcpy(msg.child_frame_id, buf);
          }

        field = mxGetField(a, 0, "pose");
        ipc_bridge_matlab::geometry_msgs::PoseWithCovariance::ProcessArray(field,
                                                                        msg.pose);

        field = mxGetField(a, 0, "twist");
        ipc_bridge_matlab::geometry_msgs::TwistWithCovariance::ProcessArray(field,
                                                                         msg.twist);

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::nav_msgs::Odometry &msg)
      {
        ipc_bridge_matlab::Header::Cleanup(msg.header);
        ipc_bridge_matlab::geometry_msgs::PoseWithCovariance::Cleanup(msg.pose);
        ipc_bridge_matlab::geometry_msgs::TwistWithCovariance::Cleanup(msg.twist);
        if (msg.child_frame_id != 0)
          {
            delete[] msg.child_frame_id;
            msg.child_frame_id = 0;
          }
      }
    }
  }
}
#endif

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
#ifndef IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_POSE
#define IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_POSE
#include <ipc_bridge/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/geometry_msgs_Pose.h>

#include <ipc_bridge/matlab/geometry_msgs/geometry_msgs_Point.h>
#include <ipc_bridge/matlab/geometry_msgs/geometry_msgs_Quaternion.h>

namespace ipc_bridge_matlab
{
  namespace geometry_msgs
  {
    namespace Pose
    {
      static mxArray* ProcessMessage(const ipc_bridge::geometry_msgs::Pose &msg)
      {
        const char *fields[] = {"position", "orientation"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        mxSetField(out, 0, "position",
                   ipc_bridge_matlab::geometry_msgs::Point::ProcessMessage(msg.position));
        mxSetField(out, 0, "orientation",
                   ipc_bridge_matlab::geometry_msgs::Quaternion::ProcessMessage(msg.orientation));

        return out;
      }

      static int ProcessArray(const mxArray *a, ipc_bridge::geometry_msgs::Pose &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "position");
        ipc_bridge_matlab::geometry_msgs::Point::ProcessArray(field, msg.position);

        field = mxGetField(a, 0, "orientation");
        ipc_bridge_matlab::geometry_msgs::Quaternion::ProcessArray(field, msg.orientation);

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::geometry_msgs::Pose &msg)
      {
        ipc_bridge_matlab::geometry_msgs::Point::Cleanup(msg.position);
        ipc_bridge_matlab::geometry_msgs::Quaternion::Cleanup(msg.orientation);
      }
    }
  }
}
#endif

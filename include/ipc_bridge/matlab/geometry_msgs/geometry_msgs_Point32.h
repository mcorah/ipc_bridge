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
#ifndef IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_POINT32
#define IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_POINT32
#include <ipc_bridge/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/geometry_msgs_Point32.h>

namespace ipc_bridge_matlab
{
  namespace geometry_msgs
  {
    namespace Point32
    {
      static mxArray* ProcessMessage(const ipc_bridge::geometry_msgs::Point32 &msg)
      {
        const char *fields[] = {"x", "y", "z"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        mxSetField(out, 0, "x", mxCreateDoubleScalar(msg.x));
        mxSetField(out, 0, "y", mxCreateDoubleScalar(msg.y));
        mxSetField(out, 0, "z", mxCreateDoubleScalar(msg.z));

        return out;
      }

      static int ProcessArray(const mxArray *a, ipc_bridge::geometry_msgs::Point32 &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "x");
        msg.x = mxGetScalar(field);

        field = mxGetField(a, 0, "y");
        msg.y = mxGetScalar(field);

        field = mxGetField(a, 0, "z");
        msg.z = mxGetScalar(field);

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::geometry_msgs::Point32 &msg)
      {
        return;
      }
    }
  }
}
#endif

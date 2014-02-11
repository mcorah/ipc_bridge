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
#ifndef IPC_BRIDGE_MATLAB_NAV_MSGS_MAP_META_DATA
#define IPC_BRIDGE_MATLAB_NAV_MSGS_MAP_META_DATA
#include <ipc_bridge/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/nav_msgs_MapMetaData.h>

#include <ipc_bridge/matlab/geometry_msgs/geometry_msgs_Pose.h>

namespace ipc_bridge_matlab
{
  namespace nav_msgs
  {
    namespace MapMetaData
    {
      static mxArray* ProcessMessage(const ipc_bridge::nav_msgs::MapMetaData &msg)
      {
        const char *fields[] = {"map_load_time",
                                "resolution",
                                "width",
                                "height",
                                "origin"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        mxSetField(out, 0, "map_load_time", mxCreateDoubleScalar(msg.map_load_time));
        mxSetField(out, 0, "resolution", mxCreateDoubleScalar(msg.resolution));
        mxSetField(out, 0, "width", mxCreateDoubleScalar(msg.width));
        mxSetField(out, 0, "height", mxCreateDoubleScalar(msg.height));
        mxSetField(out, 0, "origin",
                   ipc_bridge_matlab::geometry_msgs::Pose::ProcessMessage(msg.origin));

        return out;
      }

      static int ProcessArray(const mxArray *a,
                              ipc_bridge::nav_msgs::MapMetaData &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "map_load_time");
        msg.map_load_time = mxGetScalar(field);

        field = mxGetField(a, 0, "resolution");
        msg.resolution = mxGetScalar(field);

        field = mxGetField(a, 0, "width");
        msg.width = mxGetScalar(field);

        field = mxGetField(a, 0, "height");
        msg.height = mxGetScalar(field);

        field = mxGetField(a, 0, "origin");
        ipc_bridge_matlab::geometry_msgs::Pose::ProcessArray(field, msg.origin);

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::nav_msgs::MapMetaData &msg)
      {
        ipc_bridge_matlab::geometry_msgs::Pose::Cleanup(msg.origin);
      }
    }
  }
}
#endif

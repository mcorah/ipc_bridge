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
#ifndef IPC_BRIDGE_MATLAB_SENSOR_MSGS_POINT_CLOUD
#define IPC_BRIDGE_MATLAB_SENSOR_MSGS_POINT_CLOUD
#include <ipc_bridge/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/sensor_msgs_PointCloud.h>

#include <ipc_bridge/matlab/rosgraph_msgs/rosgraph_msgs_Header.h>
#include <ipc_bridge/matlab/geometry_msgs/geometry_msgs_Point32.h>

namespace ipc_bridge_matlab
{
  namespace sensor_msgs
  {
    namespace PointCloud
    {
      static mxArray* ProcessMessage(const ipc_bridge::sensor_msgs::PointCloud &msg)
      {
        const char *fields[] = {"header",
                                "points"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        mxSetField(out, 0, "header",
                   ipc_bridge_matlab::Header::ProcessMessage(msg.header));

        const int length = msg.points_length;
        mxArray *points = mxCreateCellArray(1, &length);
        for (unsigned int i = 0; i < length; i++)
          mxSetCell(points, i,
                    ipc_bridge_matlab::geometry_msgs::Point32::ProcessMessage(msg.points[i]));
        mxSetField(out, 0, "points", points);

        return out;
      }

      static int ProcessArray(const mxArray *a, ipc_bridge::sensor_msgs::PointCloud &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "header");
        ipc_bridge_matlab::Header::ProcessArray(field, msg.header);

        field = mxGetField(a, 0, "points");
        int nrows = mxGetM(field);
        int ncols = mxGetN(field);

        unsigned int length = nrows;
        if (nrows < ncols)
          length = ncols;
        msg.points_length = length;

        if ((ncols == 0) || (nrows == 0))
          {
            msg.points_length = 0;
            msg.points = 0;
          }

        if (msg.points_length > 0)
          {
            msg.points = new geometry_msgs_Point32[msg.points_length];
            for (unsigned int i = 0; i < msg.points_length; i++)
              {
                mxArray *p = mxGetCell(field, i);
                ipc_bridge_matlab::geometry_msgs::Point32::ProcessArray(p, msg.points[i]);
              }
          }

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::sensor_msgs::PointCloud &msg)
      {
        ipc_bridge_matlab::Header::Cleanup(msg.header);

        for (unsigned int i = 0; i < msg.points_length; i++)
          ipc_bridge_matlab::geometry_msgs::Point32::Cleanup(msg.points[i]);
        if (msg.points != 0)
          {
            delete[] msg.points;
            msg.points_length = 0;
            msg.points = 0;
          }
      }
    }
  }
}
#endif

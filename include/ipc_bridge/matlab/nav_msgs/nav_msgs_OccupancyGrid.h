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
#ifndef IPC_BRIDGE_MATLAB_NAV_MSGS_OCCUPANCY_GRID
#define IPC_BRIDGE_MATLAB_NAV_MSGS_OCCUPANCY_GRID
#include <ipc_bridge/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/nav_msgs_OccupancyGrid.h>

#include <ipc_bridge/matlab/rosgraph_msgs/rosgraph_msgs_Header.h>
#include <ipc_bridge/matlab/nav_msgs/nav_msgs_MapMetaData.h>

namespace ipc_bridge_matlab
{
  namespace nav_msgs
  {
    namespace OccupancyGrid
    {
      static mxArray* ProcessMessage(const ipc_bridge::nav_msgs::OccupancyGrid &msg)
      {
        const char *fields[] = {"header",
                                "info",
                                "data"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        mxSetField(out, 0, "header",
                   ipc_bridge_matlab::Header::ProcessMessage(msg.header));
        mxSetField(out, 0, "info",
                   ipc_bridge_matlab::nav_msgs::MapMetaData::ProcessMessage(msg.info));

        int length = msg.data_length;
        mxArray *data = mxCreateDoubleMatrix(1, length, mxREAL);
        double *p = mxGetPr(data);
        for (int i = 0; i < length; i++)
          p[i] = (double)msg.data[i];
        mxSetField(out, 0, "data", data);

        return out;
      }

      static int ProcessArray(const mxArray *a,
                              ipc_bridge::nav_msgs::OccupancyGrid &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "header");
        ipc_bridge_matlab::Header::ProcessArray(field, msg.header);

        field = mxGetField(a, 0, "info");
        ipc_bridge_matlab::nav_msgs::MapMetaData::ProcessArray(field, msg.info);

        field = mxGetField(a, 0, "data");
        int nrows = mxGetM(field);
        int ncols = mxGetN(field);

        unsigned int length = nrows;
        if (nrows < ncols)
          length = ncols;
        msg.data_length = length;

        if ((ncols == 0) || (nrows == 0))
          {
            msg.data_length = 0;
            msg.data = 0;
          }

        if (msg.data_length > 0)
          {
            double *p = mxGetPr(field);
            msg.data = new char[msg.data_length];
            for (unsigned int i = 0; i < msg.data_length; i++)
              msg.data[i] = (char)p[i];
          }

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::nav_msgs::OccupancyGrid &msg)
      {
        ipc_bridge_matlab::Header::Cleanup(msg.header);
        ipc_bridge_matlab::nav_msgs::MapMetaData::Cleanup(msg.info);
        if (msg.data != 0)
          {
            delete[] msg.data;
            msg.data_length = 0;
            msg.data = 0;
          }
      }
    }
  }
}
#endif

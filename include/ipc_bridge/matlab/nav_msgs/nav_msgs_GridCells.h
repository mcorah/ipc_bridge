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
#ifndef IPC_BRIDGE_MATLAB_NAV_MSGS_GRID_CELLS
#define IPC_BRIDGE_MATLAB_NAV_MSGS_GRID_CELLS
#include <ipc_bridge/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/nav_msgs_GridCells.h>

#include <ipc_bridge/matlab/rosgraph_msgs/rosgraph_msgs_Header.h>
#include <ipc_bridge/matlab/geometry_msgs/geometry_msgs_Point.h>

namespace ipc_bridge_matlab
{
  namespace nav_msgs
  {
    namespace GridCells
    {
      static mxArray* ProcessMessage(const ipc_bridge::nav_msgs::GridCells &msg)
      {
        const char *fields[] = {"header", "cell_width", "cell_height", "cells"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        mxSetField(out, 0, "header",
                   ipc_bridge_matlab::Header::ProcessMessage(msg.header));
        mxSetField(out, 0, "cell_width", mxCreateDoubleScalar(msg.cell_width));
        mxSetField(out, 0, "cell_height", mxCreateDoubleScalar(msg.cell_height));

        const int length = msg.cells_length;
        mxArray *cells = mxCreateCellArray(1, &length);
        for (int i = 0; i < length; i++)
          mxSetCell(cells, i,
                    ipc_bridge_matlab::geometry_msgs::Point::ProcessMessage(msg.cells[i]));
        mxSetField(out, 0, "cells", cells);

        return out;
      }

      static int ProcessArray(const mxArray *a,
                              ipc_bridge::nav_msgs::GridCells &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "header");
        ipc_bridge_matlab::Header::ProcessArray(field, msg.header);

        field = mxGetField(a, 0, "cell_width");
        msg.cell_width = mxGetScalar(field);

        field = mxGetField(a, 0, "cell_height");
        msg.cell_height = mxGetScalar(field);

        field = mxGetField(a, 0, "cells");
        int nrows = mxGetM(field);
        int ncols = mxGetN(field);

        unsigned int length = nrows;
        if (nrows < ncols)
          length = ncols;
        msg.cells_length = length;

        if ((ncols == 0) || (nrows == 0))
          {
            msg.cells_length = 0;
            msg.cells = 0;
          }

        if (msg.cells_length > 0)
          {
            msg.cells = new geometry_msgs_Point[msg.cells_length];
            for (unsigned int i = 0; i < msg.cells_length; i++)
              {
                mxArray *p = mxGetCell(field, i);
                ipc_bridge_matlab::geometry_msgs::Point::ProcessArray(p, msg.cells[i]);
              }
          }

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::nav_msgs::GridCells &msg)
      {
        ipc_bridge_matlab::Header::Cleanup(msg.header);
        for (unsigned int i = 0; i < msg.cells_length; i++)
          ipc_bridge_matlab::geometry_msgs::Point::Cleanup(msg.cells[i]);
        if (msg.cells != 0)
          {
            delete[] msg.cells;
            msg.cells_length = 0;
            msg.cells = 0;
          }
      }
    }
  }
}
#endif

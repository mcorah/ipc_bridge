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
#ifndef IPC_BRIDGE_MATLAB_STD_MSGS_EMPTY
#define IPC_BRIDGE_MATLAB_STD_MSGS_EMPTY
#include <ipc_bridge/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/std_msgs_Empty.h>

namespace ipc_bridge_matlab
{
  namespace std_msgs
  {
    namespace Empty
    {
      static mxArray* ProcessMessage(const ipc_bridge::std_msgs::Empty &msg)
      {
        const char *fields[] = {"empty"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        int d = 0;

        mxSetField(out, 0, "empty", mxCreateDoubleScalar(d));

        return out;
      }

      static int ProcessArray(const mxArray *a, ipc_bridge::std_msgs::Empty &msg)
      {
        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::std_msgs::Empty &msg)
      {
      }
    }
  }
}
#endif

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
#ifndef IPC_BRIDGE_MATLAB_ROSLIB_HEADER
#define IPC_BRIDGE_MATLAB_ROSLIB_HEADER
#include <ipc_bridge/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/rosgraph_msgs_Header.h>

namespace ipc_bridge_matlab
{
  namespace Header
  {
    static mxArray* ProcessMessage(const ipc_bridge::Header &msg)
    {
      const char *fields[] = {"seq",
                              "stamp",
                              "frame_id"};
      const int nfields = sizeof(fields)/sizeof(*fields);
      mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

      mxSetField(out, 0, "seq", mxCreateDoubleScalar(msg.seq));
      mxSetField(out, 0, "stamp", mxCreateDoubleScalar(msg.stamp));

      if (msg.frame_id == 0)
        {
          char buf[1] = {'\0'};
          mxSetField(out, 0, "frame_id", mxCreateString(buf));
        }
      else
        {
          char buf[strlen(msg.frame_id) + 1];
          strcpy(buf, msg.frame_id);
          mxSetField(out, 0, "frame_id", mxCreateString(buf));
        }

      return out;
    }

    static int ProcessArray(const mxArray *a, ipc_bridge::Header &msg)
    {
      mxArray *field;

      field = mxGetField(a, 0, "seq");
      msg.seq = mxGetScalar(field);

      field = mxGetField(a, 0, "stamp");
      msg.stamp = mxGetScalar(field);

      field = mxGetField(a, 0, "frame_id");

      int buflen = 128;
      char buf[buflen];
      mxGetString(field, buf, buflen);
      if (strlen(buf) > 0)
        {
          msg.frame_id = new char[strlen(buf) + 1];
          strcpy(msg.frame_id, buf);
        }
      else
        {
          msg.frame_id = new char[1];
          msg.frame_id[0] = '\0';
        }

      return SUCCESS;
    }

    static void Cleanup(ipc_bridge::Header &msg)
    {
      if (msg.frame_id != 0)
        {
          delete[] msg.frame_id;
          msg.frame_id = 0;
        }
    }
  }
}
#endif

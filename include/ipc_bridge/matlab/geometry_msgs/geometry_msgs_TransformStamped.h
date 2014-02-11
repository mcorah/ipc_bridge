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
#ifndef IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_TRANSFORM_STAMPED
#define IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_TRANSFORM_STAMPED
#include <ipc_bridge/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/geometry_msgs_TransformStamped.h>

#include <ipc_bridge/matlab/rosgraph_msgs/rosgraph_msgs_Header.h>
#include <ipc_bridge/matlab/geometry_msgs/geometry_msgs_Transform.h>

namespace ipc_bridge_matlab
{
  namespace geometry_msgs
  {
    namespace TransformStamped
    {
      static mxArray* ProcessMessage(const ipc_bridge::geometry_msgs::TransformStamped &msg)
      {
        const char *fields[] = {"header", "child_frame_id", "transform"};
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

        mxSetField(out, 0, "transform",
                   ipc_bridge_matlab::geometry_msgs::Transform::ProcessMessage(msg.transform));

        return out;
      }

      static int ProcessArray(const mxArray *a,
                              ipc_bridge::geometry_msgs::TransformStamped &msg)
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

        field = mxGetField(a, 0, "transform");
        ipc_bridge_matlab::geometry_msgs::Transform::ProcessArray(field, msg.transform);

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::geometry_msgs::TransformStamped &msg)
      {
        ipc_bridge_matlab::Header::Cleanup(msg.header);
        if (msg.child_frame_id != 0)
          {
            delete[] msg.child_frame_id;
            msg.child_frame_id = 0;
          }
        ipc_bridge_matlab::geometry_msgs::Transform::Cleanup(msg.transform);
      }
    }
  }
}
#endif

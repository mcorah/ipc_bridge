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
#ifndef IPC_BRIDGE_MATLAB_SENSOR_MSGS_IMU
#define IPC_BRIDGE_MATLAB_SENSOR_MSGS_IMU
#include <ipc_bridge/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/sensor_msgs_Imu.h>

#include <ipc_bridge/matlab/rosgraph_msgs/rosgraph_msgs_Header.h>
#include <ipc_bridge/matlab/geometry_msgs/geometry_msgs_Quaternion.h>
#include <ipc_bridge/matlab/geometry_msgs/geometry_msgs_Vector3.h>

namespace ipc_bridge_matlab
{
  namespace sensor_msgs
  {
    namespace Imu
    {
      static mxArray* ProcessMessage(const ipc_bridge::sensor_msgs::Imu &msg)
      {
        const char *fields[] = {"header",
                                "orientation",
                                "orientation_covariance",
                                "angular_velocity",
                                "angular_velocity_covariance",
                                "linear_acceleration",
                                "linear_acceleration_covariance"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);

        mxSetField(out, 0, "header",
                   ipc_bridge_matlab::Header::ProcessMessage(msg.header));
        mxSetField(out, 0, "orientation",
                   ipc_bridge_matlab::geometry_msgs::Quaternion::ProcessMessage(msg.orientation));

        mxArray *orientation_covariance = mxCreateDoubleMatrix(1, 9, mxREAL);
        std::copy(msg.orientation_covariance, msg.orientation_covariance + 9,
                  mxGetPr(orientation_covariance));
        mxSetField(out, 0, "orientation_covariance", orientation_covariance);

        mxSetField(out, 0, "angular_velocity",
                   ipc_bridge_matlab::geometry_msgs::Vector3::ProcessMessage(msg.angular_velocity));

        mxArray *angular_velocity_covariance = mxCreateDoubleMatrix(1, 9, mxREAL);
        std::copy(msg.angular_velocity_covariance, msg.angular_velocity_covariance + 9,
                  mxGetPr(angular_velocity_covariance));
        mxSetField(out, 0, "angular_velocity_covariance", angular_velocity_covariance);


        mxSetField(out, 0, "linear_acceleration",
                   ipc_bridge_matlab::geometry_msgs::Vector3::ProcessMessage(msg.linear_acceleration));

        mxArray *linear_acceleration_covariance = mxCreateDoubleMatrix(1, 9, mxREAL);
        std::copy(msg.linear_acceleration_covariance, msg.linear_acceleration_covariance + 9,
                  mxGetPr(linear_acceleration_covariance));
        mxSetField(out, 0, "linear_acceleration_covariance", linear_acceleration_covariance);

        return out;
      }

      static int ProcessArray(const mxArray *a, ipc_bridge::sensor_msgs::Imu &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "header");
        ipc_bridge_matlab::Header::ProcessArray(field, msg.header);

        field = mxGetField(a, 0, "orientation");
        ipc_bridge_matlab::geometry_msgs::Quaternion::ProcessArray(field, msg.orientation);

        field = mxGetField(a, 0, "orientation_covariance");
        ipc_bridge_matlab::GetDoubleArray(field, 9, msg.orientation_covariance);

        field = mxGetField(a, 0, "angular_velocity");
        ipc_bridge_matlab::geometry_msgs::Vector3::ProcessArray(field, msg.angular_velocity);

        field = mxGetField(a, 0, "angular_velocity_covariance");
        ipc_bridge_matlab::GetDoubleArray(field, 9, msg.angular_velocity_covariance);

        field = mxGetField(a, 0, "linear_acceleration");
        ipc_bridge_matlab::geometry_msgs::Vector3::ProcessArray(field, msg.linear_acceleration);

        field = mxGetField(a, 0, "linear_acceleration_covariance");
        ipc_bridge_matlab::GetDoubleArray(field, 9, msg.linear_acceleration_covariance);

        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::sensor_msgs::Imu &msg)
      {
        ipc_bridge_matlab::Header::Cleanup(msg.header);
        ipc_bridge_matlab::geometry_msgs::Quaternion::Cleanup(msg.orientation);
        ipc_bridge_matlab::geometry_msgs::Vector3::Cleanup(msg.angular_velocity);
        ipc_bridge_matlab::geometry_msgs::Vector3::Cleanup(msg.linear_acceleration);
      }
    }
  }
}
#endif

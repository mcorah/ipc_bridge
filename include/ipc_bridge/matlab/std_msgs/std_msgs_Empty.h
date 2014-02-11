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

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
#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

int main(int argc, char** argv)
{
  ros::init(argc, argv, STR(NAMESPACE)"_"STR(NAME)"_publisher");
  ros::NodeHandle n("~");

  std::string message_name;
  if (!n.hasParam("message"))
  {
    ROS_ERROR("%s: missing required parameter 'message'",
              ros::this_node::getName().c_str());
    return EXIT_FAILURE;
  }
  n.getParam("message", message_name);

  std::string server_name;
  n.param("server", server_name, std::string("localhost"));

  ros::Subscriber sub = n.subscribe("topic", 10, callback, ros::TransportHints().tcpNoDelay());

  p = new ipc_bridge::Publisher<ipc_bridge::NAMESPACE::NAME>(ros::this_node::getName(),
                                                             message_name,
                                                             server_name);

  if (p->Connect() != 0)
    {
      ROS_ERROR("%s: failed to connect to message %s:%s",
                ros::this_node::getName().c_str(),
                server_name.c_str(),
                message_name.c_str());
      return EXIT_FAILURE;
    }
  else
    {
      ROS_DEBUG("%s: connected to message %s:%s",
                ros::this_node::getName().c_str(),
                server_name.c_str(),
                message_name.c_str());
    }

  ros::spin();

  p->Disconnect();

  return EXIT_SUCCESS;
}

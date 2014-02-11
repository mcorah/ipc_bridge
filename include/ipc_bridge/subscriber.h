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
  ros::init(argc, argv, STR(NAMESPACE)"_"STR(NAME)"_subscriber");
  ros::NodeHandle n("~");

  std::string message_name;
  n.param("message", message_name, std::string("message"));

  pub = n.advertise<NAMESPACE::NAME>("topic", 100);

  ipc_bridge::Subscriber<ipc_bridge::NAMESPACE::NAME> s(ros::this_node::getName(), 
                                                        message_name,
                                                        callback);
  if (s.Connect() != 0)
    {
      ROS_ERROR("%s: failed to connect to message %s", 
                ros::this_node::getName().c_str(), 
                message_name.c_str());
      return -1;
    }
  else
    {
      ROS_DEBUG("%s: connected to message %s", 
                ros::this_node::getName().c_str(), 
                message_name.c_str());
    }

  while (n.ok())
    s.Listen(2);

  s.Disconnect();

  return 0;
}

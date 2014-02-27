# ipc\_bridge:

ipc\_bridge is an interface between ROS and MATLAB via IPC.

## Prerequisites:

- Install IPC (v.3.9.1+) [link](http://www.cs.cmu.edu/~ipc/)
- Install ROS (hydro+) [link](http://wiki.ros.org/hydro/Installation/)

## Installation:

* We must start with a [dry](http://wiki.ros.org/catkin/migrating_from_rosbuild) workspace (i.e., ```~/ws/dry```). If one does not exist:

```sh
mkdir -p ~/ws/dry
cd ~/ws/dry
wstool init src
```

* Install the ipc\_bridge package using wstool and catkin\_make\_isolated:
```sh
cd ~/ws/dry
wstool set -t src ipc_bridge https://github.com/nmichael/ipc_bridge.git --git --version=develop
wstool update -t src ipc_bridge
catkin_make_isolated --install --pkg ipc_bridge
```

### Local package messages:

Given a ROS package with messages defined locally (e.g., in the example_package/msg folder), to add support:
+ Create the directory structure:
```mkdir -p example_package/ipc/{mex,xdr,ros,include/ipc_bridge/matlab}```
+ Add the following to the example_package CMakeLists.txt file:
```cmake
find_package(ipc_bridge)
if(ipc_bridge_FOUND)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${ipc_bridge_MODULE_PATH}")
  find_package(IPC REQUIRED)
  find_package(Matlab REQUIRED COMPONENTS mex)
  find_package(catkin REQUIRED roscpp)

  include_directories(
    ${IPC_INCLUDE_DIR}
    ${ipc_bridge_INCLUDE_DIR}
  )

  set(IPC_MATLAB_CFLAGS "-I${CMAKE_CURRENT_LIST_DIR}/ipc/include")
  add_custom_target(generate_xdr_headers)
  add_subdirectory("ipc")

  install(DIRECTORY ipc/include/ipc_bridge/
    DESTINATION include/ipc_bridge
    FILES_MATCHING PATTERN "*.h"
    PATTERN ".svn" EXCLUDE
    )
endif(ipc_bridge_FOUND)
```
+ Add a file example_package/ipc/CMakeLists.txt that contains only ```generate_ipc_messages()```
+ Add the local content as follows:
  * ipc/xdr: XDR serialization definition for ROS message
  * ipc/ros: publisher,subscriber marshalling ROS <-> IPC
  * ipc/mex: boilerplate mex implementation file
  * ipc/include/ipc_bridge/matlab: MATLAB <-> IPC marshalling

## Installation Notes:

### IPC:

* IPC does not install to a specific location. A convention that works is to install as follows:
```sh
/opt/ipc/include/ipc.h
/opt/ipc/bin/central
/opt/ipc/bin/xdrgen
/opt/ipc/lib/libipc.a
```
Don't forget to set your path:
```sh
export PATH=${PATH}:/opt/ipc/bin
```

### Ubuntu:

* An old FindMatlab.cmake file resides in /usr/share/cmake-2.8/Modules. I moved this elsewhere so that the one distributed with the package is used. This step may be unnecessary.
* Matlab mex compilation outputs an error requiring '-fPIC' to be passed during IPC compilation. Modify CFLAGS line 371 of ipc-3.9.1/etc/GNUmakefile.defs as follows:

```$(CFLAGSM_$(DBMALLOC)) $(CFLAGS_EXT)``` -> ```$(CFLAGSM_$(DBMALLOC)) $(CFLAGS_EXT) -fPIC```

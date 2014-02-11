# ipc\_bridge:

ipc\_bridge is an interface between ROS and MATLAB via IPC.

## Prerequisites:

- Install IPC (v.3.9.1+) [link](http://www.cs.cmu.edu/~ipc/)
- Install ROS (hydro+) [link](http://wiki.ros.org/hydro/Installation/)

## Installation:

* Assuming a [dry](http://wiki.ros.org/catkin/migrating_from_rosbuild) workspace:
```sh
cd ~/ws/dry
wstool set -t src ipc_bridge https://github.com/nmichael/ipc_bridge.git --git --version=develop
wstool update -t src ipc_bridge
catkin_make_isolated --install --pkg ipc_bridge
```

## Installation Notes:

### Ubuntu:

* An old FindMatlab.cmake file resides in /usr/share/cmake-2.8/Modules. I moved this elsewhere so that the one distributed with the package is used. This step may be unnecessary.
* Matlab mex compilation outputs an error requiring '-fPIC' to be passed during IPC compilation. Modify CFLAGS line 371 of ipc-3.9.1/etc/GNUmakefile.defs as follows:

```$(CFLAGSM_$(DBMALLOC)) $(CFLAGS_EXT)``` -> ```$(CFLAGSM_$(DBMALLOC)) $(CFLAGS_EXT) -fPIC```

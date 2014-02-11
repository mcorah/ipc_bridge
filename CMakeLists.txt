cmake_minimum_required(VERSION 2.8.3)
project(ipc_bridge)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(IPCBridgeGenerateMessages)

find_package(IPC REQUIRED)
if(NOT IPC_FOUND)
  message(ERROR "ipc_bridge requires IPC to be installed")
endif()

find_package(Matlab REQUIRED COMPONENTS mex)
if(NOT MATLAB_FOUND)
  message(ERROR "ipc_bridge requires Matlab to be installed")
endif()

find_package(catkin REQUIRED roscpp)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${IPC_INCLUDE_DIR}
)

link_directories(
  ${catkin_LIBRARY_DIRS}
  ${IPC_LIBRARY_DIRS}
)

set(IPC_MATLAB_CFLAGS "-I${CMAKE_CURRENT_LIST_DIR}/include")
add_custom_target(generate_xdr_headers)

add_subdirectory("src/rosgraph_msgs")
add_subdirectory("src/geometry_msgs")
add_subdirectory("src/nav_msgs")
add_subdirectory("src/sensor_msgs")
add_subdirectory("src/std_msgs")

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
  )

install(DIRECTORY cmake/
  DESTINATION share/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.cmake"
  PATTERN ".svn" EXCLUDE
  )

set(ipc_bridge_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include")
set(ipc_bridge_MODULE_PATH "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}")
configure_file(ipc_bridge-config.cmake.in
  "${PROJECT_BINARY_DIR}/InstallFiles/ipc_bridge-config.cmake" @ONLY)
install(FILES
  "${PROJECT_BINARY_DIR}/InstallFiles/ipc_bridge-config.cmake"
  DESTINATION share/${PROJECT_NAME})

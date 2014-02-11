# - Check for the presence of IPC
#
# The following variables are set when IPC is found:
#  IPC_FOUND       = Set to true, if all components of IPC
#                          have been found.
#  IPC_INCLUDE_DIR   = Include path for the header files of IPC
#  IPC_LIBRARIES  = Link these to use IPC

## -----------------------------------------------------------------------------
## Check for the header files

find_path (IPC_INCLUDE_DIR ipc.h
  PATHS ${IPC_INC} /usr/local/include /usr/include /opt/ipc/include /opt/local/include
  )

## -----------------------------------------------------------------------------
## Check for the library

find_library (IPC_LIBRARIES ipc
  PATHS ${IPC_LIB} /usr/local/lib /usr/lib /usr/lib64/ /lib /opt/ipc/lib /opt/local/lib
  )

## -----------------------------------------------------------------------------
## Actions taken when all components have been found

if (IPC_INCLUDE_DIR AND IPC_LIBRARIES)
  set (IPC_FOUND TRUE)
else (IPC_INCLUDE_DIR AND IPC_LIBRARIES)
  if (NOT IPC_FIND_QUIETLY)
    if (NOT IPC_INCLUDE_DIR)
      message (STATUS "Unable to find IPC header files!")
    endif (NOT IPC_INCLUDE_DIR)
    if (NOT IPC_LIBRARIES)
      message (STATUS "Unable to find IPC library files!")
    endif (NOT IPC_LIBRARIES)
  endif (NOT IPC_FIND_QUIETLY)
endif (IPC_INCLUDE_DIR AND IPC_LIBRARIES)

if (IPC_FOUND)
  if (NOT IPC_FIND_QUIETLY)
    message (STATUS "Found components for IPC")
    message (STATUS "IPC_INCLUDE_DIR = ${IPC_INCLUDE_DIR}")
    message (STATUS "IPC_LIBRARIES = ${IPC_LIBRARIES}")
  endif (NOT IPC_FIND_QUIETLY)
else (IPC_FOUND)
  if (IPC_FIND_REQUIRED)
    SET(IPC_LIB "" CACHE PATH "Paths where to additionally look for
    libs")
    SET(IPC_INC "" CACHE PATH "Paths where to additionally look for
    includes")
    message (FATAL_ERROR "Could not find IPC!")
  endif (IPC_FIND_REQUIRED)
endif (IPC_FOUND)

mark_as_advanced (
  IPC_FOUND
  IPC_LIBRARIES
  IPC_INCLUDE_DIR
  )
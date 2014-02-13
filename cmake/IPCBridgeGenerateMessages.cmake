macro(generate_ipc_messages)
  include_directories(
    ${CMAKE_BINARY_DIR}/include
    ${CMAKE_INSTALL_PREFIX}/include
    )

  set(IPC_MATLAB_CFLAGS
    ${IPC_MATLAB_CFLAGS}
    "-I${IPC_INCLUDE_DIR}"
    "-I${CMAKE_INSTALL_PREFIX}/include"
    "-I${CMAKE_BINARY_DIR}/include")

  # Get the XDR files (assumes in xdr directory residing with calling CMakeLists.txt)
  file(GLOB MESSAGES "${CMAKE_CURRENT_SOURCE_DIR}/xdr/*.xdr")
  foreach(MSG ${MESSAGES})
    get_filename_component(MSG_NAME ${MSG} NAME_WE)
    set(xdr_header "${CMAKE_BINARY_DIR}/include/ipc_bridge/msgs/${MSG_NAME}.h")
    add_custom_command(OUTPUT ${xdr_header}
      COMMAND ${CMAKE_COMMAND}
      ARGS -E make_directory "${CMAKE_BINARY_DIR}/include/ipc_bridge/msgs"
      COMMAND ${IPC_XDRGEN}
      ARGS --directives=none ${CMAKE_CURRENT_SOURCE_DIR}/xdr/${MSG_NAME}.xdr ${xdr_header}
      COMMENT "Generating XDR: ${MSG_NAME}"
      VERBATIM
      )
    add_custom_target(${MSG_NAME}_xdrgen_header DEPENDS ${xdr_header})
    add_dependencies(generate_xdr_headers ${MSG_NAME}_xdrgen_header)
  endforeach(MSG)

  # Install the generated files in the global include
  install(DIRECTORY ${CMAKE_BINARY_DIR}/include/ipc_bridge/msgs/
    DESTINATION include/ipc_bridge/msgs
    FILES_MATCHING PATTERN "*.h"
    PATTERN ".svn" EXCLUDE
    )

  # Get the ROS nodes (assumes in ros directory residing with calling CMakeLists.txt)
  set(NODE_TARGETS "")
  file(GLOB NODES_SRC "${CMAKE_CURRENT_SOURCE_DIR}/ros/*.cc")
  foreach(NODE_SRC ${NODES_SRC})
    get_filename_component(NODE_NAME ${NODE_SRC} NAME_WE)
    add_executable(${NODE_NAME} ${NODE_SRC})
    target_link_libraries(${NODE_NAME}
      ${catkin_LIBRARIES}
      ${IPC_LIBRARIES}
      )
    add_dependencies(${NODE_NAME} generate_xdr_headers)
    list(APPEND NODE_TARGETS "${NODE_NAME}")
  endforeach(NODE_SRC)

  if (NODE_TARGETS)
    install(TARGETS ${NODE_TARGETS} RUNTIME DESTINATION lib/ipc_bridge)
  endif(NODE_TARGETS)

  # Get the MEX nodes (assumes in mex directory residing with calling CMakeLists.txt)
  set(MEX_FILES "")
  file(GLOB MEX_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/mex/*.cc")
  foreach(MEX_SRC ${MEX_SRCS})
    get_filename_component(MEX_NAME ${MEX_SRC} NAME_WE)
    set(mex_output "${CMAKE_BINARY_DIR}/lib/${MEX_NAME}.${MATLAB_MEXFILE_EXT}")
    add_custom_command(OUTPUT ${mex_output}
      COMMAND ${CMAKE_COMMAND}
      ARGS -E make_directory "${CMAKE_BINARY_DIR}/lib"
      COMMAND ${MATLAB_ROOT}/bin/mex
      ARGS ${IPC_MATLAB_CFLAGS} ${MEX_SRC} ${IPC_LIBRARIES} -output ${mex_output}
      COMMENT "Building mex: ${MEX_NAME}"
      VERBATIM
      )
    add_custom_target(${MEX_NAME}_mex ALL DEPENDS ${mex_output} generate_xdr_headers)
    list(APPEND MEX_FILES "${mex_output}")
  endforeach(MEX_SRC)

  if (MEX_FILES)
    install(FILES ${MEX_FILES} DESTINATION share/ipc_bridge/matlab)
  endif(MEX_FILES)
endmacro(generate_ipc_messages)

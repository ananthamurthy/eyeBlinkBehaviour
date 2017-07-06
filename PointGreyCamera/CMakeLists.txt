cmake_minimum_required(VERSION 2.8)
project(Blinky)

set( SOCK_PATH "\"/tmp/eye_blink_socket\"" )

# How many bytes should we write to socket in one go.
# This is deprecated. We write whole frame in one go
set( BLOCK_SIZE 4096 )

# NOTICE: Following values are optimized to achive FPS of 100. If you are changing them,
# do it at your own risk. These values replaces macros in config.h.in file in
# PointGrey submodule.
set( FRAME_HEIGHT  512 )
set( FRAME_WIDTH  640)
# Exposure time in micro-seconds")
set( EXPOSURE_TIME_IN_US  2000)
# What frame rate do you want? Camera may not honour this if FPS is higher 
# than its capacity
set( EXPECTED_FPS 200 )

# Write the configuration file.
configure_file( 
    ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h 
    )

set( CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

set( CMAKE_CXX_COMPILER g++ )
set( CMAKE_C_COMPILER g++ )

find_package( OpenCV REQUIRED )
find_package( PkgConfig REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )


set(SPINNAKER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)

set(CMAKE_BUILD_TYPE Release)

add_definitions( -std=c++11 -Wall -Wno-unknown-pragmas )

find_library( SPINNAKER_LIB Spinnaker 
    PATHS ${SPINNAKER_SRC_DIR}/lib
    NO_CMAKE_PATHS 
    )

message(STATUS "Found ${SPINNAKER_LIB}")
include_directories( ${SPINNAKER_SRC_DIR} ${SPINNAKER_SRC_DIR}/include )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include )
add_executable( cam_server ./src/main.cpp )

# After building the server, copy required client and configuration files into
# current binary directory.
add_custom_command( TARGET cam_server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/camera_config_xml/ ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/config.h ${CMAKE_BINARY_DIR}
    VERBATIM 
   )
target_link_libraries(cam_server ${SPINNAKER_LIB} ${OpenCV_LIBRARIES} )

set_target_properties( cam_server 
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )

enable_testing( )

add_executable( test-socket ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_socket.cc )
target_link_libraries( test-socket )

add_test( test_socket test-socket )





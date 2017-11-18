cmake_minimum_required(VERSION 2.8)
project(EyeBlinkBehavour)

################################################################################
# ARDUINO BOARD 
################################################################################
find_package( PythonInterp REQUIRED )

if( NOT PORT )
execute_process( 
    COMMAND bash ${CMAKE_SOURCE_DIR}/scripts/list_serial_ports.sh 
    OUTPUT_VARIABLE PORT 
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif(NOT PORT)

if (NOT PORT )
    message(STATUS
        "WARNING:"
        "\nCould not find a serial port automatically. You won't be able to upload"
        "\n and run the arduino target. If you are sure that arduino board is "
        "\n connected and functional, you should provide port path from "
        "\n command line: e.g. \n"
        "\t -DPORT=/dev/ttyACM0 etc."
        "\n\n Or you may not be part of 'dailout' group?"
        )
else (NOT PORT)
    message(STATUS "Default serial port ${PORT}" )
endif (NOT PORT)


# Options related to Arduino board.
# Set the board tag
set(ARDUINO_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Extra paths to search for headers.
set(ARDUINO_EXTRA_CXXFLAGS "")

set(BOARD_TAG   uno)
set(BAUD_RATE   38400)
find_program(ARDUINO_BIN arduino )

# Set mouse path.
if( NOT MOUSE_PATH )
    message( STATUS "Searching for Logitech mouse" )
    execute_process( 
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/scripts/find_Logitech_mouse.sh
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        TIMEOUT 5
        OUTPUT_VARIABLE MOUSE_PATH 
        OUTPUT_STRIP_TRAILING_WHITESPACE )
endif( )

if(MOUSE_PATH)
    message( STATUS "Found Logitech mouse: ${MOUSE_PATH}" )
else(MOUSE_PATH)
    message( FATAL_ERROR "CMake could not find Logitech mouse. " 
        "Make sure it is connected to laptop. You can also specify mouse by "
        " setting the MOUSE_PATH variable "
        "     $ cmake -DMOUSE_PATH=/dev/input/mouse2 "
        " etc. "
        )
endif( )

set(ARDUINO_BOARD_FILE hardware/arduino/boards.txt)
find_path( ARDUINO_DIR 
    NAMES boards.txt
    PATHS /usr/share/arduino/hardware
    PATH_SUFFIXES arduino arduino/avr
    )
message( STATUS "Arduino location ${ARDUINO_DIR}" )

find_path( ARDUINO_LIQUID_LIB_DIRS 
    NAMES LiquidCrystal.h 
    PATHS /usr/share/arduino /opt
    PATH_SUFFIXES libraries/LiquidCrystal
    )

# Find directory where LiquidCrystal is installed.
message( STATUS "Liquid crystal library ${ARDUINO_LIQUID_LIB_DIRS}" )
if( ARDUINO_LIQUID_LIB_DIRS )
    set(ARDUINO_EXTRA_CXXFLAGS 
        "${ARDUINO_EXTRA_CXXFLAGS} -I${ARDUINO_LIQUID_LIB_DIRS}"
    )
endif( )


if(NOT ARDUINO_DIR)
    message(FATAL_ERROR "Arduino board list not found")
endif( )
message(STATUS "List of arduino boards ${ARDUINO_DIR}")

################################################################################
# Animal related options.
################################################################################
if( (NOT ANIMAL_NAME) OR (NOT SESSION_TYPE) OR (NOT SESSION_NUM) )
    message( FATAL_ERROR 
        "Please pass ANIMAL_NAME, SESSION_NUM and SESSION_TYPE to cmake \n"
        "\te.g cmake -DANIMAL_NAME=k3 -DSESSION_NUM=1 -DSESSION_TYPE=1 \n"
        )
endif ( )

# Data directory for given session and animal
set(DATADIR "$ENV{HOME}/DATA/${ANIMAL_NAME}/${ANIMAL_NAME}_${SESSION_TYPE}_${SESSION_NUM}")

# Python script handle this.
# file(MAKE_DIRECTORY ${DATADIR})


configure_file( ${CMAKE_SOURCE_DIR}/Makefile.arduino.in
    ${CMAKE_SOURCE_DIR}/Makefile.arduino
    )


set(ARDUINO_TARGET_NAME eyeBlinkBehaviour)
set(ARDUINO_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Write variables to config.h file.
configure_file( ${ARDUINO_SRC_DIR}/config.h.in ${ARDUINO_SRC_DIR}/config.h )

set(ARDDUINO_OUT_HEX_FILE 
    ${CMAKE_SOURCE_DIR}/${BOARD_NAME}/${ARDUINO_TARGET_NAME}/${ARDUINO_TARGET_NAME}.hex 
    )

add_custom_target( build_arduino_hex  ALL DEPENDS ${ARDDUINO_OUT_HEX_FILE}
    VERBATIM 
    )

add_custom_command( OUTPUT ${ARDDUINO_OUT_HEX_FILE}
    COMMAND $(MAKE) -f ${CMAKE_SOURCE_DIR}/Makefile.arduino
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    VERBATIM
    )

add_custom_target( upload 
    DEPENDS build_arduino_hex 
    COMMAND make -f ${CMAKE_CURRENT_SOURCE_DIR}/Makefile.arduino upload 
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

# make miniterm will launch the miniterm.py .
add_custom_target( miniterm
    DEPENDS upload 
    COMMAND miniterm.py ${PORT} ${BAUD_RATE}
    VERBATIM 
    )

# Reset all attached boards.
add_custom_target( reset_boards
    COMMAND bash scripts/reset_all_boards.sh
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    VERBATIM
    )

# Before run is executed, all scripts must be current binary directory.
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/run.sh.in ${CMAKE_BINARY_DIR}/run.sh )
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/copy_file.sh.in
    ${CMAKE_BINARY_DIR}/copy_file.sh )
configure_file( ${CMAKE_SOURCE_DIR}/camera_arduino_client.py.in 
    ${CMAKE_BINARY_DIR}/camera_arduino_client.py 
    )

# write .gnuplot
file(WRITE $ENV{HOME}/.gnuplot "set fit quiet; " )

# Pass animal options to run.sh which will will passed to python script.
SET(RUN_ARGS 
    -p ${PORT} -n ${ANIMAL_NAME} -sn ${SESSION_NUM} -st ${SESSION_TYPE} 
     )

# Copy python files into current working directory.
file(COPY ${CMAKE_SOURCE_DIR}/eyeblinkdetector/extract.py 
        ${CMAKE_SOURCE_DIR}/blinky.py 
        ${CMAKE_SOURCE_DIR}/read_mouse_delta.py
        DESTINATION ${CMAKE_BINARY_DIR}
     )

add_custom_target( run  
    DEPENDS cam_server upload
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
        ${CMAKE_SOURCE_DIR}/pyblink ${CMAKE_BINARY_DIR}
    COMMAND bash -x ./run.sh ${RUN_ARGS}
    COMMENT "Run arduino client and camera client"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    VERBATIM
    )

# Now  add the client and server 
add_subdirectory( ${CMAKE_SOURCE_DIR}/PointGreyCamera )

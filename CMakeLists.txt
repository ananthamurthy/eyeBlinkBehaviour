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
    message(FATAL_ERROR 
        "Could not find a serial port automatically. You won't be able to upload
        and run the arduino target. If you are sure that arduino board is
        connected and function, you should provide this information from command
        line: e.g. \n"
        "\t -DPORT=/dev/ttyACM0 etc."
        "\n Or you may not be part of 'dailout' group?"
        )
else (NOT PORT)
    message(STATUS "Default serial port ${PORT}" )
endif (NOT PORT)


# Options related to Arduino board.
# Set the board tag
set(BOARD_TAG   uno)
set(BAUD_RATE   38400)
find_program(ARDUINO_BIN arduino )

set(ARDUINO_BOARD_FILE hardware/arduino/boards.txt)
find_path( ARDUINO_DIR ${ARDUINO_BOARD_FILE}
    PATHS /usr/share/arduino /opt
    )

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
set(SELECT_AFTER 600000000)
set(FLIPPED 0)
set(CS_FRACTION 10)


configure_file( ${CMAKE_SOURCE_DIR}/Makefile.arduino.in
    ${CMAKE_SOURCE_DIR}/Makefile.arduino
    )

set(ARDUINO_TARGET_NAME eyeBlinkBehaviour)
set(ARDUINO_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(ARDDUINO_OUT_HEX_FILE 
    ${CMAKE_SOURCE_DIR}/${BOARD_NAME}/${ARDUINO_TARGET_NAME}/${ARDUINO_TARGET_NAME}.hex 
    )

add_custom_target( build_arduino_hex  ALL
    DEPENDS ${ARDDUINO_OUT_HEX_FILE}
    VERBATIM 
    )

add_custom_command( OUTPUT ${ARDDUINO_OUT_HEX_FILE}
    COMMAND $(MAKE) -f ${CMAKE_SOURCE_DIR}/Makefile.arduino
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    VERBATIM
    )

add_custom_target( upload 
    DEPENDS build_arduino_hex 
    COMMAND $(MAKE) -f ${CMAKE_SOURCE_DIR}/Makefile.arduino upload 
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

# make miniterm will launch the miniterm.py .
add_custom_target( miniterm
    DEPENDS upload 
    COMMAND miniterm.py ${PORT} ${BAUD_RATE}
    VERBATIM 
    )

# Reset all attached boards.
add_custom_target( reset
    COMMAND bash scripts/reset_all_boards.sh
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    VERBATIM
    )

# Before run is executed, all scripts must be current binary directory.
configure_file( ${CMAKE_SOURCE_DIR}/run.sh.in ${CMAKE_BINARY_DIR}/run.sh )
configure_file( ${CMAKE_SOURCE_DIR}/camera_arduino_client.py.in 
    ${CMAKE_BINARY_DIR}/camera_arduino_client.py 
    )

# Pass animal options to run.sh which will will passed to python script.
SET(RUN_ARGS 
    "-p ${PORT} -n ${ANIMAL_NAME} -sn ${SESSION_NUM} -st ${SESSION_TYPE}"
     " -f ${FLIPPED} -cf ${CS_FRACTION} -sa ${SELECT_AFTER}" 
     )

add_custom_target( run  
    DEPENDS cam_server
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
        ${CMAKE_SOURCE_DIR}/pyblink ${CMAKE_BINARY_DIR}
        COMMAND bash ./run.sh ${RUN_ARGS}
    COMMENT "Run arduino client and camera client"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    VERBATIM
    )

# Now  add the client and server 
add_subdirectory( ${CMAKE_SOURCE_DIR}/PointGreyCamera )

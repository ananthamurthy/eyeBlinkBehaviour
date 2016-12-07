cmake_minimum_required(VERSION 2.8)
project(EyeBlinkBehavour)

# Options related to Arduino board.
# Set the board tag
set(BOARD_TAG   uno)
set(BAUD_RATE   38400)
set(PORT "/dev/ttyACM0" )

find_program(ARDUINO_BIN arduino )

set(ARDUINO_BOARD_FILE hardware/arduino/boards.txt)
find_path( ARDUINO_DIR ${ARDUINO_BOARD_FILE}
    PATHS /usr/share/arduino /opt
    )

if(NOT ARDUINO_DIR)
    message(FATAL_ERROR "Arduino board list not found")
endif( )
message(STATUS "List of arduino boards ${ARDUINO_DIR}")

configure_file( ${CMAKE_SOURCE_DIR}/Makefile.in
    ${CMAKE_SOURCE_DIR}/Makefile 
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
    COMMAND $(MAKE) -f ${CMAKE_SOURCE_DIR}/Makefile
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    VERBATIM
    )

add_custom_target( upload 
    DEPENDS build_arduino_hex 
    COMMAND $(MAKE) upload 
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
    COMMAND bash ./reset_all_boards.sh
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    VERBATIM
    )

# Now  add the client and server 
add_subdirectory( ${CMAKE_SOURCE_DIR}/PointGreyCamera )

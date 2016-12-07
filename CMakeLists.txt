cmake_minimum_required(VERSION 2.8)
project(EyeBlinkBehavour)

# Options related to Arduino board.
# Set the board tag
set(BOARD_TAG uno)
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

set_target_properties( build_arduino_hex PROPERTIES 
    CMAKE_CXX_COMPILER gcc-avr
    )



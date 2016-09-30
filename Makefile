UNAME_S := $(shell uname -s)

### PROJECT_DIR
### This is the path to where you have created/cloned your project
PROJECT_DIR       = .

### ARDMK_DIR
### Path to the Arduino-Makefile directory.
ARDMK_DIR         = $(PROJECT_DIR)/makefiles

### ARDUINO_DIR
ARDUINO_BIN       = $(shell which arduino)
ifeq ($(UNAME_S),Darwin)
    ARDUINO_DIR       = /Applications/Arduino.app/Contents/Java
else
    ARDUINO_DIR       = $(dir $(shell readlink -f $(ARDUINO_BIN)))
endif

### BOARD_TAG
### It must be set to the board you are currently using. (i.e uno, mega2560, etc.)
BOARD_TAG         = uno

### MONITOR_BAUDRATE
### It must be set to Serial baudrate value you are using.
MONITOR_BAUDRATE  = 38400

### CFLAGS_STD
### Set the C standard to be used during compilation. Documentation (https://github.com/WeAreLeka/Arduino-Makefile/blob/std-flags/arduino-mk-vars.md#cflags_std)
CFLAGS_STD        = -std=gnu11

### CXXFLAGS_STD
### Set the C++ standard to be used during compilation. Documentation (https://github.com/WeAreLeka/Arduino-Makefile/blob/std-flags/arduino-mk-vars.md#cxxflags_std)
CXXFLAGS_STD      = -std=gnu++11

### CXXFLAGS
### Flags you might want to set for debugging purpose. Comment to stop.
CXXFLAGS         += -pedantic -Wall -Wextra

### MONITOR_PORT
### The port your board is connected to. Using an '*' tries all the ports and finds the right one.
MONITOR_PORT      = $(shell python $(PROJECT_DIR)/config/get_serial_ports.py)

### CURRENT_DIR
### Do not touch - used for binaries path
CURRENT_DIR       = $(shell basename $(CURDIR))

ARDUINO_LIBS 	  = LiquidCrystal

### OBJDIR
### This is where you put the binaries you just compile using 'make'
OBJDIR            = $(PROJECT_DIR)/bin/$(BOARD_TAG)/$(CURRENT_DIR)

## INO file and other cpp files
LOCAL_INO_SRCS     = $(PROJECT_DIR)/src/main.ino
LOCAL_CPP_SRCS     = 

### Do not touch - the path to Arduino.mk, inside the ARDMK_DIR
include $(ARDMK_DIR)/Arduino.mk


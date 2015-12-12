### PROJECT_DIR
### This is the path to where you have created/cloned your project
PROJECT_DIR       = .

### ARDMK_DIR
### Path to the Arduino-Makefile directory.
ARDMK_DIR         = $(PROJECT_DIR)/makefiles

### ARDUINO_DIR
### Path to the Arduino application and resources directory.
### On OS X:
ARDUINO_BIN       = $(shell which arduino)
ARDUINO_DIR       = $(dir $(shell readlink -f $(ARDUINO_BIN)))
### or on Linux: (remove the one you don't want)
##ARDUINO_DIR       = /usr/share/arduino

### BOARD_TAG
### It must be set to the board you are currently using. (i.e uno, mega2560, etc.)
BOARD_TAG         = uno

### MONITOR_BAUDRATE
### It must be set to Serial baudrate value you are using.
MONITOR_BAUDRATE  = 9600

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
MONITOR_PORT      = /dev/tty.usbmodem*

### CURRENT_DIR
### Do not touch - used for binaries path
CURRENT_DIR       = $(shell basename $(CURDIR))

ARDUINO_LIBS 	  = LiquidCrystal

### OBJDIR
### This is where you put the binaries you just compile using 'make'
OBJDIR            = $(PROJECT_DIR)/bin/$(BOARD_TAG)/$(CURRENT_DIR)

## INO file and other cpp files
LOCAL_INO_SRCS     = $(PROJECT_DIR)/eye-Blink_Conditioning/eye-Blink_Conditioning.ino 
LOCAL_CPP_SRCS     = $(PROJECT_DIR)/eye-Blink_Conditioning/TriggerImaging.cpp \
		$(PROJECT_DIR)/eye-Blink_Conditioning/Solenoid.cpp \
		$(PROJECT_DIR)/eye-Blink_Conditioning/PhaseChangeRoutine.cpp \
		$(PROJECT_DIR)/eye-Blink_Conditioning/main.cpp \
		$(PROJECT_DIR)/eye-Blink_Conditioning/LocalLibrary.cpp \
		$(PROJECT_DIR)/eye-Blink_Conditioning/LCDRelated.cpp \
		$(PROJECT_DIR)/eye-Blink_Conditioning/Initialize.cpp \
		$(PROJECT_DIR)/eye-Blink_Conditioning/DetectBlinks.cpp \
		$(PROJECT_DIR)/eye-Blink_Conditioning/ChangePhase.cpp 

### Do not touch - the path to Arduino.mk, inside the ARDMK_DIR
include $(ARDMK_DIR)/Arduino.mk

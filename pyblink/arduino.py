"""arduino.py: 

    Helper functions to communicate with arduino.

"""
from __future__ import print_function
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2015, Dilawar Singh and NCBS Bangalore"
__credits__          = ["NCBS Bangalore"]
__license__          = "GNU GPL"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import time
import serial
import serial.tools.list_ports 
import config
import logging
#logging = logging.getLogger('')

# Create a class to handle serial port.
class ArduinoPort( ):

    def __init__(self, path, baud_rate = 38400, **kwargs):
        self.path = path
        config.args_.port = path
        self.baudRate = baud_rate
        self.port = None

    def open(self, wait = True):
        # ATTN: timeout is essential else realine will block.
        try:
            print( "Trying %s with %d baudrate" % ( config.args_.port,
                self.baudRate ) )
            self.port = serial.serial_for_url( config.args_.port 
                    , baudrate = self.baudRate 
                    , timeout = 0.5
                    )
        except OSError as e:
            # Most like to be a busy resourse. Wait till it opens.
            print("[FATAL] Could not connect")
            print(e)
            if wait:
                logging.warn("[INFO] Device seems to be busy. I'll try to reconnect"
                        " after  some time..."
                        )
                time.sleep(1)
                self.open( True )
            else:
                quit()
        except Exception as e:
            logging.error("[FATAL] Failed to connect to port. Error %s" % e)
            quit()
        if wait:
            print("[INFO] Waiting for port %s to open" % self.path, end='')
            while not self.port.isOpen():
                if int(time.time() - tstart) % 2 == 0:
                    print('.', end='')
                    sys.stdout.flush()
        print(" ... OPEN")

    def read_line(self, **kwargs):
        line = self.port.readline()
        logging.debug('RX< %s' % line)
        # mysql.insert_line( line , auto_commit = True)
        return line.strip()

    def write_msg(self, msg):
        logging.info('Writing %s to serial port' % msg)
        self.port.write( bytes(msg) )

def get_default_serial_port( ):
    # If port part is not given from command line, find a serial port by
    # default.
    print("[WARN] Searching for ARDUINO port since no --port/-p is given")
    print("       Only listing ports with VENDOR ID ")
    coms = list(serial.tools.list_ports.grep( 'PID' ))
    return coms[-1][0]

def read_until( msg, timeout = 2.0, debug = False ):
    t = time.time()
    while True:
        line = config.serial_port_.read_line()
        if msg.lower() in line.lower():
            return line
        if time.time() - t > timeout:
            print("[INFO] Timeout for waiting.. %s" % (time.time() - t))
            return '0, 0'

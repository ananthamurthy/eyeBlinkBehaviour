"""arduino.py: 

    Helper functions to communicate with arduino.

"""
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2015, Dilawar Singh and NCBS Bangalore"
__credits__          = ["NCBS Bangalore"]
__license__          = "GNU GPL"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import serial
import serial.tools.list_ports 

# Create a class to handle serial port.
class ArduinoPort( ):

    def __init__(self, path, baud_rate = 9600, **kwargs):
        self.path = path
        self.baudRate = kwargs.get('baud_rate', 9600)
        self.port = None

    def open(self, wait = True):
        # ATTN: timeout is essential else realine will block.
        try:
            self.port = serial.serial_for_url(args_.port, self.baudRate, timeout = 1)
        except OSError as e:
            # Most like to be a busy resourse. Wait till it opens.
            print("[FATAL] Could not connect")
            print(e)
            if wait:
                print("[INFO] Device seems to be busy. I'll try to reconnect"
                        " after  some time..."
                        )
                time.sleep(1)
                self.open( True )
            else:
                quit()
        except Exception as e:
            print("[FATAL] Failed to connect to port. Error %s" % e)
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
        return line.strip()

    def write_msg(self, msg):
        print('[INFO] Writing %s to serial port' % msg)
        self.port.write(b'%s' % msg)
        time.sleep(0.1)



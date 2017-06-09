"""wheel_design.py: 

Wheel design in FreeCad.

"""
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2016, Dilawar Singh"
__credits__          = ["NCBS Bangalore"]
__license__          = "GNU GPL"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import sys
import os
import numpy as np
sys.path.append( '/usr/lib64/FreeCAD/lib/' )
import FreeCAD as _f

def write_wheel( doc ):
    """Write wheel on the doc
    """
    box = doc.addObject( "Part::Box", "mybox" )
    vo = box.ViewObject
    print vo

def main( ):
    doc = _f.newDocument( )
    write_wheel( doc )

if __name__ == '__main__':
    main()

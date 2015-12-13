"""mysql_support.py: 

Adds mysql support to eyeblink behaviour.

"""
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2015, Dilawar Singh and NCBS Bangalore"
__credits__          = ["NCBS Bangalore"]
__license__          = "GNU GPL"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

username = 'eyeblink'
server = 'ghevar.ncbs.res.in'
password = 'Jhapki1'
dbName = 'jhapki'

import MySQLdb as sql

db_alive_ = False

try:
    db_ = sql.connect( server, username, password, dbName)
    print('[INFO] MySql is alive')
    db_alive_ = True
except Exception as e:
    print("[INFO] Could not connect to mysql. Disabling support")
    db_alive_ = False

def main():
    pass

if __name__ == '__main__':
    main()

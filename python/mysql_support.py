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

import MySQLdb as sql
import datetime
import config
import time
import logging 
_logger =  logging.getLogger('')

username = 'eyeblink'
server = 'ghevar.ncbs.res.in'
password = 'Jhapki1'
dbName = 'jhapki'



db_alive_ = False
cursor_ = None
db_ = None

# one table for every months.
table_name = datetime.date.today().strftime('data_%Y%m')

try:
    db_ = sql.connect( server, username, password, dbName)
    print('[INFO] MySql is alive')
    db_alive_ = True
    cursor_ = db_.cursor()
    init()
except Exception as e:
    print("[INFO] Could not connect to mysql. Disabling support")
    db_alive_ = False

def init( ):
    global cursor_
    if not db_alive_:
        return
    print('Table name: %s' % table_name)
    cursor_.execute(
            '''CREATE TABLE IF NOT EXISTS {0} (timestamp TIMESTAMP
            , data VARCHAR(100) )'''.format(table_name)
            )

def insert_line( line, auto_commit = True, commit_interval = 2 ):
    global cursor_ 
    if not db_alive_:
        return 
    cursor_.execute('''INSERT INTO {0} VALUES( now(), '{1}')'''.format(
        table_name, line)
        )
    if auto_commit:
        # commit to server after commit_interval
        if int(time.time() - config.tstart) % commit_interval == 0:
            commit( )

def commit( ):
    # Should be called every three seconds. 
    global cursor_
    _logger.info("Writing data to mysql")
    if not db_alive_:
        return
    db_.commit()

def cleanup( ):
    if not db_alive_:
        return
    db_.close()

def main():
    init()

if __name__ == '__main__':
    main()

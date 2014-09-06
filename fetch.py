import urllib2
import string
import MySQLdb
import os
from dotenv import Dotenv

url = 'http://192.168.1.100'
env = Dotenv(os.path.dirname(os.path.realpath(__file__)) + '/.env')

socket = urllib2.urlopen(url)
row = socket.read()
socket.close()

data = string.split(row, ' ')

if data[0] == 'OK':
    data.pop(0)

    db = MySQLdb.connect(host=env['DB_HOST'],
                         user=env['DB_USER'],
                         passwd=env['DB_PASS'],
                         db=env['DB_NAME'])

    cursor = db.cursor()

    try:
        cursor.execute("""INSERT INTO sensors (humidity, temperature) VALUES (%s,%s)""",(data[0],data[1]))
        db.commit()
    except:
        db.rollback()

    db.close()

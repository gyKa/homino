import urllib2
import string

url = 'http://192.168.1.100'

socket = urllib2.urlopen(url)
row = socket.read()
socket.close()

data = string.split(row, ' ')

if data[0] == 'OK':
	data.pop(0)
	print data
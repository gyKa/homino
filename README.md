## homino

### System requirements

* Python
* Python Pip
* MySQL

### Installation

`make install`

Create database and user with password.

Fill up fields in `.env` file.python /home/pi/homino/fetch.py

Execute SQLs from `database.sql`.

Run `crontab -e` and at the bottom of the file add `*/1 * * * * /usr/bin/python /home/pi/homino/fetch.py`.

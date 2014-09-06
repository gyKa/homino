install:
	sudo apt-get install -y python-mysqldb python-pip
	sudo easy_install -U distribute
	sudo pip install dotenv
	touch .env
	echo "DB_HOST=localhost" > .env
	echo "DB_NAME=homino" >> .env
	echo "DB_USER=homino" >> .env
	echo "DB_PASS=" >> .env

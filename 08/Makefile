CC=gcc
FLAGS= -fPIC -shared -I/usr/include/python3.8 -o libutils.so

all: cjson setup

cjson: cjson.c
	$(CC) $(FLAGS) cjson.c -o cjson

setup: setup.py
	sudo python3 setup.py install

test: main.py
	python3 main.py

clean:
	rm -rf build/ cjson.egg-info/ dist/ cjson
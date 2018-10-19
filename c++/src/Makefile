demo: demo.cpp ../include/easydump.hpp
	g++ -std=c++14 -o demo demo.cpp

example: example.cpp ../include/easydump.hpp
	g++ -std=c++14 -o example example.cpp && ./example

.PHONY: all clear

all: example

clean:
	rm -rf example demo

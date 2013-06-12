all: main

main: ConfigLoader.o main.cpp
	g++ -Wall -o main main.cpp ConfigLoader.o

ConfigLoader.o: ConfigLoader.h ConfigLoader.cpp
	g++ -Wall -c ConfigLoader.cpp

VPATH = ../include/SFML ../include

main: main.o raymarching.o
	g++ -Wall main.o raymarching.o -o main -L../lib/ -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp Graphics.hpp raymarching.hpp
	g++ -Wall -c main.cpp -I ../include

raymarching.o: raymarching.cpp Graphics.hpp raymarching.hpp
	g++ -Wall -c raymarching.cpp -I ../include

clean:
	del /S main.o main.exe
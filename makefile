#Makefile for src folder
DIR = /home/shantanu/reporitories/csl781_assignment1

SRC = hello_world

LIBS = -lglut -lGLU -lGL

CC = g++

default:
		$(CC) -Wall -o build/$(SRC) src/$(SRC).cpp $(LIBS)

run:
		build/$(SRC)

clean:
		-rm -f $(SRC)


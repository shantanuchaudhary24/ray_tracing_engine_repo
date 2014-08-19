#Makefile for src folder
TARGET = src_name

LIBS = -lglut -lGLU -lGL

CC = /usr/gnu/bin/gcc

default: $(TARGET)

all: default

.c.o:
		$(CC) -c $<

$(TARGET): $$@.o
		$(CC) $@.o -Wall $(LIBS) -o $@

clean:
		-rm -f *.o $(TARGET)


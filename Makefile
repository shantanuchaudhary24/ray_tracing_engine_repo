CXX=g++
EXE=bin/run
FILES= src/main.cpp src/polygon.cpp
COMPILE=-c
LINK=-o
OBJECTS= obj/main.o obj/polygon.o
OBJDIR= obj/
LIBS= -lGL -lGLU -lglut -lm
DISABLE_WARNING=-w

all: create

create:
	$(CXX) $(COMPILE) $(FILES)  $(LIBS)
	mv *.o $(OBJDIR)
	$(CXX) $(LINK) $(EXE) $(OBJECTS) $(LIBS)

run: create
	./$(EXE)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJECTS)
	rm -rf *.h~ *.cpp~ *Makefile~

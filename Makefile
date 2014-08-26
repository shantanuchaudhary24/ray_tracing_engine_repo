CXX=g++
EXE=bin/run
FILES= src/polygon.cpp src/scene.cpp src/main.cpp src/transformations.cpp
COMPILE=-c
LINK=-o
OBJECTS= obj/polygon.o obj/scene.o obj/main.o obj/transformations.o
OBJDIR= obj/
LIBS= -lGL -lGLU -lglut -lm
DISABLE_WARNING=-w

all: bin

run:
	./$(EXE)

bin:object
	$(CXX) $(LINK) $(EXE) $(OBJECTS) $(LIBS)

object:
	$(CXX) $(COMPILE) $(FILES)  $(LIBS)
	mv *.o $(OBJDIR)
	
clean:
	rm -rf $(EXE)
	rm -rf $(OBJECTS)
	rm -rf *.h~ *.cpp~ *Makefile~


CXX=g++
EXE=bin/run
FILES= src/polygon.cpp src/scene.cpp src/main.cpp src/transformations.cpp src/clipping.cpp src/frustum.cpp
COMPILE=-c
LINK=-o
OBJECTS= obj/polygon.o obj/scene.o obj/main.o obj/transformations.o obj/clipping.o obj/frustum.o
OBJDIR= obj/
LIBS= -lGL -lGLU -lglut -lm
DISABLE_WARNING=-w

all: run

run: bin
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


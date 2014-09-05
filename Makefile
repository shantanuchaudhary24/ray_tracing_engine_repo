CXX=g++
EXE=bin/run
FILES= src/polygon.cpp src/scene.cpp src/main.cpp src/transformations.cpp src/clipping.cpp src/frustum.cpp
FILE2= src/main2.cpp
COMPILE=-c
LINK=-o
OBJECTS= obj/polygon.o obj/scene.o obj/main.o obj/transformations.o obj/clipping.o obj/frustum.o
OBJECT2= obj/main2.o
OBJDIR= obj/
LIBS= -lGL -lGLU -lglut -lm
DISABLE_WARNING=-w

all: m2

m2:
	$(CXX) $(COMPILE) $(FILE2)  $(LIBS)
	mv *.o $(OBJDIR)
	$(CXX) $(LINK) $(EXE) $(OBJECT2) $(LIBS)
	./$(EXE)

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


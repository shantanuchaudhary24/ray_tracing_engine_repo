CXX=g++
EXE=bin/run
FILES= src/polygon.cpp  src/matrix.cpp src/transformations.cpp src/frustum.cpp src/clipping.cpp src/scene.cpp src/parser.cpp src/illumination.cpp src/vectors.cpp src/main.cpp
COMPILE=-c
LINK=-o
OBJECTS= obj/polygon.o obj/matrix.o obj/transformations.o obj/frustum.o obj/clipping.o obj/scene.o obj/parser.o obj/illumination.o obj/vectors.o obj/main.o
OBJDIR= obj/
LIBS= -lGL -lGLU -lglut -lm
DISABLE_WARNING=-w
DIR=/home/mukesh/Desktop/graphics_csl781/csl781_assignment2/

all: gdb

create:
	$(CXX) $(COMPILE) $(FILES)  $(LIBS)
	mv *.o $(OBJDIR)
	$(CXX) $(LINK) $(EXE) $(OBJECTS) $(LIBS)

gdb:
	$(CXX) -g $(COMPILE) $(FILES)  $(LIBS)
	mv *.o $(OBJDIR)
	$(CXX) $(LINK) $(EXE) $(OBJECTS) $(LIBS)

debug:	
	gdb $(DIR)$(EXE)
	
run: create
	./$(EXE)

cscope:
	cscope -R -b

clean:
	rm -rf $(EXE)
	rm -rf $(OBJECTS)
	rm -rf *.h~ *.cpp~ *Makefile~

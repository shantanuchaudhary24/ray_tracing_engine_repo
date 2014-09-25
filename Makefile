CXX=g++
EXE=bin/run
FILES= src/polygon.cpp  src/matrix.cpp src/transformations.cpp src/frustum.cpp src/clipping.cpp src/scene.cpp src/parser.cpp src/illumination.cpp src/vectors.cpp src/main.cpp
COMPILE=-c
LINK=-o
OBJECTS= obj/polygon.o obj/matrix.o obj/transformations.o obj/frustum.o obj/clipping.o obj/scene.o obj/parser.o obj/illumination.o obj/vectors.o obj/main.o
OBJDIR= obj/
LIBS= -lGL -lGLU -lglut -lm
DISABLE_WARNING=-w
DEBUG= -g
DIR=/home/mukesh/Desktop/graphics_csl781/csl781_assignment2/
CONFIG_DIR=config/

ifndef CONFIG
	CONFIG=config.cfg
endif

OPTIONS_HEADER=include/options.h
SAMPLING = "\#define SUPERSAMPLING 1\n"
ifndef CONFIG
	CONFIG=config.cfg
endif

ifndef LEVEL
	OPTIONS=""
endif
ifdef LEVEL
	OPTIONS=$(SAMPLING)"\#define LEVEL "$(LEVEL)
endif

CONFIG_FILE=$(CONFIG_DIR)$(CONFIG)

all: build

build:
	@ echo $(OPTIONS) > $(OPTIONS_HEADER)
	$(CXX) $(COMPILE) $(FILES)  $(LIBS)
	mv *.o $(OBJDIR)
	$(CXX) $(LINK) $(EXE) $(OBJECTS) $(LIBS)

supersample:
	@ echo $(OPTIONS) > $(OPTIONS_HEADER)
	$(CXX) $(COMPILE) $(FILES)  $(LIBS)
	mv *.o $(OBJDIR)
	$(CXX) $(LINK) $(EXE) $(OBJECTS) $(LIBS)

run:
	./$(EXE) $(CONFIG_FILE)

gdb:
	$(CXX) $(DEBUG) $(COMPILE) $(FILES)  $(LIBS)
	mv *.o $(OBJDIR)
	$(CXX) $(LINK) $(EXE) $(OBJECTS) $(LIBS)

debug:	gdb
	gdb $(DIR)$(EXE)

cscope:
	cscope -R -b

clean:
	rm -rf $(EXE)
	rm -rf $(OBJECTS)
	rm -rf *.h~ *.cpp~ *Makefile~

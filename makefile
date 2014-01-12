#####################
#  tetris makefile  #
#####################

# code folders
SOURCE_DIR = src

ifeq ($(OS),Windows_NT)
RESOURCES = res/tetris.rc
endif

# build options
# -Ofast -msse4.1 -ffast-math -mfpmath=both -march=native -flto -fwhole-program
# -Ofast -msse4.1 -ffast-math -mfpmath=both -march=native
BUILDOPT = -g
# output file
OUTPUT   = ./Debug/tetris

##############################################################

# compiler
CC = g++ $(BUILDOPT) -std=c++11
# compiler flags
CCFLAGS = -c -Wall -pedantic -Iinc
# linker flags
ifeq ($(OS),Windows_NT)
	LFLAGS  = -Llib -llibrary -lpthread -lbassdll -lglfw3 -lgdi32 -lopengl32
else
	LFLAGS  = -Llib -llibrary -lpthread -lbass -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lXi
endif
# resource builder
RES = windres
# resource builder flags
RFLAGS = -O coff

##############################################################

# make pipeline
DIRECTORIES = $(SOURCE_DIR)
CXXDIRS = $(foreach dir, $(DIRECTORIES), $(dir)/*.cpp)
CXXMODS = $(wildcard $(CXXDIRS))

# compile each .cpp to .o
.cpp.o:
	$(CC) $(CCFLAGS) $< -o $@

# recipe for building .o from .rc files
%.o : %.rc
	$(RES) $(RFLAGS) $< -o $@

# convert .cpp to .o
CXXOBJS = $(CXXMODS:.cpp=.o)
# resource .rc to .o
CCRES   = $(RESOURCES:.rc=.o)

# link all OBJS using CC and link with LFLAGS, then output to OUTPUT
all: $(CXXOBJS) $(CCRES)
	$(CC) $(CXXOBJS) $(CCRES) $(LFLAGS) -o $(OUTPUT)

# remove each known .o file, and output
clean:
	$(RM) $(CXXOBJS) $(CCOBJS) $(CCRES) *~ $(OUTPUT).*

#
# Cross Platform Makefile
# Compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X
#
# Linux:
#   apt-get install freeglut3-dev
#

#CXX = g++
#CXX = clang++

EXE = asmbl_lib
SOURCES = ./src/main.cpp
SOURCES += ./lib/glut/imgui_impl_glut.cpp
SOURCES += ./lib/opengl2/imgui_impl_opengl2.cpp
SOURCES += ./lib/imgui/imgui.cpp
SOURCES += ./lib/imgui/imgui_demo.cpp
SOURCES += ./lib/imgui/imgui_draw.cpp
SOURCES += ./lib/imgui/imgui_widgets.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)

CXXFLAGS = -I./lib/imgui/ 
CXXFLAGS += -g -Wall -Wformat
LIBS =
BUILD_DIR=bin
##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += -lGL -lglut
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"
	LIBS += -framework OpenGL -framework GLUT
	LIBS += -L/usr/local/lib -L/opt/local/lib

	CXXFLAGS += -I/usr/local/include -I/opt/local/include
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
	ECHO_MESSAGE = "MinGW"
	LIBS += -lgdi32 -lopengl32 -limm32 -lglut
	CFLAGS = $(CXXFLAGS)
endif

OBJS += lib.o
##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------
%.o:./%.asm
	nasm -f elf *.asm

%.o:./src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:./lib/glut/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:./lib/opengl2/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:./lib/imgui/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)
	@echo $(OBJS)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	$(dir_guard)
	rm -f $(EXE) $(OBJS)

run:
	./$(EXE)
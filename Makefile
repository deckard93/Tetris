LIBDIRS= -L/usr/X11R6/lib
LDLIBS = -lglut -lGL -lGLU -lX11 -lm 

CPPFLAGS= -O3 -fpermissive -std=c++11
LDFLAGS= $(CPPFLAGS) $(LIBDIRS)

TARGETS = test anti practice tetris malloc tetrisGL
 
SRCS = test.cpp anti.cpp practice.cpp tetris.cpp malloc.cpp tetrisGL.cpp

OBJS =  $(SRCS:.cpp=.o)

CXX = g++

default: $(TARGETS)

LIBDIRS= -L/usr/X11R6/lib
LDLIBS = -lglut -lGL -lGLU -lX11 -lm -lpng

CPPFLAGS= -O3 -fpermissive -w -std=c++11
LDFLAGS= $(CPPFLAGS) $(LIBDIRS)

TARGETS = tetrisGL
 
SRCS = tetrisGL.cpp

OBJS =  $(SRCS:.cpp=.o)

CXX = g++

default: $(TARGETS)

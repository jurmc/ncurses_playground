CXX=g++
RM=rm -rf
CPPFLAGS=-I./ -ggdb
LDFLAGS=-lncurses

SRCS=ncurses_main.cpp nc_window.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: demo

demo: $(OBJS)
	$(CXX) $(LDFLAGS) -o demo $(OBJS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

ncurses_main.o: ncurses_main.cpp nc_window.hpp

nc_window.o: nc_window.cpp nc_window.hpp

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) demo

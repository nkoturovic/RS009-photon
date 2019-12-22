PROGRAM1   = int_example.out
PROGRAM2   = image_example.out
CXX       = g++
CXXFLAGS  = -g -std=c++17 -Wall -Wextra -Wpedantic -Iinclude -pthread -Wno-unused-parameter

OPENCV_CFLAGS := $(shell pkg-config opencv --cflags)
OPENCV_LIBS := $(shell pkg-config opencv --libs)

all: $(PROGRAM1) $(PROGRAM2)
	@echo 'Build finished'

$(PROGRAM2): image_example.o ../rs_img/librsimg.a
	$(CXX) $(CXXFLAGS) -o $@ $^ $(OPENCV_LIBS)

image_example.o: image_example.cpp undo.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(OPENCV_CFLAGS)

$(PROGRAM1): int_example.o
	$(CXX) $(CXXFLAGS) -o $@ $^

int_example.o: int_example.cpp undo.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) compile_commands.json *.out

dist: clean
	-tar -czvf $(PROGRAM).tar.bz2 *

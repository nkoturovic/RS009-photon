PROGRAM   = main.out
CXX       = g++
CXXFLAGS  = -g -std=c++17 -Wall -Wextra -Wpedantic -Iinclude -pthread -Wno-unused-parameter

$(PROGRAM): main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp undo.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) compile_commands.json

dist: clean
	-tar -czvf $(PROGRAM).tar.bz2 *

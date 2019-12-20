PROGRAM   = main.out
CXX       = g++
CXXFLAGS  = -g -std=c++17 -Wall -Wextra -Wpedantic

$(PROGRAM): main.o transform_manager.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

transform_manager.o: transform_manager.cpp transform_manager.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) compile_commands.json

dist: clean
	-tar -czvf $(PROGRAM).tar.bz2 *

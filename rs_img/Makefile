CXX = clang++

OPENCV_CFLAGS := $(shell pkg-config opencv --cflags)
OPENCV_LIBS := $(shell pkg-config opencv --libs)

CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Wno-unused-parameter -g $(OPENCV_CFLAGS) -O3
LDLIBS = $(OPENCV_LIBS)
SRC_DIR = src
INCLUDE_DIR = include

default: 
	@echo "Making library distribution package."
	+make dist -j 8
	@echo "Making Demos"
	+make demos -j 8
	@echo "Whole library is packed in 'rsimg.tar.gz', to use it just extract it in your project folder."

.PHONY: demos dist clean

dist: librsimg.a
	rm -f rsimg.tar rsimg.tar.gz
	tar -C include -zcvf rsimg.tar.gz rsimg ../librsimg.a

demos: demo_01.out demo_02.out demo_03.out demo_04.out demo_05.out
	@echo "Demos maked: "
	@echo $^

demo_01.out: demos/01/main.cpp librsimg.a
	$(CXX) -o $@ $(CXXFLAGS) $(LDLIBS) $^

demo_02.out: demos/02/main.cpp librsimg.a
	$(CXX) -o $@ $(CXXFLAGS) $(LDLIBS) $^

demo_03.out: demos/03/main.cpp librsimg.a
	$(CXX) -o $@ $(CXXFLAGS) $(LDLIBS) $^

demo_04.out: demos/04/main.cpp librsimg.a
	$(CXX) -o $@ $(CXXFLAGS) $(LDLIBS) $^

demo_05.out: demos/05/main.cpp librsimg.a
	$(CXX) -o $@ $(CXXFLAGS) $(LDLIBS) $^

librsimg.a: image.o image_impl.o transform.o display.o to_string.o
	ar rvs $@ $^

image.o: $(SRC_DIR)/image.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

image_impl.o: $(SRC_DIR)/image_impl.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

transform.o: $(SRC_DIR)/transform.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

display.o: $(SRC_DIR)/display.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

to_string.o: $(SRC_DIR)/visitor/to_string.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

clean:
	rm -rf $(TARGET) *.out *.o compile_commands.json output* *.a *.tar.gz

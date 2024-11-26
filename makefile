#Authored by Noah Klein

COMP=g++
CPPFLAGS=-std=c++11 -pedantic -Wformat -Wreturn-type 
FL_LINK_FLAGS=`fltk-config --ldflags`

all: headers main

main: main.o physics.o Robot.o RobotWidget.o sim.o
	$(COMP) $(COMP_FLAGS) $^ -o $@ -L lib $(FL_LINK_FLAGS)


#headers: src/*.cpp tags
headers: *.cpp tags
	./headers.sh

tags: *.cpp
	ctags -R

headersclean:
	-rm tags
	-rm headers
	-rm *.vs


# This is our master compiler rule to generate .o files.
# It needs all 4 warnings
%.o:src/%.cpp include/*.hpp
	$(COMP) $(CPPFLAGS) -g -c $< -o $@

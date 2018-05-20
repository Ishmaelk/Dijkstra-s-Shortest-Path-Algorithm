########################################
##
## Makefile
## LINUX compilation 
##
##############################################

#FLAGS
C++FLAG = -g -std=c++11 -Wall

all: PROGRAM

PROGRAM:
	g++ CreateGraphAndTest.cc -o CreateGraphAndTest -std=c++11
	g++ FindPaths.cc -o FindPaths -std=c++11
	g++ TopologicalSort.cc -o TopologicalSort -std=c++11

clean:
	(rm CreateGraphAndTest)
	(rm FindPaths)
	(rm TopologicalSort)

CPP = g++ -g -O0 -Wall -Wextra -std=gnu++11
EXECBIN = graph

CPPSRC = main.cpp graph.cpp
OBJECTS = ${CPPSRC:.cpp=.o}

all: ${OBJECTS}
	${CPP} -o ${EXECBIN} ${OBJECTS}

%.o : %.cpp 
	${CPP} -c $<

clean:
	rm *o 
	rm graph

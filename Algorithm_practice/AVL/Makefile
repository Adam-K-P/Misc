CPP = g++ -g -O0 -Wall -Wextra -std=c++1y

CPPSRC = test1.cpp

T1OBJS = test1.o 

all: ${T1OBJS}
	${CPP} -o test1 ${T1OBJS}

%.o : %.cpp 
	${CPP} -c $<

clean:
	rm *o
	rm test1



GPP = g++ -g -O0 -Wall -Wextra -std=gnu++11

all : merge

merge : main.o merge.o
	${GPP} main.o merge.o -o merge

%.o : %.cpp
	${GPP} -c $<

clean :
	-rm main.o merge.o merge

#Dependencies
main.o: main.cpp merge.o
merge.o: merge.cpp merge.h

MatrixTest : MatrixTest.o Matrix.o List.o
	gcc -o MatrixTest MatrixTest.o Matrix.o List.o

Matrix.o : Matrix.c Matrix.h List.h
	gcc -c -std=c11 -Wall -Wextra -O3 -g Matrix.c

MatrixTest.o : MatrixTest.c Matrix.h List.h
	gcc -c -std=c11 -Wall -Wextra -O3 -g MatrixTest.c

List.o : List.c List.h
	gcc -c -std=c11 -Wall -Wextra -O3 -g List.c

clean :
	rm -f MatrixTest .*.o .*.swp 


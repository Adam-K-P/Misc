Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -c -std=c11 -Wall -Wextra -O3 -g Lex.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c11 -Wall -Wextra -O3 -g ListClient.c

List.o : List.c List.h
	gcc -c -std=c11 -Wall -Wextra -O3 -g List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o .*.swp 


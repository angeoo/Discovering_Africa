CC = gcc -fsanitize=address
CFLAGS = -Wall -Wextra

all:main
main : main.o questions.o

questions.o: questions.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} main

#END

CC = gcc
CFLAGS= -Wall -Wextra

all:main
main : main.o pixel_operations.o pretraitement.o

pixel_operations.o : pixel_operations.h
pretraitement.o: pixel_operations.o 


clean:
	${RM} *.o
	${RM} *.d
	${RM} main

#END

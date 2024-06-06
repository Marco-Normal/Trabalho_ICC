##
# main.c
#
# @file
# @version 0.1

CC = gcc
CFLAGS = -O2 -Wall -lm



all: main

main: main.c
	$(CC) $(CFLAGS) -o main main.c


clean:
	@rm -f main *.txt 


# end

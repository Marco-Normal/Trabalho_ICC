##
# main.c
#
# @file
# @version 0.1

CC = gcc
CFLAGS = -O2 -Wall -lm



all: main2

main: main2.c
	$(CC) $(CFLAGS) -o main main2.c


clean:
	@rm -f main *.txt 


# end

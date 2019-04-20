# CFLAGS = -g -Wall
# LDFLAGS = -g

# program: program.o mod.o
# mod.o: mod.c
# program.o: program.c
# clean: 
# 	rm -f program *.o

CC = gcc
CFLAGS = -Wall

main: person
	$(CC) $(CFLAGS) main.c -o person person.o

person: 
	$(CC) $(CFLAGS) -c person.c

clean: 
	rm person person.o
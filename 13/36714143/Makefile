CC = gcc
CFLAGS = -Wall -Wextra

OBJS = task13.o main13.o

task13: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main13.o: main13.c task13.h
	$(CC) $(CFLAGS) -c main13.c

task13.o: task13.c task13.h
	$(CC) $(CFLAGS) -c task13.c

clean:
	rm -f *.o task13

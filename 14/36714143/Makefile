CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = main
OBJS = main.o task14.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c task14.h
	$(CC) $(CFLAGS) -c main.c

task14.o: task14.c task14.h
	$(CC) $(CFLAGS) -c task14.c

clean:
	rm -f $(OBJS) $(TARGET)

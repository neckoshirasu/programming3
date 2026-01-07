CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lm

OBJS = main12.o image.o ascii.o crop.o concat.o

36714143: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

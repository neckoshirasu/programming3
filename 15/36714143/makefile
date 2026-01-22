CC = gcc
CFLAGS = -Wall -lm

TARGET = task15-1
OBJS = main15-1.o task15-1.o
STUNO = 36714143

all: $(TARGET) run plot

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -lm

main15-1.o: main15-1.c task15-1.h
task15-1.o: task15-1.c task15-1.h

run: $(TARGET)
	./$(TARGET)

plot:
	echo "set xlabel 'x'; \
	set ylabel 'y'; \
	set style data lines; \
	plot '$(STUNO)-1.dat' title 'sin(x^2)/x', \
	     '$(STUNO)-2.dat' title '1/x', \
	     '$(STUNO)-3.dat' title '-1/x'; \
	set terminal pdf; \
	set output '$(STUNO)-15-3.pdf'; \
	replot; \
	exit" | gnuplot

clean:
	rm -f $(OBJS) $(TARGET) $(STUNO)-*.dat $(STUNO)-15.pdf

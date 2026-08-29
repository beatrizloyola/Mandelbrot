CC = gcc
CFLAGS = -Wall -Wextra -O2 -pthread
LDFLAGS = -lm

TARGET = mandelbrot

all: $(TARGET)

$(TARGET): main.c mandelbrot.c
	$(CC) $(CFLAGS) -fopenmp -o $(TARGET) main.c mandelbrot.c $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o *.pgm times.txt

.PHONY: all clean

CC=gcc
CFLAGS=-02 -W -Wall -pedantic -ansi
TARGET=sdksolver

all: $(TARGET)

$(TARGET): grid.o
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $^ $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -f *.o

mrproper: clean
	@rm -f $(TARGET)

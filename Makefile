CC=gcc
CFLAGS=-O2 -W -Wall -pedantic -ansi
TARGET=sdksolver

all: $(TARGET)

$(TARGET): main.o grid.o solve.o
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $^ $(CFLAGS)

.PHONY: clean mrproper rebuild

clean:
	@rm -f *.o

mrproper: clean
	@rm -f $(TARGET)

rebuild: mrproper all

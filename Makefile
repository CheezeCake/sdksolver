CC=gcc
CFLAGS=-O2 -W -Wall -pedantic -ansi
TARGET=sdksolver

all: $(TARGET)

$(TARGET): main.o grid.o solve.o
	$(CC) $^ -o $@

main.o: main.c
	$(CC) -c $^ $(CFLAGS)

%.o: %.c %.h
	$(CC) -c $< $(CFLAGS)

.PHONY: clean mrproper rebuild

clean:
	@rm -f *.o

mrproper: clean
	@rm -f $(TARGET)

rebuild: mrproper all

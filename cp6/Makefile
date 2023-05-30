CC=clang
CFLAGS=-Wall -Werror -Wextra -Wfatal-errors -Wpedantic -pedantic-errors -std=c18
LDFLAGS=
LDLIBS=
EXECUTABLE=bin/pdump bin/pselect

all: $(EXECUTABLE)

bin/pdump: passenger.o dump_passenger.o
	$(CC) $(LDFLAGS) passenger.o dump_passenger.o $(LDLIBS) -o $@

bin/pselect: passenger.o select_passenger.o 
	$(CC) $(LDFLAGS) passenger.o select_passenger.o  $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

debug: CFLAGS+=-Og -g

.PHONY: all debug clean

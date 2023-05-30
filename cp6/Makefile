CC=clang
CFLAGS=-Wall -Werror -Wextra -Wfatal-errors -Wpedantic -pedantic-errors -std=c18
LDFLAGS=
LDLIBS=
SOURCES=passenger.c dump_passenger.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=pdump pselect

all: pdump

pdump : passenger.o dump_passenger.o
	$(CC) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

debug: CFLAGS+=-Og -g

.PHONY: all debug clean

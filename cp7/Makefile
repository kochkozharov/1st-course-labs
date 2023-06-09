CC=gcc
CFLAGS=-Wall -Werror -Wextra -Wfatal-errors -Wpedantic -pedantic-errors -std=c18
LDFLAGS=
LDLIBS=
SOURCES=main.c matrix.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

debug: CFLAGS+=-Og -g

.PHONY: all debug clean

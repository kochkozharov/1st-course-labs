CC=gcc
CFLAGS=-Wall -Werror -Wextra -Wfatal-errors -Wpedantic -pedantic-errors -std=c18
LDFLAGS=
LDLIBS=
EXECUTABLE=bin/pdump bin/pselect
DIRS=bin


all: $(DIRS) $(EXECUTABLE)

$(DIRS):
	mkdir -p $(DIRS)

bin/pdump: bin/passenger.o bin/dump_passenger.o
	$(CC) $(LDFLAGS) bin/passenger.o bin/dump_passenger.o $(LDLIBS) -o $@

bin/pselect: bin/passenger.o bin/select_passenger.o 
	$(CC) $(LDFLAGS)  bin/passenger.o bin/select_passenger.o  $(LDLIBS) -o $@

bin/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf bin/*.o $(EXECUTABLE)

debug: CFLAGS+=-Og -g

.PHONY: all debug clean

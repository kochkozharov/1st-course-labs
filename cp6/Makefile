CC=gcc
CFLAGS=-Wall -Werror -Wextra -Wfatal-errors -Wpedantic -pedantic-errors -std=c18
LDFLAGS=
LDLIBS=
EXECUTABLE=pdump pselect
SOURCES=passenger.c select_passenger.c dump_passenger.c
OBJECTS=$(SOURCES:.c=.o)
BIN=bin

all: $(EXECUTABLE)

pdump: $(BIN) $(OBJECTS)
	$(CC) $(LDFLAGS) $(addprefix $(BIN)/, passenger.o dump_passenger.o) $(LDLIBS) -o $(BIN)/$@

pselect: $(BIN) $(OBJECTS)
	$(CC) $(LDFLAGS) $(addprefix $(BIN)/, passenger.o select_passenger.o) $(LDLIBS) -o $(BIN)/$@

$(BIN):
	mkdir -p $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(BIN)/$@

clean:
	rm -rf $(BIN)

debug: CFLAGS+=-Og -g

.PHONY: all debug clean

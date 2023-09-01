CC=gcc
CFLAGS=-Wall -Werror -Wextra -Wfatal-errors -Wpedantic -pedantic-errors -std=c18
LDFLAGS=
LDLIBS=
EXECUTABLE=dump select
SOURCES=student.c select_students.c dump_students.c
OBJECTS=$(SOURCES:.c=.o)
BIN=bin

all: $(EXECUTABLE)

dump: $(BIN) $(OBJECTS)
	$(CC) $(LDFLAGS) $(addprefix $(BIN)/, student.o dump_students.o) $(LDLIBS) -o $(BIN)/$@

select: $(BIN) $(OBJECTS)
	$(CC) $(LDFLAGS) $(addprefix $(BIN)/, student.o select_students.o) $(LDLIBS) -o $(BIN)/$@

$(BIN):
	mkdir -p $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(BIN)/$@

clean:
	rm -rf $(BIN)

debug: CFLAGS+=-Og -g

.PHONY: all debug clean

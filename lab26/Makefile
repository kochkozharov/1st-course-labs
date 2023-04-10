CC=gcc
RM=rm -fr
CFLAGS=-Wall -Werror -Wextra -Wfatal-errors -Wpedantic -pedantic-errors -std=c18
LDFLAGS=
LDLIBS=
SOURCES=main.c vector.c
#TEST_SOURCES=vector.test.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main
#TEST_EXECUTABLE=$(TEST_SOURCES:.test.c=)

debug: CFLAGS+=-Og -g
debug: all

all: $(EXECUTABLE)

# test: $(TEST_EXECUTABLE)
test: vector sort
	./vector
	./sort

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

vector: vector.test.c vector.o
	$(CC) $(CFLAGS) -c vector.test.c -o vector.test.o
	$(CC) $(LDFLAGS) vector.o vector.test.o $(LDLIBS) -o $@

sort: sort.test.c sort.o vector.o
	$(CC) $(CFLAGS) -c sort.test.c -o sort.test.o
	$(CC) $(LDFLAGS) sort.o vector.o sort.test.o $(LDLIBS) -o $@

# $(TEST_EXECUTABLE): $(OBJECTS) $(TEST_SOURCES)
#	$(CC) -c $(LDFLAGS) $(OBJECTS) $(TEST_SOURCES) $(LDLIBS) -o $@
#	$(CC) -c $(LDFLAGS) $(OBJECTS) $(TEST_SOURCES) $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o $(EXECUTABLE)

# This is Makefile for test execution

BINARY_NAME=test

SOURCES=*.c
DEFINES=RINGBUFFER_VERSION="\"1.0\""

all:
	gcc $(SOURCES) -o $(BINARY_NAME) -D$(DEFINES)
	@echo "Tests successfully compiled."
	@echo "Executing \"$(BINARY_NAME)\"\n\n"
	./$(BINARY_NAME)

clean:
	rm $(BINARY_NAME)
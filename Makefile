# Makefile for test building, execution and saving results

RINGBUFFER_VERSION="1.0"
RINGBUFFER_GIT_REVISION := $(shell git log --pretty=format:"%H" -n1)


C_SOURCES=*.c
C_DEFINES=\
	-DRINGBUFFER_VERSION="\"$(RINGBUFFER_VERSION)\"" \
	-DRINGBUFFER_GIT_REVISION="\"$(RINGBUFFER_GIT_REVISION)\""

BINARY_NAME=test
TEST_RESULT_FILENAME=$(RINGBUFFER_VERSION)"_test_result.txt"

all:
	gcc $(C_SOURCES) -o $(BINARY_NAME) $(C_DEFINES)
	@echo "Tests successfully compiled."
	@echo "Executing \"$(BINARY_NAME)\"\n\n"
	./$(BINARY_NAME) | tee $(TEST_RESULT_FILENAME)

clean:
	rm $(BINARY_NAME) $(TEST_RESULT_FILENAME)

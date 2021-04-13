# RingBuffer 1.0

A simple ring buffer implementation. The ring buffer can hold a number of
32bit values.

## Features

* Statically allocated
* Oldest values are not overwritten, when size is exceeded
* Api supports getting/putting data

## Implementation
Underlying buffer is **statically** allocated on the stack. Up to 32 bit values
can be put into buffer. In this implementation entries **are not** overwritten
when the size is exceeded.

## Usage
Use **RING_BUFFER_DECLARE** to create a buffer.
```
...
RING_BUFFER_DECLARE(MY_BUF_NAME, MY_SIZE);
...
```

Use **ringBufferPut** to insert a value to buffer.
```
...
ringBufferPut(&MY_BUF_NAME, MY_VALUE);
...
```

Use **ringBufferGet** to get and remove the oldest entry.

```
...
ringBufferGet(&MY_BUF_NAME, POINTER_TO_MY_VAL)
...
```

See **main.c** for more examples.

## Tests
Test results are saved in **1.0_test_result.txt**.
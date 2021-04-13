#pragma once

#include <stdint.h>

typedef struct RingBuffer {
    uint32_t *mem;
    uint32_t *current;
    uint32_t usage;
    const uint32_t size;
} RingBuffer_t;

/** Creates ring buffer instance **/
#define RING_BUFFER_DECLARE(name, size) \
    volatile unsigned _static_buf##name[size]; \
    RingBuffer_t name = { \
         (uint32_t*)_static_buf##name, \
         (uint32_t*)_static_buf##name, \
         0, \
         size }

/** Creates ring buffer for holding a size of type values */
#define RING_BUFFER_DECLARE_ANY(type, name, buf_size) \
    type _static_buf##name[buf_size]; \
    struct RingBuffer_##type##name { \
        type *mem; \
        type *current; \
        uint32_t usage; \
        const uint32_t size; \
    }; \
    struct RingBuffer_##type##name name = { \
        .mem = _static_buf##name, \
        .current = _static_buf##name, \
        .usage = 0, \
        .size = buf_size }

/** Puts new element into ring buffer
 *
 * Args:
 *      ringBuffer - pointer to ringbuffer
 *      value      - value to put into ringBuffer
 * Returns:
 *      0          - success
 *      negative   - value couldn't be put into ringbuffer
 */
int ringBufferPut(RingBuffer_t *ringBuffer, uint32_t value);

/** Gets current value from ring buffer
 *
 * Args:
 *      ringBuffer  - pointer to ringbuffer
 *      value [out] - pointer where value will be stored
 * Returns:
 *      0           - success
 *      negative    - value couldn't be gotten
 */
int ringBufferGet(RingBuffer_t *ringBuffer, uint32_t * const value);
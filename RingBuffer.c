#include "RingBuffer.h"

#define RET_ERR -1
#define RET_OK  0

static uint32_t *getOldestElement(RingBuffer_t *buf);

int ringBufferPut(RingBuffer_t *ringBuffer, uint32_t value)
{
    if (!ringBuffer) {
        return RET_ERR;
    }

    if (ringBuffer->usage == ringBuffer->size) {
        return RET_ERR;
    }

    *ringBuffer->current = value;
    ringBuffer->usage++;
    ringBuffer->current = (ringBuffer->current < &ringBuffer->mem[ringBuffer->size-1]) ?
                           ringBuffer->current+1 : ringBuffer->mem;

    return RET_OK;
}

int ringBufferGet(RingBuffer_t *ringBuffer, uint32_t * const value)
{
    if (!ringBuffer || !value) {
        return RET_ERR;
    }

    if (ringBuffer->usage == 0) {
        return RET_ERR;
    }

    ringBuffer->usage--;
    *value = *getOldestElement(ringBuffer);

    return RET_OK;
}



static uint32_t *getOldestElement(RingBuffer_t *buf)
{
    uint32_t distanceToBegin = buf->current - buf->mem;

    if (distanceToBegin > buf->usage) {
        return buf->current - buf->usage;
    }

    uint32_t distanceFromBack = buf->usage - distanceToBegin;

    return buf->mem + (buf->size-1) - distanceFromBack;
}

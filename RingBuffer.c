#include "RingBuffer.h"

#define RET_ERR -1
#define RET_OK  0

static void moveCurrentForward(RingBuffer_t *buf);
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
    moveCurrentForward(ringBuffer);

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

static void moveCurrentForward(RingBuffer_t *buf)
{
    if (buf->current < &buf->mem[buf->size-1]) {
        buf->current++;
    } else {
        buf->current = buf->mem;
    }
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

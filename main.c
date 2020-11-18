#include "RingBuffer.h"
#include <stdio.h>
#include <stdbool.h>

#define LOG_TEST_RESULT(index, test_name, result) \
    printf("[%2d] %-45s %s\n", index, test_name, result ? "passed" : "failed")


int main()
{
    printf("[Id] %-45s %s\n\n", "Test Name", "Results");

    int testNumber = 0;
    {
        /* Check return value of ringBufferPut */
        RING_BUFFER_DECLARE(buf, 5);
        bool ringBufferPutRetOk;

        for (int i = 100; i < 100 + buf.size; i++)
        {
            if (ringBufferPut(&buf, i) == 0)
            {
                ringBufferPutRetOk = true;
            }
            else
            {
                ringBufferPutRetOk = false;
                break;
            }
        }

        LOG_TEST_RESULT(++testNumber, "RingBufferPut", ringBufferPutRetOk);
    }

    {
        /* Check if values put into buffer are present there */
        RING_BUFFER_DECLARE(buf, 5);
        bool ringBufferPutOk;

        for (int i = 0; i < buf.size; i++)
        {
            (void)ringBufferPut(&buf, (uint32_t)i);

            if (buf.mem[i] != i) {
                ringBufferPutOk = false;
                break;
            } else {
                ringBufferPutOk = true;
            }
        }

        LOG_TEST_RESULT(++testNumber, "Values in ring buffer", ringBufferPutOk);
    }

    {
        /* Check if value cannot be put into buffer when full */
        RING_BUFFER_DECLARE(buf, 5);
        for (int i=0; i<buf.size; i++) ringBufferPut(&buf, (uint32_t)i);

        bool result = ringBufferPut(&buf, 0) < 0;
        LOG_TEST_RESULT(++testNumber, "Check return value when full", result);
    }

    {
        /** Check if buffer content remains unchanged after attempt to put the 
         *  new value to full buffer.
         */
        RING_BUFFER_DECLARE(buf, 25);
        bool contentOk;

        for (int i=0; i<buf.size; i++) ringBufferPut(&buf, (uint32_t)i);

        (void)ringBufferPut(&buf, 259);
        for (int i=0; i<buf.size; i++) {
            if (buf.mem[i] != i) {
                contentOk = false;
                break;
            } else {
                contentOk = true;
            }
        }

        LOG_TEST_RESULT(++testNumber, "Check content after put fail", contentOk);
    }

    {
        /* Check return value of ringBufferGet when buf is empty */
        RING_BUFFER_DECLARE(buf, 2);
        uint32_t _;
        LOG_TEST_RESULT(++testNumber, "ringBufferGet when empty", 
                        ringBufferGet(&buf, &_) < 0);
    }

    {
        /* Check return value of ringBufferGet when buf is full */
        RING_BUFFER_DECLARE(buf, 7);
        for (int i=0; i<buf.size; i++) ringBufferPut(&buf, (uint32_t)i);

        bool getOk;
        for (int i=0; i<buf.size; i++) {
            uint32_t _;
            getOk = ringBufferGet(&buf, &_) == 0;
            if (!getOk) {
                break;
            }
        }

        LOG_TEST_RESULT(++testNumber, "ringBufferGet ret whole buffer", getOk);
    }

    {
        /* Check values gotten by ringBufferGet */
        RING_BUFFER_DECLARE(buf, 7);

        for (int i=0; i<buf.size; i++) ringBufferPut(&buf, (uint32_t)i);

        bool valuesMatch;
        for (int i=0; i<buf.size; i++) {
            uint32_t gotVal;
            (void)ringBufferGet(&buf, &gotVal);
            
            valuesMatch = gotVal == i;
            if (!valuesMatch) {
                break;
            }
        }

        LOG_TEST_RESULT(++testNumber, "ringBufferGet compare values", valuesMatch);
    }

    {
        /* Check getting values after one round */
        RING_BUFFER_DECLARE(buf, 8);

        /* [0, 1, 2, 3, 4, 5, 6, 7] */
        for (int i=0; i<8; i++) ringBufferPut(&buf, i);

        /* [_, _, _, _, _, _, 6, 7] */
        for (int i=0, _; i<6; i++) ringBufferGet(&buf, (uint32_t*)&_);

        /* [10, 11, 12, 13, 14, 15, 6, 7] */
        for (int i=10; i<16; i++) ringBufferPut(&buf, i);

        uint32_t expectedValues[] = {10, 11, 12, 13, 14, 15, 6, 7};
        bool valuesMatch;

        for (uint32_t i=0, value; i<8; i++) {
            ringBufferGet(&buf, &value);
            valuesMatch = expectedValues[i] != value;

            if (!valuesMatch) {
                break;
            }
        }

        LOG_TEST_RESULT(++testNumber, "Get values after circle", valuesMatch);

    }

    return 0;
}

#include <spu_mfcio.h>

/* Vectors per iteration = 4096/4 */
#define SIZE 1024

int main(unsigned long long speid, unsigned long long argp, unsigned long long envp)
{
    unsigned short i, j, start, end = 0;

    /* The buffer is twice the size of the data */
    vector unsigned int buff[SIZE * 2] __attribute__((aligned(128)));
    unsigned short block_size = sizeof(buff) / 2;

    /* Fill low half with unprocessed data */
    mfc_get(buff, argp, block_size, 0, 0, 0);

    for (i = 0; i < 8; i++) {

        /* Fill new buffer with unprocessed data */
        mfc_get(buff + (i & 1) * SIZE, argp + i * block_size, block_size, i & 1, 0, 0);

        /* Wait for old buffer to fill/empty */
        mfc_write_tag_mask(1 << (1 - (i & 1)));
        mfc_read_tag_status_all();

        /* Process data in old buffer */
        start = (i & 1) ? 0 : SIZE;
        end = start + SIZE;
        for (j = start; j < end; j++)
            buff[j] = spu_add(buff[j], 1);

        /* Write data in old buffer to memory */
        mfc_put(buff + (1 - (i & 1)) * SIZE, argp + (i - 1) * block_size, block_size, 1 - (i & 1), 0, 0);
    }

    /* Read the last unprocessed data */
    mfc_write_tag_mask(2);
    mfc_read_tag_status_all();

    /* Process the last data */
    start = SIZE;
    end = 2 * SIZE;
    for (j = start; j < end; j++)
        buff[j] = spu_add(buff[j], 1);

    /* Write the last processed data to memory */
    mfc_put(buff + SIZE, argp + 7 * block_size, block_size, 1, 0, 0);
    mfc_read_tag_status_all();

    return 0;
}


#include <spu_mfcio.h>

/* Vectors per iteration */
#define SIZE 1024
#define TAG 3

int main(unsigned long long speid, unsigned long long argp, unsigned long long envp)
{
    int i, j;
    vector unsigned int buff[SIZE] __attribute__((aligned (128)));

    for (i = 0; i < 8; i++) {

        /* Read unprocessed data from main memory */
        mfc_get(buff, argp + i * sizeof(buff), sizeof(buff), TAG, 0, 0);
        mfc_write_tag_mask(1 << TAG);
        mfc_read_tag_status_all();

        /* Process the data */
        for (j = 0; j < SIZE; j++)
            buff[j] = spu_add(buff[j], 1);

        /* Write the processed data to main memory */
        mfc_put(buff, argp + i * sizeof(buff), sizeof(buff), TAG, 0, 0);
        mfc_write_tag_mask(1 << TAG);
        mfc_read_tag_status_all();
    }

    return 0;
}


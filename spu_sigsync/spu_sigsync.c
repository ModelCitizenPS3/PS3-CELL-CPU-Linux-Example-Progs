#include <stdio.h>
#include <spu_mfcio.h>
#include <spu_intrinsics.h>

#define TAG 3
#define SPUS 5

/* SPU initialization data */
typedef struct _control_block {
    unsigned long long ea_addr[SPUS];
    unsigned long long pad[8 - SPUS];
} control_block;

int main(unsigned long long speid, unsigned long long argp, unsigned long long envp)
{
    control_block cb __attribute__((aligned(128)));
    volatile vector unsigned int sig_vec;
    unsigned int i, sig_data;

    if (envp != 0) {

        /* This SPU is a slave */
        sig_data = 1 << (unsigned int)envp - 1;
        sig_vec = spu_promote(sig_data, 3);

        /* Send signal to master */
        mfc_sndsig((volatile void *)(&sig_vec) + 12, argp, TAG, 0, 0);
        mfc_write_tag_mask(1 << TAG);
        mfc_read_tag_status_all();

        /* Receive signal from master */
        spu_read_signal1();
        printf("SPU %llu starting operation\n", envp);
    }

    else {
        /* This SPU is the master */

        /* Transfer the array from argp */
        mfc_get(&cb, argp, sizeof(cb), TAG, 0, 0);
        mfc_write_tag_mask(1 << TAG);
        mfc_read_tag_status_all();

        /* Check to make sure the slave SPUs are ready */
        unsigned int count = 1;
        unsigned int total_count = 15;
        while (count < total_count)
            count |= spu_read_signal1();

        /* Tell the slave SPUs to start processing */
        sig_vec = spu_promote(sig_data, 3);
        for (i = 1; i < SPUS; i++)
            mfc_sndsig((volatile void *)(&sig_vec) + 12, cb.ea_addr[i], TAG, 0, 0);
        mfc_write_tag_mask(1 << TAG);
        mfc_read_tag_status_all();
    }
    return 0;
}


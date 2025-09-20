#include <stdio.h>
#include <spu_mfcio.h>
#include <spu_intrinsics.h>
#include <libsync.h>

#define TAG 3

/* SPU initialization data */
typedef struct _control_block {
    cond_ea_t cashier;
    mutex_ea_t cashier_mutex, served_mutex;
    unsigned long long served_addr;
} control_block;

control_block cb __attribute__((aligned(128)));

int main(unsigned long long speid, unsigned long long argp, unsigned long long envp)
{
    /* Get the control block from main memory */
    mfc_get(&cb, argp, sizeof(cb), TAG, 0, 0);
    mfc_write_tag_mask(1 << TAG);
    mfc_read_tag_status_all();

    /* Enter the store: get lock to wait for cashier */
    mutex_lock(cb.cashier_mutex);

    /* Wait for cashier */
    cond_wait(cb.cashier, cb.cashier_mutex);

    /* Allow others to wait for the cashier */
    mutex_unlock(cb.cashier_mutex);

    /* Leave the store: get lock to increment num_served */
    mutex_lock(cb.served_mutex);

    /* Increment the number of customers served */
    atomic_inc((atomic_ea_t)cb.served_addr);
    printf("Thread %llu incremented num_served to %u\n", speid, atomic_read((atomic_ea_t)cb.served_addr));

    /* Allow others to access num_served */
    mutex_unlock(cb.served_mutex);
    return 0;
}


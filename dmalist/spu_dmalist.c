#include <spu_mfcio.h>
#include <spu_intrinsics.h>

#define SIZE 4096   /* Max # if ints in a transfer */
#define TAG 3

/* Array to hold the received values */
unsigned int hold_array[SIZE * 4] __attribute__((aligned(128)));

int main(vector unsigned long long arg1, vector unsigned long long arg2, vector unsigned long long arg3)
{
    int i;
    unsigned long long get_addr, put_addr[4];

    /* Retrieve the five addresses from parameters */
    get_addr = spu_extract(arg1, 0);
    put_addr[0] = spu_extract(arg1, 1);
    put_addr[1] = spu_extract(arg2, 0);
    put_addr[2] = spu_extract(arg2, 1);
    put_addr[3] = spu_extract(arg3, 0);

    /* Create list elements for mfc_getl */
    mfc_list_element_t get_element[4];
    for (i = 0; i < 4; i++) {
        get_element[i].size = SIZE * sizeof(unsigned int);
        get_element[i].eal = mfc_ea2l(get_addr) + i * SIZE * sizeof(unsigned int);
    }

    /* Transfer data into LS */
    mfc_getlb(hold_array, get_addr, get_element, sizeof(get_element), TAG, 0, 0);
    mfc_write_tag_mask(1 << TAG);
    mfc_read_tag_status_all();

    /* Create list elements for mfc_putl */
    mfc_list_element_t put_element[4];
    for (i = 0; i < 4; i++) {
        put_element[i].size = SIZE * sizeof(unsigned int);
        put_element[i].eal = mfc_ea2l(put_addr[i]);
    }

    /* Transfer data out of LS */
    mfc_putl(hold_array, put_addr[0], put_element, sizeof(put_element), TAG, 0, 0);
    mfc_write_tag_mask(1 << TAG);
    mfc_read_tag_status_all();
    return 0;
}


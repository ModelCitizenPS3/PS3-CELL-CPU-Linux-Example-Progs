#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>

extern spe_program_handle_t spu_basic;  /* Program handle */

int main(int argc, char **argv)
{
    spe_context_ptr_t ctx;      /* Context */
    unsigned int entry_point;   /* Start address */
    int retval;                 /* Return value */
    spe_stop_info_t stop_info;  /* Stop info */

    /* Create the SPE Context */
    ctx = spe_context_create(0, NULL);
    if (!ctx) {
        perror("spe_context_create");
        exit(1);
    }

    /* Load the program handle into the context */
    retval = spe_program_load(ctx, &spu_basic);
    if (retval) {
        perror("spe_program_load");
        exit(1);
    }

    /* Run the program inside the context */
    entry_point = SPE_DEFAULT_ENTRY;
    retval = spe_context_run(ctx, &entry_point, 0, NULL, NULL, &stop_info);
    if (retval < 0) {
        perror("spe_context_run");
        exit(1);
    }

    /* Deallocate the context */
    retval = spe_context_destroy(ctx);
    if (retval) {
        perror("spe_context_destroy");
        exit(1);
    }
    return 0;
}


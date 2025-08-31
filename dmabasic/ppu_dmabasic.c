#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>

extern spe_program_handle_t spu_dmabasic;

int main(int argc, char **argv)
{
    spe_context_ptr_t ctx;
    unsigned int entry_point;
    int retval;
    spe_stop_info_t stop_info;

    ctx = spe_context_create(0, NULL);
    if (!ctx) {
        perror("spe_context_create");
        exit(1);
    }

    retval = spe_program_load(ctx, &spu_dmabasic);
    if (retval) {
        perror("spe_program_load");
        exit(1);
    }

    entry_point = SPE_DEFAULT_ENTRY;
    char argp[128] = {0};
    retval = spe_context_run(ctx, &entry_point, 0, argp, NULL, &stop_info);
    if (retval < 0) {
        perror("spe_context_run");
        exit(1);
    }

    retval = spe_context_destroy(ctx);
    if (retval) {
        perror("spe_context_destroy");
        exit(1);
    }

    return 0;
}


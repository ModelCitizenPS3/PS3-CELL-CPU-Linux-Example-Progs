#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>
#include <pthread.h>

/* The data sent to the pthread */
typedef struct ppu_thread_data {
    spe_context_ptr_t speid;
    pthread_t pthread;
    void *argp;
} ppu_thread_data_t;

/* The function executed in the pthread */
void *ppu_thread_function(void *arg)
{
    ppu_thread_data_t *data = (ppu_thread_data_t *)arg;
    int retval;
    unsigned int entry = SPE_DEFAULT_ENTRY;
    if ((retval = spe_context_run(data->speid, &entry, 0, data->argp, NULL, NULL)) < 0) {
        perror("spe_context_run");
        exit(1);
    }
    pthread_exit(NULL);
}

/* SPU initialization data */
unsigned long long control_block;

/* SPU program handle */
extern spe_program_handle_t spu_threads;
ppu_thread_data_t data[16];

int main(int argc, char **argv)
{
    int i, retval, spus;

    /* Determine the number of available SPUs */
    spus = spe_cpu_info_get(SPE_COUNT_USABLE_SPES, 0);
    if (argc != 2) {
        printf("Usage: 'threads <1-%u>'\n", spus);
        exit(1);
    }
    else if ((atoi(argv[1]) < 1) || (atoi(argv[1]) > spus)) {
        printf("Usage: 'threads <1-%u>'\n", spus);
        exit(1);
    }
    else
        spus = atoi(argv[1]);

    /* Create a context and thread for each SPU */
    for (i = 0; i < spus; i++) {

        /* Create context */
        if ((data[i].speid = spe_context_create(0, NULL)) == NULL) {
            perror("spe_context_create");
            exit(1);
        }

        /* Load program into the context */
        if ((retval = spe_program_load(data[i].speid, &spu_threads)) != 0) {
            perror("spe_program_load");
            exit(1);
        }

        /* Initialize control block and thread data */
        control_block = i;
        data[i].argp = (void *)control_block;

        /* Create thread */
        if ((retval = pthread_create(&data[i].pthread, NULL, &ppu_thread_function, &data[i])) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    /* Wait for the threads to finish processing */
    for (i = 0; i < spus; i++) {
        if ((retval = pthread_join(data[i].pthread, NULL)) != 0) {
            perror("pthread_join");
            exit(1);
        }
        if ((retval = spe_context_destroy(data[i].speid)) != 0) {
            perror("spe_context_destroy");
            exit(1);
        }
    }
    return 0;
}


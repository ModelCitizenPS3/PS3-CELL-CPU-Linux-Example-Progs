#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>

#define MAX_EVENTS 16

extern spe_program_handle_t spu_events;     /* Program handle */

int main(int argc, char **argv)
{
    int i, event_count;
    spe_context_ptr_t ctx;                  /* Context */
    unsigned int entry_point;               /* Start address */
    int retval;                             /* Return value */
    spe_stop_info_t stop_info;              /* Stop info */

    spe_event_handler_ptr_t ehandler;       /* Event handler */
    spe_event_unit_t event;                 /* Event to be handled */
    spe_event_unit_t events[MAX_EVENTS];    /* Events to be received */

    /* Create the context */
    ctx = spe_context_create(SPE_EVENTS_ENABLE, NULL);
    if (!ctx) {
        perror("spe_context_create");
        exit(1);
    }

    /* Create an event handler and event */
    ehandler = spe_event_handler_create();
    event.spe = ctx;
    event.events = SPE_EVENT_SPE_STOPPED;
    spe_event_handler_register(ehandler, &event);

    /* Load the program handle into the context */
    entry_point = SPE_DEFAULT_ENTRY;
    retval = spe_program_load(ctx, &spu_events);
    if (retval) {
        perror("spe_program_load");
        exit(1);
    }

    /* Execute the program inside the context */
    retval = spe_context_run(ctx, &entry_point, 0, NULL, NULL, &stop_info);
    if (retval < 0) {
        perror("spe_context_run");
        exit(1);
    }

    /* Receive events and analyze stop information */
    event_count = spe_event_wait(ehandler, events, MAX_EVENTS, 10);
    printf("Number of events detected: %d\n", event_count);
    for (i = 0; i < event_count; i++) {
        if (events[i].events & SPE_EVENT_SPE_STOPPED) {
            printf("Received SPE_EVENT_SPE_STOPPED\n");
            spe_stop_info_read(events[i].spe, &stop_info);
            printf("Stop reason: ");
            switch (stop_info.stop_reason) {
                case 1:
                    printf("SPE_EXIT\n");
                    break;
                case 2:
                    printf("SPE_STOP_AND_SIGNAL\n");
                    break;
                case 3:
                    printf("SPE_RUNTIME_ERROR\n");
                    break;
                case 4:
                    printf("SPE_RUNTIME_EXCEPTION\n");
                    break;
                case 5:
                    printf("SPE_RUNTIME_FATAL\n");
                    break;
                case 6:
                    printf("SPE_CALLBACK_ERROR\n");
                    break;
            }
            printf("Exit code: %d\n", stop_info.result.spe_exit_code);
        }
    }

    /* Free the event handler and context */
    spe_event_handler_destroy(ehandler);
    retval = spe_context_destroy(ctx);
    return 0;
}


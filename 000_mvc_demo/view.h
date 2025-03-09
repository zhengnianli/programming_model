#ifndef VIEW_H
#define VIEW_H

#include <pthread.h>
#include "message_queue.h"

typedef struct View 
{
    int current_page;
    pthread_t thread;
    mqd_t mq;
} View;

View* create_view(void);
void start_view(View *view);
void stop_view(View *view);

#endif
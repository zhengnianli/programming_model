#ifndef MODEL_H
#define MODEL_H

#include <pthread.h>
#include "message_queue.h"
#include "config.h"

#define MAX_CONFIGS 10

typedef struct Model 
{
    Config configs[MAX_CONFIGS];
    int num_configs;
    pthread_t thread;
    mqd_t mq;
} Model;

Model* create_model(void);
void start_model(Model *model);
void stop_model(Model *model);

#endif
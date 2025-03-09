#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "model.h"

static void update_config(Model *model, int config_index) 
{
    const Config *config = get_config(model->configs, config_index, model->num_configs);

    if (config) 
    {
        char msg[MAX_MSG_SIZE] = {0};

        snprintf(msg, sizeof(msg), "CONFIG:%s:%d", config->name, config->value);
        send_message(model->mq, msg);
    }
}

void* model_thread_func(void *arg) 
{
    Model *model = (Model *)arg;
    char buf[MAX_MSG_SIZE] = {0};

    while (1) 
    {
        ssize_t bytes_received = receive_message(model->mq, buf);
        buf[bytes_received] = '\0';
        
        if (strncmp(buf, "READ_CONFIG:", 12) == 0) 
        {
            int config_index = atoi(buf + 12);
            update_config(model, config_index);
        }
    }

    return NULL;
}

Model* create_model(void) 
{
    Model *model = (Model *)malloc(sizeof(Model));

    if (model == NULL) 
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    model->num_configs = MAX_CONFIGS;
    init_configs(model->configs, model->num_configs);
    model->mq = init_message_queue();

    return model;
}

void start_model(Model *model) 
{
    if (pthread_create(&model->thread, NULL, model_thread_func, model) != 0) 
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
}

void stop_model(Model *model) 
{
    pthread_join(model->thread, NULL);
    close_message_queue(model->mq);
    free(model);
}
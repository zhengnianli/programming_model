#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "controller.h"
#include "message_queue.h"

#define PAGE_CONFIG_MAP_SIZE 10
static int page_config_map[PAGE_CONFIG_MAP_SIZE] = {0};

static void init_page_config_map(void) 
{
    for (int i = 0; i < PAGE_CONFIG_MAP_SIZE; i++) 
    {
        page_config_map[i] = i;
    }
}

void* controller_thread_func(void *arg) 
{
    Controller *controller = (Controller *)arg;
    char input[10] = {0};

    init_page_config_map();

    while (1) 
    {
        printf("输入页面索引 (0 - %d) 显示对应页面配置，输入 'q' 退出程序: ", PAGE_CONFIG_MAP_SIZE - 1);
        fgets(input, sizeof(input), stdin);
        if (input[0] >= '0' && input[0] <= '9') 
        {
            int page_index = atoi(input);

            if (page_index >= 0 && page_index < PAGE_CONFIG_MAP_SIZE) 
            {
                controller->view->current_page = page_index;
                int config_index = page_config_map[page_index];

                char msg[MAX_MSG_SIZE] = {0};

                snprintf(msg, sizeof(msg), "READ_CONFIG:%d", config_index);
                send_message(controller->model->mq, msg);
            } 
            else 
            {
                printf("无效的页面索引，请重新输入。\n");
            }
        } 
        else if (input[0] == 'q') 
        {
            stop_model(controller->model);
            stop_view(controller->view);
            close_message_queue(controller->mq);
            exit(0);
        }
    }

    return NULL;
}

Controller* create_controller(Model *model, View *view) 
{
    Controller *controller = (Controller *)malloc(sizeof(Controller));

    if (controller == NULL) 
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    controller->model = model;
    controller->view = view;
    controller->mq = init_message_queue();

    return controller;
}

void start_controller(Controller *controller) 
{
    if (pthread_create(&controller->thread, NULL, controller_thread_func, controller) != 0) 
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
}

void stop_controller(Controller *controller) 
{
    pthread_join(controller->thread, NULL);
    close_message_queue(controller->mq);
    free(controller);
}
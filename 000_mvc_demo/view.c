#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view.h"

static void display_page(View *view, const char *config_name, int config_value) 
{
    printf("当前页面: %d\n", view->current_page);
    printf("业务配置: %s, 值: %d\n", config_name, config_value);
}

void* view_thread_func(void *arg) 
{
    View *view = (View *)arg;
    char buf[MAX_MSG_SIZE] = {0};

    while (1) 
    {
        ssize_t bytes_received = receive_message(view->mq, buf);
        buf[bytes_received] = '\0';

        if (strncmp(buf, "CONFIG:", 7) == 0) 
        {
            char config_name[32] = {0};
            int config_value = 0;
            sscanf(buf + 7, "%[^:]:%d", config_name, &config_value);
            display_page(view, config_name, config_value);
        }
    }

    return NULL;
}

View* create_view(void) 
{
    View *view = (View *)malloc(sizeof(View));

    if (view == NULL) 
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    view->current_page = 1;
    view->mq = init_message_queue();

    return view;
}

void start_view(View *view) 
{
    if (pthread_create(&view->thread, NULL, view_thread_func, view) != 0) 
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
}

void stop_view(View *view) 
{
    pthread_join(view->thread, NULL);
    close_message_queue(view->mq);

    free(view);
}
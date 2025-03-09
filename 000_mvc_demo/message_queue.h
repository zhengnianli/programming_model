#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_QUEUE_NAME "/ui_switch_queue"
#define MAX_MSG_SIZE 128
#define MAX_MSG_NUM 10

mqd_t init_message_queue(void);
void close_message_queue(mqd_t mq);
void send_message(mqd_t mq, const char *msg);
ssize_t receive_message(mqd_t mq, char *buf);

#endif
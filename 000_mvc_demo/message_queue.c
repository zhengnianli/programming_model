#include "message_queue.h"

mqd_t init_message_queue(void) 
{
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MSG_NUM;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    mqd_t mq = mq_open(MSG_QUEUE_NAME, O_CREAT | O_RDWR, 0666, &attr);
    if (mq == (mqd_t)-1) 
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    return mq;
}

void close_message_queue(mqd_t mq) 
{
    if (mq_close(mq) == -1) 
    {
        perror("mq_close");
        exit(EXIT_FAILURE);
    }

    if (mq_unlink(MSG_QUEUE_NAME) == -1) 
    {
        perror("mq_unlink");
        exit(EXIT_FAILURE);
    }
}

void send_message(mqd_t mq, const char *msg) 
{
    if (mq_send(mq, msg, strlen(msg), 0) == -1) 
    {
        perror("mq_send");
        exit(EXIT_FAILURE);
    }
}

ssize_t receive_message(mqd_t mq, char *buf) 
{
    ssize_t bytes_received = mq_receive(mq, buf, MAX_MSG_SIZE, NULL);
    
    if (bytes_received == -1) 
    {
        perror("mq_receive");
        exit(EXIT_FAILURE);
    }

    return bytes_received;
}
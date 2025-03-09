#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "view.h"

typedef struct Controller 
{
    Model *model;
    View *view;
    pthread_t thread;
    mqd_t mq;
} Controller;

Controller* create_controller(Model *model, View *view);
void start_controller(Controller *controller);
void stop_controller(Controller *controller);

#endif
// 微信公众号：嵌入式大杂烩
#include <stdio.h>
#include "model.h"
#include "view.h"
#include "controller.h"

int main(void) 
{
    Model *model = create_model();
    View *view = create_view();
    Controller *controller = create_controller(model, view);

    start_model(model);
    start_view(view);
    start_controller(controller);

    pthread_exit(NULL);

    return 0;
}
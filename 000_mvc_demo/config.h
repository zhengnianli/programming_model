#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONFIG_NAME_LEN 32

typedef struct 
{
    char name[MAX_CONFIG_NAME_LEN];
    int value;
} Config;

void init_configs(Config *configs, int num_configs);
const Config* get_config(const Config *configs, int index, int num_configs);

#endif
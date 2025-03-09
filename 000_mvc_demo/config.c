#include "config.h"

void init_configs(Config *configs, int num_configs) 
{
    for (int i = 0; i < num_configs; i++) 
    {
        snprintf(configs[i].name, MAX_CONFIG_NAME_LEN, "Config%d", i + 1);
        configs[i].value = i + 1;
    }
}

const Config* get_config(const Config *configs, int index, int num_configs) 
{
    if (index >= 0 && index < num_configs) 
    {
        return &configs[index];
    }
    
    return NULL;
}
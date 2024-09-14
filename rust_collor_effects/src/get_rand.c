#include"get_rand.h"

#include<stdlib.h>

uint32_t get_rand(uint32_t range_max)
{
    return range_max * ((float)rand() / RAND_MAX);
}


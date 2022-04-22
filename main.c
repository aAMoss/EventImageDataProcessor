// main.c

// Standard Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Posix Headers
#include <sys/types.h>
#include <sys/stat.h>


// Program Specific Headers
#include "main.h"


#define EVENTS_PER_SAMPLE_MAX 10000
#define DATA_SAMPLES_CLASSES 10
#define EVENT_BUFF_SIZE 5







int main(void)
{
    
    
    
    
    puts("Start");
    puts("Testing: dataio_SetOutputDataName");
    
    config_get_out_dir_label(output_dir_label);
    
    printf("Data Output Label is: %s\n", output_dir_label);
    
    
    
    
    
    return 0;
}







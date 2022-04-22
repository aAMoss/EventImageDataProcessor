// main.c

// Standard Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// p_osix Headers
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
    
    //config_get_out_dir_label(output_dir_label);
    config_set_event_packet_vars(&packet_size, &packet_overlap);
    
    
    printf("Packet size: %d\tPacket Overlap: %d\n", packet_size, packet_overlap);
    
    
    
    
    
    return 0;
}




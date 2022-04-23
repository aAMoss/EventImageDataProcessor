// main.c

// Standard Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Posix Headers
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


// Program Specific Headers
#include "main.h"


#define EVENTS_PER_SAMPLE_MAX 10000

#define EVENT_BUFF_SIZE 5


// Directory paths for the input data
#define TESTINDIR "./N-MNIST_test/Test/"
#define TRAININDIR "./N-MNIST_test/Train/"








int main(void)
{


    
    
    puts("\nStart Test\n\n\n");
    
    config_get_out_dir_label(output_dir_label);
    
    
    config_set_event_packet_vars(&packet_size, &packet_overlap);
    printf("Packet size: %d\tPacket Overlap: %d\n", packet_size, packet_overlap);
    
    config_create_output_dir(output_dir_label, output_dir_name);
    
   
    
    return 0;
}



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
#define TEST_IN_DIR "./N-MNIST_test/Test/"
#define TRAIN_IN_DIR "./N-MNIST_test/Train/"

// Input Directory and File Structures
DIR *DataInputTargetDir;
struct dirent *DataInEntrySample;
FILE *EventSampleIn;






int main(void)
{


    
    
    puts("\nStart Test\n\n\n");
    
    config_get_out_dir_label(output_dir_label);
    
    
    config_set_event_packet_vars(&packet_size, &packet_overlap);
    printf("Packet size: %d\tPacket Overlap: %d\n", packet_size, packet_overlap);
    
    config_create_output_dir(output_dir_label, output_dir_name);
    
   
    
    return 0;
}



DIR *OpenDataInDirectory(DIR *DataInputTargetDir, int c)
{
    char dirclassnum[10] = "";
    char dirpathname[250] = "";
    
    // Creates the full directory path using strcat
    sprintf(dirclassnum, "%d", c);
    strcat(dirpathname, TESTINDIR);
    strcat(dirpathname, dirclassnum);
    
    
    // Opens the directory specificied by the directory path
    DataInputTargetDir = opendir(dirpathname);
    
    
    if(DataInputTargetDir == NULL)
    {
        puts("ERROR: Unable to read directory!");
        exit(EXIT_FAILURE);
    }
    
    
    printf("%s\n", dirpathname);
    
    return DataInputTargetDir;
}

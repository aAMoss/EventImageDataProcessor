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
#define CLASSES 10
#define EVENT_BUFF_SIZE 5


// Directory paths for the input data
#define TESTINDIR "./N-MNIST_test/Test/"
#define TRAININDIR "./N-MNIST_test/Train/"



void config_create_output_dir(char *output_dir_label, char *output_dir_name);

char output_dir_name[DATA_OUT_NAME_MAX] = "";


int main(void)
{


    
    
    puts("\nStart Test\n\n\n");
    
    config_get_out_dir_label(output_dir_label);
    printf("Data Output Label: %s\n", output_dir_label);
    
    config_set_event_packet_vars(&packet_size, &packet_overlap);
    printf("Packet size: %d\tPacket Overlap: %d\n", packet_size, packet_overlap);
    
    config_create_output_dir(output_dir_label, output_dir_name);
    
   
    
    return 0;
}



// Function to create the new output directories
void config_create_output_dir(char *output_dir_label, char *output_dir_name)
{
    // Static Strings
    char *s0 = "./";
    char *s1 = "/Test/";
    char *s2 = "/Train/";
    
    // Strings
    char s3[10] = "";
    char local_dir_name1[DATA_OUT_NAME_MAX] = "mkdir -p ";
    char local_dir_name2[DATA_OUT_NAME_MAX] = "mkdir -p ";
    
    // create directory path ./output_dir_name/
    strcat(output_dir_name, s0);
    strcat(output_dir_name, output_dir_label);
    printf("Output Data Label: %s\n", output_dir_name);


    // create directory ./output_dir_name/Test/
    strcat(local_dir_name1, output_dir_name);
    strcat(local_dir_name1, s1);
    system(local_dir_name1);

    // create directory ./output_dir_name/Train/
    strcat(local_dir_name2, output_dir_name);
    strcat(local_dir_name2, s2);
    system(local_dir_name2);

    // create directory ./output_dir_name/Test/CLASSES .. 0 1 2 3 ... 9
    // create directory ./output_dir_name/Train/CLASSES .. 0 1 2 3 ... 9
    for(int i = 0; i<CLASSES; i++)
    {
        sprintf(s3, "%d", i);
        strcat(local_dir_name1, s3);
        strcat(local_dir_name2, s3);

        system(local_dir_name1);
        system(local_dir_name2);

        local_dir_name1[strlen(local_dir_name1)-1] = '\0'; // removing the last character, the class number
        local_dir_name2[strlen(local_dir_name2)-1] = '\0';
    }
}

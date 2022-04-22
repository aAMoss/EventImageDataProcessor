// STANDARD HEADERS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// POSIX HEADERS
#include <sys/types.h>
#include <sys/stat.h>


// PROGRAM SPECIFIC HEADERS
#include "main.h"

#define DATA_OUT_NAME_MAX 200
#define EVENTS_PER_SAMPLE_MAX 10000
#define DATA_SAMPLES_CLASSES 10
#define EVENT_BUFF_SIZE 5


char output_dir_label[MAXNAME];

// Function to create the new output directories
void dataio_get_out_dir_label(char *output_dir_label);

int main(void)
{
    
    
    
    
    puts("Start");
    puts("Testing: dataio_SetOutputDataName");
    
    dataio_get_out_dir_label(output_dir_label);
    
    printf("Data Output Label is: %s\n", output_dir_label);
    
    
    
    
    
    
    
    
    return 0;
}



// Allows the user to set the name of the output data (data that has been processed and booleanized)
void dataio_get_out_dir_name(char *output_dir_name)
{
    char user_input[(DATA_OUT_NAME_MAX/4)];
    
    puts("Please enter a name for the data output directory.");
    printf("The name must be no more than %d characters.\n", (MAXDATAOUTNAME/4));

    fgets(UserInput, MAXDATAOUTNAME, stdin);
    strcpy(OutputDataName, UserInput);
}




// STANDARD HEADERS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// POSIX HEADERS
#include <sys/types.h>
#include <sys/stat.h>


// PROGRAM SPECIFIC HEADERS
#include "main.h"

#define MAXDATAOUTNAME 200

#define SAMPLEMAXSIZE 10000
#define DATACLASSES 10
#define EVENTBUFFSIZE 5

// Function to create the new output directories
void dataio_CreateOutputDataDirectories(char *OutputDataName);

int main(void)
{
    
    
    
    
    puts("Start");
    puts("Testing: dataio_SetOutputDataName");
    
    dataio_CreateOutputDataDirectories(OutputDataName)
    
    printf("Data Output Name is: %s\n", OutputDataName);
    
    
    
    
    
    
    
    
    return 0;
}



// Allows the user to set the name of the output data (data that has been processed and booleanized)
void dataio_SetOutputDataName(char *OutputDataName)
{
    char UserInput[(MAXDATAOUTNAME/4)];
    puts("Please enter a name for the data output directory.");
    printf("The name must be no more than %d characters.\n", (MAXDATAOUTNAME/4));

    fgets(UserInput, MAXDATAOUTNAME, stdin);
    strcpy(OutputDataName, UserInput);
}




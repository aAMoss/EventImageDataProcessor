// config.c

// Standard Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Program Specific Headers
#include "config.h"



// Allows the user to set the name of the output data (data that has been processed and booleanized)
void config_get_out_dir_label(char *output_dir_label)
{
    char user_input[(DATA_OUT_NAME_MAX/4)];
    
    puts("Please enter a name for the data output directory.");
    printf("The name must be no more than %d characters.\n", (DATA_OUT_NAME_MAX/4));

    fgets(user_input, DATA_OUT_NAME_MAX, stdin);
    strcpy(output_dir_label, user_input);
}




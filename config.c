// config.c

// Standard Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Program Specific Headers
#include "config.h"


// Variables
char output_dir_label[(DATA_OUT_NAME_MAX /2)] = "";
char output_dir_name[DATA_OUT_NAME_MAX] = "";

int packet_size = 0;
int packet_overlap = 0;


// Allows the user to set the name of the output data (data that has been processed and booleanized)
void config_get_out_dir_label(char *output_dir_label)
{
    char user_input[(DATA_OUT_NAME_MAX/4)];
    char time_string[100] = "";
    
    time_t t = time(NULL);
    strftime(time_string, sizeof(time_string), "%Y%m%d_%H%M%S_", localtime(&t));
    strcat(output_dir_label, time_string);
    
    puts("Please enter a name for the data output directory.");
    printf("The name must be no more than %d characters.\n", (DATA_OUT_NAME_MAX/4));

    fgets(user_input, (DATA_OUT_NAME_MAX/4), stdin);
    user_input[strcspn(user_input, "\n")] = '\0'; // removes the return key
    strcat(output_dir_label, user_input);
}


// Allows the user to set the number of events in each packet to be processed, and the overlap of the event packets (in number of events)
void config_set_event_packet_vars(int *packet_size, int *packet_overlap)
{
    int p_s = 0;
    int p_o = 0;
    int p_s_flag = 0;
    int p_o_flag = 0;
    
    while(p_s_flag < 1)
    {
        printf("Please enter the Event Packet Size.\nValue must be in the range 1 to 1000.\n");
       
        scanf("%d", &p_s);
        
        if(p_s < 1 || p_s > 1000)
        {
            printf("ERROR: Event Packet Size must be between 1 and 1000!\n");
        }
        else if (p_s >= 1 && p_s <= 1000)
        {
            *packet_size = p_s;
            p_s_flag++;
        }
    }
    
    while(p_o_flag < 1)
    {
        if(p_s == 1)
        {
            *packet_overlap = 0;
            break;
        }
        
        printf("Please enter the Event Packet Overlap.\nValue must be in the range 0 to %d.\n", (p_s - 1) );
       
        scanf("%d", &p_o);
        
        if(p_o < 0 || p_o > (p_s - 1) )
        {
            printf("ERROR: Event Packet Size must be between 0 and %d!\n", (p_s - 1) );
        }
        else if (p_o >= 0 && p_o < p_s)
        {
            *packet_overlap = p_o;
            p_o_flag++;
        }
    }
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

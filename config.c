// config.c

// Standard Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Program Specific Headers
#include "config.h"


// Variables
char output_dir_label[(DATA_OUT_NAME_MAX /2)];


int packet_size = 0;
int packet_overlap = 0;


// Allows the user to set the name of the output data (data that has been processed and booleanized)
void config_get_out_dir_label(char *output_dir_label)
{
    char user_input[(DATA_OUT_NAME_MAX/4)];
    
    puts("Please enter a name for the data output directory.");
    printf("The name must be no more than %d characters.\n", (DATA_OUT_NAME_MAX/4));

    fgets(user_input, (DATA_OUT_NAME_MAX/4), stdin);
    user_input[strcspn(user_input, "\n")] = '\0'; // removes the return key
    
    
    time_t t = time(NULL);
    
    //struct tm time_buf;
    char time_string[100] = "";
    
    //asctime_s(str,sizeof str,localtime_s(&t, &buf));
    strftime(time_string, sizeof(time_string), "%Y%m%d_%H%M%S_", localtime(&t));
    printf("local: %s\n", time_string);
   // Time???
    
    
    strcat(output_dir_label, time_string);
    
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




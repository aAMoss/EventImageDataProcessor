// idfe.c - inter (packet) dynamics feature extraction

// Standard Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Posix Headers
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Program Specific Headers
#include "idfe.h"




// functions - zeroing
void idfe_zero_event_frames(int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y])
{
    for (int i = 0; i < MAXFRAME_X; i++)
    {

        for (int j = 0; j < MAXFRAME_Y; j++)
        {
            EventFrameCountALL[i][j] = 0;

        }

    }

}
                                    
void idfe_zero_prev_event_frame(int PrevEventFrameCountALL[MAXFRAME_X][MAXFRAME_Y])
{
    for (int i = 0; i < MAXFRAME_X; i++)
    {

        for (int j = 0; j < MAXFRAME_Y; j++)
        {
            PrevEventFrameCountALL[i][j] = 0;
        }

    }

}

void idfe_zero_inter_frame_events(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y])
{
    for (int i = 0; i < MAXFRAME_X; i++)
    {

        for (int j = 0; j < MAXFRAME_Y; j++)
        {
            OutputEventFrameBoolsALL[i][j] = 0;
        }

    }

}








// functions - packet features
void idfe_event_frame_count(int f_packet_size, int *packet_event_no, int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                       long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[])
{
    
    for(int e = 0; e < f_packet_size; e++) // for each event in the packet
    {
        
        for (int i = 0; i < MAXFRAME_X; i++) // for each x co-ordinate in event
        {
            
            for (int j = 0; j < MAXFRAME_Y; j++) // for each y co-ordinate in event
            {

                if (i == EventPacketX[e] && j == EventPacketY[e]) // accumulate if p = 1
                {
                    int temp1 = EventFrameCountALL[i][j];
                    
                    temp1++;
                    
                    EventFrameCountALL[i][j] = temp1;
                
                }
                  
              

            }
        
        }
        
    }
    
}







    
 

// functions - inter-packet features
void idfe_create_inter_frame_events(int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                     int PrevEventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                     int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y])
                                   
{
        
        // Creating bools/literals
        for(int i = 0; i < MAXFRAME_X; i++)
        {
            
            for(int j = 0; j < MAXFRAME_Y; j++)
            {
                
                if (EventFrameCountALL[i][j] > PrevEventFrameCountALL[i][j])
                {
                    OutputEventFrameBoolsALL[i][j] = 1;
                }
                
            
            }
            
        }
        
        //copying current frame values to previous frame
        for(int i = 0; i < MAXFRAME_X; i++)
        {
            
            for(int j = 0; j < MAXFRAME_Y; j++)
            {
                    PrevEventFrameCountALL[i][j] = EventFrameCountALL[i][j];
                   
            }
            
        }
        
}


    
    
    
    
 




//functions - print to terminal
void idfe_print_event_frame_count(int f_packet_size, int *packet_event_no, int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                      long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[])
{
    
        for (int i = 0; i < MAXFRAME_X; i++)
        {
    
            for (int j = 0; j < MAXFRAME_Y; j++)
            {
    
                printf("%d\t", EventFrameCountALL[i][j]);

            }
    
            printf("\n");
    
        }
    
        printf("\n");
        
}
    


void idfe_print_inter_frame_events(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y])
{
    
    printf("Positive and Negative Polarity\n");
    for(int i = 0; i < MAXFRAME_X; i++)
    {

        for(int j = 0; j < MAXFRAME_Y; j++)
        {
            printf("%d ", OutputEventFrameBoolsALL[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

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



// functions - inter-packet features
void idfe_inter_frame_events_counter(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                                          int inter_frame_events[MAXFRAME_X][MAXFRAME_Y])
{
        
        // Creating bools/literals
        for(int i = 0; i < MAXFRAME_X; i++)
        {
            
            for(int j = 0; j < MAXFRAME_Y; j++)
            {
                
                if (OutputEventFrameBoolsALL[i][j] == 1)
                {
                    inter_frame_events[i][j]++;
                }


            }
            
        }
        
        
}




void idfe_print_inter_frame_events_counter(int inter_frame_events[MAXFRAME_X][MAXFRAME_Y])
{
    
        for (int i = 0; i < MAXFRAME_X; i++)
        {
    
            for (int j = 0; j < MAXFRAME_Y; j++)
            {
    
                printf("%d\t", inter_frame_events[i][j]);
              
            }
    
            printf("\n");
    
        }
    
        printf("\n");
        
}


void idfe_zero_inter_frame_events_counter(int inter_frame_events[MAXFRAME_X][MAXFRAME_Y])
{
    for (int i = 0; i < MAXFRAME_X; i++)
    {

        for (int j = 0; j < MAXFRAME_Y; j++)
        {
            inter_frame_events[i][j] = 0;
        }

    }

}






void idfe_inter_frame_events_segment_count(int inter_frame_events[MAXFRAME_X][MAXFRAME_Y],
                                           int seg_iframe_events[S_FEATURES][S_FEATURES])
{
    
    
    for(int i = 0; i < SEG_X; i++)
    {
        for(int j = 0; j < SEG_Y; j++)
        {
            
            
            count_segment_events(i, j, inter_frame_events, seg_iframe_events);
            
            
        }
        
    }
    
}


void count_segment_events(int seg_x, int seg_y,
                          int inter_frame_events[MAXFRAME_X][MAXFRAME_Y],
                          int seg_iframe_events[S_FEATURES][S_FEATURES] )
{
    
    int x_start = seg_x * SEG_A_X;
    int y_start = seg_y * SEG_A_Y;
    
    
    for(int i = x_start; i < (x_start + SEG_A_X); i ++)
    {
       
        for(int j = y_start; j < (y_start + SEG_A_Y); j++)
        {
            
            if( inter_frame_events[i][j] >= 1)
            {
                
                int temp = seg_iframe_events[seg_x][seg_y];
                temp = temp + inter_frame_events[i][j];
                seg_iframe_events[seg_x][seg_y] = temp;
                
            }
            
            
            
        }
        
        
        
    }
    
    
}


void idfe_zero_seg_iframe_events( int seg_iframe_events[S_FEATURES][S_FEATURES])
{
        
      
        for(int i = 0; i < S_FEATURES; i++)
        {
            
            for(int j = 0; j < S_FEATURES; j++)
            {
                
                seg_iframe_events[i][j] = 0;
                

            }
            
        }
        
        
}



void idfe_print_inter_frame_events_per_segment(int seg_iframe_events[S_FEATURES][S_FEATURES])
{
    
    printf("Interframe Events per Segment\n");
    for(int i = 0; i < SEG_X; i++)
    {
        
        
        
        for(int j = 0; j < SEG_Y; j++)
        {
            printf("Segment %d\t%d\t%d\n", i, j, seg_iframe_events[i][j]);
        
        }
        
        
    }
    
    
    
    
}



void idfe_threshold_create_literals(int seg_iframe_events[S_FEATURES][S_FEATURES], int idfe_output_literals[S_FEATURES][S_FEATURES])
{
    
    int check_seg_val = 0;
    int hold_seg_val = 0;
    int threshold_value = 0;
    
    
    for(int i = 0; i < SEG_X; i++)
    {
        
        for(int j = 0; j < SEG_Y; j++)
        {
            
            check_seg_val = seg_iframe_events[i][j];
            if (check_seg_val> hold_seg_val)
            {
                hold_seg_val = check_seg_val;
            }
        
        }
    
    }
    
    
    threshold_value = hold_seg_val / THRESHOLD_DIV;
    
    
    for(int i = 0; i < SEG_X; i++)
    {
        
        for(int j = 0; j < SEG_Y; j++)
        {
            
            if(seg_iframe_events[i][j] >= threshold_value)
            {
                idfe_output_literals[i][j] = 1;

            }
            
            if(seg_iframe_events[i][j] < threshold_value)
            {
                idfe_output_literals[i][j] = 0;
            }
            
        }
        
    }
    
    
    
    
    
    
}




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
void idfe_zero_EventFrameCounts(int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                     int EventFrameCountPOS[MAXFRAME_X][MAXFRAME_Y],
                                     int EventFrameCountNEG[MAXFRAME_X][MAXFRAME_Y])
{
    for (int i = 0; i < MAXFRAME_X; i++)
    {

        for (int j = 0; j < MAXFRAME_Y; j++)
        {
            EventFrameCountALL[i][j] = 0;
            EventFrameCountPOS[i][j] = 0;
            EventFrameCountNEG[i][j] = 0;
        }

    }

}
                                    
void idfe_zero_PrevEventFrameCounts(int PrevEventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                         int PrevEventFrameCountPOS[MAXFRAME_X][MAXFRAME_Y],
                                         int PrevEventFrameCountNEG[MAXFRAME_X][MAXFRAME_Y])
{
    for (int i = 0; i < MAXFRAME_X; i++)
    {

        for (int j = 0; j < MAXFRAME_Y; j++)
        {
            PrevEventFrameCountALL[i][j] = 0;
            PrevEventFrameCountPOS[i][j] = 0;
            PrevEventFrameCountNEG[i][j] = 0;
        }

    }

}

void idfe_zero_OutputEventFrameBools(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                                           int OutputEventFrameBoolsPOS[MAXFRAME_X][MAXFRAME_Y],
                                           int OutputEventFrameBoolsNEG[MAXFRAME_X][MAXFRAME_Y])
{
    for (int i = 0; i < MAXFRAME_X; i++)
    {

        for (int j = 0; j < MAXFRAME_Y; j++)
        {
            OutputEventFrameBoolsALL[i][j] = 0;
            OutputEventFrameBoolsPOS[i][j] = 0;
            OutputEventFrameBoolsNEG[i][j] = 0;
        }

    }

}

void idfe_zero_EventFrameDensity(float EventFrameDensityALL[MAXFRAME_X][MAXFRAME_Y],
                                     float EventFrameDensityPOS[MAXFRAME_X][MAXFRAME_Y],
                                     float EventFrameDensityNEG[MAXFRAME_X][MAXFRAME_Y])
{
    for (int i = 0; i < MAXFRAME_X; i++)
    {

        for (int j = 0; j < MAXFRAME_Y; j++)
        {
            EventFrameDensityALL[i][j] = 0;
            EventFrameDensityPOS[i][j] = 0;
            EventFrameDensityNEG[i][j] = 0;
        }

    }

}










// functions - packet features
void idfe_event_frame_count(int f_packet_size, int *packet_event_no, int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                       int EventFrameCountPOS[MAXFRAME_X][MAXFRAME_Y], int EventFrameCountNEG[MAXFRAME_X][MAXFRAME_Y],
                                       long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[])
{
    
    for(int e = 0; e < f_packet_size; e++) // for each event in the packet
    {
        
        for (int i = 0; i < MAXFRAME_X; i++) // for each x co-ordinate in event
        {
            
            for (int j = 0; j < MAXFRAME_Y; j++) // for each y co-ordinate in event
            {

                if (i == EventPacketX[e] && j == EventPacketY[e] && EventPacketP[e] == 1) // accumulate if p = 1
                {
                    int temp1 = EventFrameCountALL[i][j];
                    int temp2 = EventFrameCountPOS[i][j];
                    temp1++;
                    temp2++;
                    EventFrameCountALL[i][j] = temp1;
                    EventFrameCountPOS[i][j] = temp2;
                }

                if (i == EventPacketX[e] && j == EventPacketY[e] && EventPacketP[e] == 0) // accumulate if p = 0
                {
                    int temp1 = EventFrameCountALL[i][j];
                    int temp2 = EventFrameCountNEG[i][j];
                    temp1++;
                    temp2++;
                    EventFrameCountALL[i][j] = temp1;
                    EventFrameCountNEG[i][j] = temp2;
                }

            }
        
        }
        
    }
    
}

void idfe_event_frame_density(int f_packet_size, int *packet_event_no, float EventFrameDensityALL[MAXFRAME_X][MAXFRAME_Y],
                                  float EventFrameDensityPOS[MAXFRAME_X][MAXFRAME_Y], float EventFrameDensityNEG[MAXFRAME_X][MAXFRAME_Y],
                                  long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[])
{
    
    for(int e = 0; e < f_packet_size; e++) // for each event in the packet
    {
        
        for (int i = 0; i < MAXFRAME_X; i++) // for each x co-ordinate in event
        {
            
            for (int j = 0; j < MAXFRAME_Y; j++) // for each y co-ordinate in event
            {

                if (i == EventPacketX[e] && j == EventPacketY[e] && EventPacketP[e] == 1) // accumulate if p = 1
                {
                    float temp1 = EventFrameDensityALL[i][j];
                    float temp2 = EventFrameDensityPOS[i][j];
                    temp1++;
                    temp2++;
                    EventFrameDensityALL[i][j] = temp1;
                    EventFrameDensityPOS[i][j] = temp2;
                }

                if (i == EventPacketX[e] && j == EventPacketY[e] && EventPacketP[e] == 0) // accumulate if p = 0
                {
                    float temp1 = EventFrameDensityALL[i][j];
                    float temp2 = EventFrameDensityNEG[i][j];
                    temp1++;
                    temp2++;
                    EventFrameDensityALL[i][j] = temp1;
                    EventFrameDensityNEG[i][j] = temp2;
                }
                
            }
            
        }
        
    }
    
    // Normalizes to show event density spatial event density for the packet
    for (int i = 0; i < MAXFRAME_X; i++) // for each x co-ordinate in event
    {

        for (int j = 0; j < MAXFRAME_Y; j++) // for each y co-ordinate in event
        {
            float temp1 = EventFrameDensityALL[i][j];
            float temp2 = EventFrameDensityPOS[i][j];
            float temp3 = EventFrameDensityNEG[i][j];
            
            temp1 = temp1 / f_packet_size;
            temp2 = temp2 / f_packet_size;
            temp3 = temp3 / f_packet_size;
            
            EventFrameDensityALL[i][j] = temp1;
            EventFrameDensityPOS[i][j] = temp2;
            EventFrameDensityNEG[i][j] = temp3;
        }

    }
    
}

   





    
 

// functions - inter-packet features
void idfe_eframe_continuous_bool(int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                     int EventFrameCountPOS[MAXFRAME_X][MAXFRAME_Y],
                                     int EventFrameCountNEG[MAXFRAME_X][MAXFRAME_Y],
                                     int PrevEventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                     int PrevEventFrameCountPOS[MAXFRAME_X][MAXFRAME_Y],
                                     int PrevEventFrameCountNEG[MAXFRAME_X][MAXFRAME_Y],
                                     int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                                     int OutputEventFrameBoolsPOS[MAXFRAME_X][MAXFRAME_Y],
                                     int OutputEventFrameBoolsNEG[MAXFRAME_X][MAXFRAME_Y])
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
                
                if (EventFrameCountPOS[i][j] > PrevEventFrameCountPOS[i][j])
                {
                    OutputEventFrameBoolsPOS[i][j] = 1;
                }
                
                if (EventFrameCountNEG[i][j] > PrevEventFrameCountNEG[i][j])
                {
                    OutputEventFrameBoolsNEG[i][j] = 1;
                }

            }
            
        }
        
        //copying current frame values to previous frame
        for(int i = 0; i < MAXFRAME_X; i++)
        {
            
            for(int j = 0; j < MAXFRAME_Y; j++)
            {
                    PrevEventFrameCountALL[i][j] = EventFrameCountALL[i][j];
                    PrevEventFrameCountPOS[i][j] = EventFrameCountPOS[i][j];
                    PrevEventFrameCountNEG[i][j] = EventFrameCountNEG[i][j];
            }
            
        }
        
}


    
    
    
    
 




//functions - print to terminal
void idfe_print_event_frame_count(int f_packet_size, int *packet_event_no, int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                      int EventFrameCountPOS[MAXFRAME_X][MAXFRAME_Y], int EventFrameCountNEG[MAXFRAME_X][MAXFRAME_Y],
                                      long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[])
{
    
        for (int i = 0; i < MAXFRAME_X; i++)
        {
    
            for (int j = 0; j < MAXFRAME_Y; j++)
            {
    
                printf("%d\t", EventFrameCountALL[i][j]);
                //printf("%d\t", EventFrameCountPOS[i][j]);
                //printf("%d\t", EventFrameCountNEG[i][j]);
            }
    
            printf("\n");
    
        }
    
        printf("\n");
        
}
    
void idfe_print_event_frame_density(float EventFrameDensityALL[MAXFRAME_X][MAXFRAME_Y],
                                        float EventFrameDensityPOS[MAXFRAME_X][MAXFRAME_Y],
                                        float EventFrameDensityNEG[MAXFRAME_X][MAXFRAME_Y])
                                    
{
    
        for (int i = 0; i < MAXFRAME_X; i++)
        {
    
            for (int j = 0; j < MAXFRAME_Y; j++)
            {
    
                printf("%.5f\t", EventFrameDensityALL[i][j]);
                //printf("%.5f\t", EventFrameDensityPOS[i][j]);
                //printf("%.5f\t", EventFrameDensityNEG[i][j]);
            }
    
            printf("\n");
    
        }
    
        printf("\n");
    
}

void idfe_print_eframe_continuous_bool(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                                            int OutputEventFrameBoolsPOS[MAXFRAME_X][MAXFRAME_Y],
                                            int OutputEventFrameBoolsNEG[MAXFRAME_X][MAXFRAME_Y])
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
    
//    printf("Positive Polarity\n");
//    for(int i = 0; i < MAXFRAME_X; i++)
//    {
//
//        for(int j = 0; j < MAXFRAME_Y; j++)
//        {
//            printf("%d ", OutputEventFrameBoolsPOS[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
//
//    printf("Negative Polarity\n");
//    for(int i = 0; i < MAXFRAME_X; i++)
//    {
//
//        for(int j = 0; j < MAXFRAME_Y; j++)
//        {
//            printf("%d ", OutputEventFrameBoolsNEG[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
    
}

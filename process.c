// process.c

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
#include "process.h"

#define MAXFRAME_X 32
#define MAXFRAME_Y 32

#define F_DIV 2
#define REG_X 8
#define REG_Y 8


#define MIN_FRAME_X (MAXFRAME_X / F_DIV)
#define MIN_FRAME_Y (MAXFRAME_Y / F_DIV)

int f_select;

int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y];
int EventFrameCountPOS[MAXFRAME_X][MAXFRAME_Y];
int EventFrameCountNEG[MAXFRAME_X][MAXFRAME_Y];

int PrevEventFrameCountALL[MAXFRAME_X][MAXFRAME_Y];
int PrevEventFrameCountPOS[MAXFRAME_X][MAXFRAME_Y];
int PrevEventFrameCountNEG[MAXFRAME_X][MAXFRAME_Y];

int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y];
int OutputEventFrameBoolsPOS[MAXFRAME_X][MAXFRAME_Y];
int OutputEventFrameBoolsNEG[MAXFRAME_X][MAXFRAME_Y];

int MiniEventFrameBoolsALL[MIN_FRAME_X][MIN_FRAME_Y];
int MiniEventFrameBoolsPOS[MIN_FRAME_X][MIN_FRAME_Y];
int MiniEventFrameBoolsNEG[MIN_FRAME_X][MIN_FRAME_Y];

float EventFrameDensityALL[MAXFRAME_X][MAXFRAME_Y];
float EventFrameDensityPOS[MAXFRAME_X][MAXFRAME_Y];
float EventFrameDensityNEG[MAXFRAME_X][MAXFRAME_Y];



int MiniEventRegion[REG_X][REG_Y];

void features_event_frame_count(int f_packet_size, int *packet_event_no, int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                       int EventFrameCountPOS[MAXFRAME_X][MAXFRAME_Y], int EventFrameCountNEG[MAXFRAME_X][MAXFRAME_Y],
                                       long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[]);

void features_print_event_frame_count(int f_packet_size, int *packet_event_no, int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                             int EventFrameCountPOS[MAXFRAME_X][MAXFRAME_Y], int EventFrameCountNEG[MAXFRAME_X][MAXFRAME_Y],
                                             long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[]);


void features_zero_EventFrameCounts(int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                     int EventFrameCountPOS[MAXFRAME_X][MAXFRAME_Y],
                                     int EventFrameCountNEG[MAXFRAME_X][MAXFRAME_Y]);
                                    
void features_zero_PrevEventFrameCounts(int PrevEventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                         int PrevEventFrameCountPOS[MAXFRAME_X][MAXFRAME_Y],
                                         int PrevEventFrameCountNEG[MAXFRAME_X][MAXFRAME_Y]);
                                    
void features_zero_OutputEventFrameBools(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                                         int OutputEventFrameBoolsPOS[MAXFRAME_X][MAXFRAME_Y],
                                         int OutputEventFrameBoolsNEG[MAXFRAME_X][MAXFRAME_Y]);

void features_eframe_continuous_bool(int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                     int EventFrameCountPOS[MAXFRAME_X][MAXFRAME_Y],
                                     int EventFrameCountNEG[MAXFRAME_X][MAXFRAME_Y],
                                     int PrevEventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                     int PrevEventFrameCountPOS[MAXFRAME_X][MAXFRAME_Y],
                                     int PrevEventFrameCountNEG[MAXFRAME_X][MAXFRAME_Y],
                                     int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                                     int OutputEventFrameBoolsPOS[MAXFRAME_X][MAXFRAME_Y],
                                     int OutputEventFrameBoolsNEG[MAXFRAME_X][MAXFRAME_Y]);

void features_print_eframe_continuous_bool(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                                           int OutputEventFrameBoolsPOS[MAXFRAME_X][MAXFRAME_Y],
                                           int OutputEventFrameBoolsNEG[MAXFRAME_X][MAXFRAME_Y]);


void features_continuous_bool_min(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                                  int OutputEventFrameBoolsPOS[MAXFRAME_X][MAXFRAME_Y],
                                  int OutputEventFrameBoolsNEG[MAXFRAME_X][MAXFRAME_Y],
                                  int MiniEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y], int f_packet_size);


void features_event_frame_density(int f_packet_size, int *packet_event_no, float EventFrameDensityALL[MAXFRAME_X][MAXFRAME_Y],
                                  float EventFrameDensityPOS[MAXFRAME_X][MAXFRAME_Y], float EventFrameDensityNEG[MAXFRAME_X][MAXFRAME_Y],
                                  long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[]);


void features_print_event_frame_density(float EventFrameDensityALL[MAXFRAME_X][MAXFRAME_Y],
                                        float EventFrameDensityPOS[MAXFRAME_X][MAXFRAME_Y],
                                        float EventFrameDensityNEG[MAXFRAME_X][MAXFRAME_Y]);
    
void features_zero_EventFrameDensity(float EventFrameDensityALL[MAXFRAME_X][MAXFRAME_Y],
                                     float EventFrameDensityPOS[MAXFRAME_X][MAXFRAME_Y],
                                     float EventFrameDensityNEG[MAXFRAME_X][MAXFRAME_Y]);



void process_event_data(int sample_events,int packet_size, int packet_overlap, int packets_req, int last_packet_size, int c,
                        long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[])
{

    int byte_no = 0;
    int f_packet_size = 0;
    
    int event_no = 0;
    int packet_event_no = 0;
    
    
    
                                        
    features_zero_PrevEventFrameCounts(PrevEventFrameCountALL, PrevEventFrameCountPOS, PrevEventFrameCountNEG);
                                        
    
    
    
    // Run for N number of packets to extract all data
    for(int packet_no = 0; packet_no < packets_req; packet_no++)
    {
        
        
        // Zero the packet arrays
        dataio_zero_event_packet_arrays(EventPacketX,EventPacketY, EventPacketP,EventPacketT);
        features_zero_EventFrameCounts(EventFrameCountALL, EventFrameCountPOS, EventFrameCountNEG);
        features_zero_OutputEventFrameBools(OutputEventFrameBoolsALL, OutputEventFrameBoolsPOS, OutputEventFrameBoolsNEG);
        
        features_zero_EventFrameDensity(EventFrameDensityALL, EventFrameDensityPOS, EventFrameDensityNEG);
        
        // Select variables for first N-1 packets, and last Nth packet
        if(packet_no < (packets_req - 1))
        {
            byte_no = packet_no * (packet_size - packet_overlap) * EVENT_BUFF_SIZE;
            f_packet_size = packet_size;
            p_f_packet_size = &f_packet_size;
            packet_event_no = 0;
            
        } else
        if(packet_no == (packets_req - 1))
        {
            byte_no = (sample_events - last_packet_size) * EVENT_BUFF_SIZE;
            f_packet_size = last_packet_size;
            p_f_packet_size = &f_packet_size;
            packet_event_no = 0;
        }
        
        
        // Arrays to store int version of the literals/booleans, has to be called after f_packet)size is set
        int literals_raw[RAW_BOOL_MAX][f_packet_size];
        
        //printf("packet_no %d\t", packet_no);
        //printf("byte_no %d\t", byte_no);
        //printf("f_packet_size %d\n", f_packet_size);
        
        // Extract a packets worth of event data
        dataio_extract_event_packets(Sample_Input_File, byte_no, f_packet_size, &packet_event_no, EventPacketX,EventPacketY, EventPacketP,EventPacketT);
        
        
        // FEATURES - Comment out as necessary
        
        features_event_frame_density(f_packet_size, &packet_event_no,
                                     EventFrameDensityALL, EventFrameDensityPOS, EventFrameDensityNEG,
                                     EventPacketX, EventPacketY, EventPacketP, EventPacketT);
        
        features_print_event_frame_density(EventFrameDensityALL, EventFrameDensityPOS, EventFrameDensityNEG);
        
        
        
//
//        features_event_frame_count(f_packet_size, &packet_event_no,
//                                          EventFrameCountALL, EventFrameCountPOS, EventFrameCountNEG,
//                                          EventPacketX, EventPacketY, EventPacketP, EventPacketT);
//
//        features_eframe_continuous_bool(EventFrameCountALL, EventFrameCountPOS, EventFrameCountNEG,
//                                        PrevEventFrameCountALL, PrevEventFrameCountPOS, PrevEventFrameCountNEG,
//                                        OutputEventFrameBoolsALL, OutputEventFrameBoolsPOS, OutputEventFrameBoolsNEG);
//
//        features_print_event_frame_count(f_packet_size, &packet_event_no,
//                                                EventFrameCountALL, EventFrameCountPOS, EventFrameCountNEG,
//                                                EventPacketX, EventPacketY, EventPacketP, EventPacketT);
//        features_print_eframe_continuous_bool(OutputEventFrameBoolsALL, OutputEventFrameBoolsPOS, OutputEventFrameBoolsNEG);
        
        
        
        features_literals_raw_data(EventPacketX, EventPacketY, EventPacketP, EventPacketT,f_packet_size, c, literals_raw);
        dataio_print_to_file_literals_raw(Processed_Data_Output_File, literals_raw, p_f_packet_size);

        
//        // Print to terminal for checking output and debug
//        for(int a = 0; a < f_packet_size; a++)
//        {
//
//            printf("Packet Event No --> %d \t%lu\t%lu", a, EventPacketX[a],EventPacketY[a]);
//            printf("\t%lu\t%lu\t",EventPacketP[a],EventPacketT[a]);
//            for(int b = 0; b < RAW_BOOL_MAX; b++)
//            {
//
//                printf("%d", literals_raw[b][a]);
//
//            }
//
//            printf("\n");
//        }


    }
    
}


 
// need one function to create the features
// will that include some form of thresholding functions??

// need a function to create the booleans


// need a function for minimization


// need a function to print the boolenas/literals to the output directories



// all these functions should be generic enough that they can just be slotted into the process_event_data loop and work seamlessly for both test and training data




void features_event_frame_count(int f_packet_size, int *packet_event_no, int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
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

void features_event_frame_density(int f_packet_size, int *packet_event_no, float EventFrameDensityALL[MAXFRAME_X][MAXFRAME_Y],
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

void features_print_event_frame_density(float EventFrameDensityALL[MAXFRAME_X][MAXFRAME_Y],
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

void features_zero_EventFrameDensity(float EventFrameDensityALL[MAXFRAME_X][MAXFRAME_Y],
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

void features_print_event_frame_count(int f_packet_size, int *packet_event_no, int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
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


void features_zero_EventFrameCounts(int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
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
                                    
void features_zero_PrevEventFrameCounts(int PrevEventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
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
void features_zero_OutputEventFrameBools(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
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





void features_eframe_continuous_bool(int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
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


void features_print_eframe_continuous_bool(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                                            int OutputEventFrameBoolsPOS[MAXFRAME_X][MAXFRAME_Y],
                                            int OutputEventFrameBoolsNEG[MAXFRAME_X][MAXFRAME_Y])
{
    
    printf("Positive and Negative Polarity\n");
    for(int i = 0; i < MAXFRAME_X; i++)
    {

        for(int j = 0; j < MAXFRAME_Y; j++)
        {
            printf("%d", OutputEventFrameBoolsALL[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    printf("Positive Polarity\n");
    for(int i = 0; i < MAXFRAME_X; i++)
    {

        for(int j = 0; j < MAXFRAME_Y; j++)
        {
            printf("%d", OutputEventFrameBoolsPOS[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Negative Polarity\n");
    for(int i = 0; i < MAXFRAME_X; i++)
    {

        for(int j = 0; j < MAXFRAME_Y; j++)
        {
            printf("%d", OutputEventFrameBoolsNEG[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
}


void features_continuous_bool_min(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                                  int OutputEventFrameBoolsPOS[MAXFRAME_X][MAXFRAME_Y],
                                  int OutputEventFrameBoolsNEG[MAXFRAME_X][MAXFRAME_Y],
                                  int MiniEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                                  int f_packet_size)
{
   
    //a bool is generated if the number of events at the next packet exceeded the previous, otherwise it was zero
    // areas where bools are generated are active areas, we're interested in those areas, like a heat map
    // so we could add the bools in a segment, and normalize to the number of packets
    // OR them, AND them, XOR them
    // going to count up the number of bools per segment, some form of thresholding, we've reduced the event space to the most active areas
    //segment and count, not unlike chrononetworks
}



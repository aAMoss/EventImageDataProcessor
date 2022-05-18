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

int f_select;

int EventPacketFrameALL[MAXFRAME_X][MAXFRAME_Y];
int EventPacketFramePOS[MAXFRAME_X][MAXFRAME_Y];
int EventPacketFrameNEG[MAXFRAME_X][MAXFRAME_Y];

int PrevEventPacketFrameALL[MAXFRAME_X][MAXFRAME_Y];
int PrevEventPacketFramePOS[MAXFRAME_X][MAXFRAME_Y];
int PrevEventPacketFrameNEG[MAXFRAME_X][MAXFRAME_Y];

int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y];
int OutputEventFrameBoolsPOS[MAXFRAME_X][MAXFRAME_Y];
int OutputEventFrameBoolsNEG[MAXFRAME_X][MAXFRAME_Y];

void features_event_packet_accumulator(int f_packet_size, int *packet_event_no, int EventPacketFrameALL[MAXFRAME_X][MAXFRAME_Y],
                                       int EventPacketFramePOS[MAXFRAME_X][MAXFRAME_Y], int EventPacketFrameNEG[MAXFRAME_X][MAXFRAME_Y],
                                       long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[]);

void features_print_accumulated_event_packet(int f_packet_size, int *packet_event_no, int EventPacketFrameALL[MAXFRAME_X][MAXFRAME_Y],
                                             int EventPacketFramePOS[MAXFRAME_X][MAXFRAME_Y], int EventPacketFrameNEG[MAXFRAME_X][MAXFRAME_Y],
                                             long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[]);


void features_zero_array(int EventPacketFrameALL[MAXFRAME_X][MAXFRAME_Y],
                         int EventPacketFramePOS[MAXFRAME_X][MAXFRAME_Y],
                         int EventPacketFrameNEG[MAXFRAME_X][MAXFRAME_Y],
                         int PrevEventPacketFrameALL[MAXFRAME_X][MAXFRAME_Y],
                         int PrevEventPacketFramePOS[MAXFRAME_X][MAXFRAME_Y],
                         int PrevEventPacketFrameNEG[MAXFRAME_X][MAXFRAME_Y],
                         int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                         int OutputEventFrameBoolsPOS[MAXFRAME_X][MAXFRAME_Y],
                         int OutputEventFrameBoolsNEG[MAXFRAME_X][MAXFRAME_Y]);

void features_eframe_continuous_bool(int EventPacketFrameALL[MAXFRAME_X][MAXFRAME_Y],
                                     int EventPacketFramePOS[MAXFRAME_X][MAXFRAME_Y],
                                     int EventPacketFrameNEG[MAXFRAME_X][MAXFRAME_Y],
                                     int PrevEventPacketFrameALL[MAXFRAME_X][MAXFRAME_Y],
                                     int PrevEventPacketFramePOS[MAXFRAME_X][MAXFRAME_Y],
                                     int PrevEventPacketFrameNEG[MAXFRAME_X][MAXFRAME_Y],
                                     int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                                     int OutputEventFrameBoolsPOS[MAXFRAME_X][MAXFRAME_Y],
                                     int OutputEventFrameBoolsNEG[MAXFRAME_X][MAXFRAME_Y]);

void features_print_eframe_continuous_bool(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                                           int OutputEventFrameBoolsPOS[MAXFRAME_X][MAXFRAME_Y],
                                           int OutputEventFrameBoolsNEG[MAXFRAME_X][MAXFRAME_Y]);






void process_event_data(int sample_events,int packet_size, int packet_overlap, int packets_req, int last_packet_size, int c,
                        long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[])
{

    int byte_no = 0;
    int f_packet_size = 0;
    
    int event_no = 0;
    int packet_event_no = 0;
    
    features_zero_array(EventPacketFrameALL, EventPacketFramePOS, EventPacketFrameNEG,
                        PrevEventPacketFrameALL, PrevEventPacketFramePOS, PrevEventPacketFrameNEG,
                        OutputEventFrameBoolsALL, OutputEventFrameBoolsPOS, OutputEventFrameBoolsNEG);
    
    // Run for N number of packets to extract all data
    for(int packet_no = 0; packet_no < packets_req; packet_no++)
    {
        
        
        // Zero the packet arrays
        dataio_zero_event_packet_arrays(EventPacketX,EventPacketY, EventPacketP,EventPacketT);
        
        
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
        features_event_packet_accumulator(f_packet_size, &packet_event_no,
                                          EventPacketFrameALL, EventPacketFramePOS, EventPacketFrameNEG,
                                          EventPacketX, EventPacketY, EventPacketP, EventPacketT);
        
        features_eframe_continuous_bool(EventPacketFrameALL, EventPacketFramePOS, EventPacketFrameNEG,
                                        PrevEventPacketFrameALL, PrevEventPacketFramePOS, PrevEventPacketFrameNEG,
                                        OutputEventFrameBoolsALL, OutputEventFrameBoolsPOS, OutputEventFrameBoolsNEG);

        features_print_eframe_continuous_bool(OutputEventFrameBoolsALL, OutputEventFrameBoolsPOS, OutputEventFrameBoolsNEG);
        //features_print_accumulated_event_packet(f_packet_size, &packet_event_no, EventPacketFrameALL, EventPacketFramePOS, EventPacketFrameNEG,
        //                                        EventPacketX, EventPacketY, EventPacketP, EventPacketT);
        
        features_literals_raw_data(EventPacketX, EventPacketY, EventPacketP, EventPacketT,f_packet_size, c, literals_raw);
        
        // PRINT TO FILE - Comment out as necessary
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




void features_event_packet_accumulator(int f_packet_size, int *packet_event_no, int EventPacketFrameALL[MAXFRAME_X][MAXFRAME_Y],
                                       int EventPacketFramePOS[MAXFRAME_X][MAXFRAME_Y], int EventPacketFrameNEG[MAXFRAME_X][MAXFRAME_Y],
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
                    int temp1 = EventPacketFrameALL[i][j];
                    int temp2 = EventPacketFramePOS[i][j];
                    temp1++;
                    temp2++;
                    EventPacketFrameALL[i][j] = temp1;
                    EventPacketFramePOS[i][j] = temp2;
                }

                if (i == EventPacketX[e] && j == EventPacketY[e] && EventPacketP[e] == 0) // accumulate if p = 0
                {
                    int temp1 = EventPacketFrameALL[i][j];
                    int temp2 = EventPacketFrameNEG[i][j];
                    temp1++;
                    temp2++;
                    EventPacketFrameALL[i][j] = temp1;
                    EventPacketFrameNEG[i][j] = temp2;
                }

            }
        
        }
        
    }
    
}

void features_print_accumulated_event_packet(int f_packet_size, int *packet_event_no, int EventPacketFrameALL[MAXFRAME_X][MAXFRAME_Y],
                                       int EventPacketFramePOS[MAXFRAME_X][MAXFRAME_Y], int EventPacketFrameNEG[MAXFRAME_X][MAXFRAME_Y],
                                       long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[])
{
    
        for (int i = 0; i < MAXFRAME_X; i++)
        {
    
            for (int j = 0; j < MAXFRAME_Y; j++)
            {
    
                printf("%d\t", EventPacketFrameALL[i][j]);
    
            }
    
            printf("\n");
    
        }
    
        printf("\n");
    
    
}

void features_zero_array(int EventPacketFrameALL[MAXFRAME_X][MAXFRAME_Y],
                         int EventPacketFramePOS[MAXFRAME_X][MAXFRAME_Y],
                         int EventPacketFrameNEG[MAXFRAME_X][MAXFRAME_Y],
                         int PrevEventPacketFrameALL[MAXFRAME_X][MAXFRAME_Y],
                         int PrevEventPacketFramePOS[MAXFRAME_X][MAXFRAME_Y],
                         int PrevEventPacketFrameNEG[MAXFRAME_X][MAXFRAME_Y],
                         int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                         int OutputEventFrameBoolsPOS[MAXFRAME_X][MAXFRAME_Y],
                         int OutputEventFrameBoolsNEG[MAXFRAME_X][MAXFRAME_Y])
{
    for (int i = 0; i < MAXFRAME_X; i++)
    {

        for (int j = 0; j < MAXFRAME_Y; j++)
        {
            EventPacketFrameALL[i][j] = 0;
            EventPacketFramePOS[i][j] = 0;
            EventPacketFrameNEG[i][j] = 0;
            PrevEventPacketFrameALL[i][j] = 0;
            PrevEventPacketFramePOS[i][j] = 0;
            PrevEventPacketFrameNEG[i][j] = 0;
            OutputEventFrameBoolsALL[i][j] = 0;
            OutputEventFrameBoolsPOS[i][j] = 0;
            OutputEventFrameBoolsNEG[i][j] = 0;
        }

    }

}


void features_eframe_continuous_bool(int EventPacketFrameALL[MAXFRAME_X][MAXFRAME_Y],
                                     int EventPacketFramePOS[MAXFRAME_X][MAXFRAME_Y],
                                     int EventPacketFrameNEG[MAXFRAME_X][MAXFRAME_Y],
                                     int PrevEventPacketFrameALL[MAXFRAME_X][MAXFRAME_Y],
                                     int PrevEventPacketFramePOS[MAXFRAME_X][MAXFRAME_Y],
                                     int PrevEventPacketFrameNEG[MAXFRAME_X][MAXFRAME_Y],
                                     int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                                     int OutputEventFrameBoolsPOS[MAXFRAME_X][MAXFRAME_Y],
                                     int OutputEventFrameBoolsNEG[MAXFRAME_X][MAXFRAME_Y])
{
    
    // Creating bools/literals
    for(int i = 0; i < MAXFRAME_X; i++)
    {
        
        for(int j = 0; j < MAXFRAME_Y; j++)
        {
            
            if (EventPacketFrameALL[i][j] > PrevEventPacketFrameALL[i][j])
            {
                OutputEventFrameBoolsALL[i][j] = 1;
            }
            
            if (EventPacketFramePOS[i][j] > PrevEventPacketFramePOS[i][j])
            {
                OutputEventFrameBoolsPOS[i][j] = 1;
            }
            
            if (EventPacketFrameNEG[i][j] > PrevEventPacketFrameNEG[i][j])
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
                PrevEventPacketFrameALL[i][j] = EventPacketFrameALL[i][j];
                PrevEventPacketFramePOS[i][j] = EventPacketFramePOS[i][j];
                PrevEventPacketFrameNEG[i][j] = EventPacketFrameNEG[i][j];
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


void dataio_print_to_file_eframe_continuous_bool(FILE *Processed_Data_Output_File, int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y], int c)
{
    char buf[2] = "";
    char *space = " ";
    int  literals = MAXFRAME_X * MAXFRAME_Y;
    char line[(2 * literals) + 1];
    
//    switch (c)
//    {
//        case 0: p
//
//
//
//
//
//    }
//    char class0 = "0000";
//    char class1 = "0001";
//    char class2 = "0010";
//    char class3 = "0011";
//    char class4 = "0100";
//    char class5 = "0101";
//    char class6 = "0110";
//    char class7 = "0111";
//    char class8 = "1000";
//    char class9 = "1001";
//
    
    for(int i = 0; i < MAXFRAME_X; i++)
    {
        
        for(int j = 0; j < MAXFRAME_Y; j++)
        {
                fprintf(Processed_Data_Output_File, "%d ", OutputEventFrameBoolsALL[i][j]);
        }
        
       // fprintf(
        fprintf(Processed_Data_Output_File, "\n");
                
    }
    
   
    //        for(int b = 0; b < RAW_BOOL_MAX; b++)
    //        {
    //            sprintf(buf, "%d", literals_raw[b][a]);
    //            strcat(line,buf);
    //            memset(buf,0,sizeof(buf));
    //            if( b < (RAW_BOOL_MAX - 1) )
    //            {
    //            strcat(line,space);
    //            }
    //
    //        }
    //
    //        fprintf(Processed_Data_Output_File, "%s\n", line);
    //        memset(line,0,sizeof(line));
    //
    //    }
    
    
}


//void dataio_print_to_file_literals_raw(FILE *Processed_Data_Output_File, int literals_raw[RAW_BOOL_MAX][*p_f_packet_size], int *p_f_packet_size)
//{
//
//    char buf[2] = "";
//    char *space = " ";
//    char line[(2 * RAW_BOOL_MAX) + 1];
//    int local_packet_size = *p_f_packet_size;
//
//    for(int a = 0; a < local_packet_size; a++)
//    {
//
//        for(int b = 0; b < RAW_BOOL_MAX; b++)
//        {
//            sprintf(buf, "%d", literals_raw[b][a]);
//            strcat(line,buf);
//            memset(buf,0,sizeof(buf));
//            if( b < (RAW_BOOL_MAX - 1) )
//            {
//            strcat(line,space);
//            }
//
//        }
//
//        fprintf(Processed_Data_Output_File, "%s\n", line);
//        memset(line,0,sizeof(line));
//
//    }
//
//}

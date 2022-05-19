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



int f_select;





int MiniEventRegion[REG_X][REG_Y];





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
        
        
        // PACKET FEATURES - Comment out as necessary
        
        features_event_frame_count(f_packet_size, &packet_event_no,
                                          EventFrameCountALL, EventFrameCountPOS, EventFrameCountNEG,
                                          EventPacketX, EventPacketY, EventPacketP, EventPacketT);
        
        features_event_frame_density(f_packet_size, &packet_event_no,
                                     EventFrameDensityALL, EventFrameDensityPOS, EventFrameDensityNEG,
                                     EventPacketX, EventPacketY, EventPacketP, EventPacketT);
        
        // PACKET-TO-PACKET FEATURES
        features_eframe_continuous_bool(EventFrameCountALL, EventFrameCountPOS, EventFrameCountNEG,
                                        PrevEventFrameCountALL, PrevEventFrameCountPOS, PrevEventFrameCountNEG,
                                        OutputEventFrameBoolsALL, OutputEventFrameBoolsPOS, OutputEventFrameBoolsNEG);
        
        
        
        
        // PRINT FEATURES - comment out as necessary

        //features_print_event_frame_count(f_packet_size, &packet_event_no,
        //                                        EventFrameCountALL, EventFrameCountPOS, EventFrameCountNEG,
        //                                        EventPacketX, EventPacketY, EventPacketP, EventPacketT);
        
        //features_print_event_frame_density(EventFrameDensityALL, EventFrameDensityPOS, EventFrameDensityNEG);
        
        
        
        // PRINT PACKET-TO-PACKET FEATURES

        features_print_eframe_continuous_bool(OutputEventFrameBoolsALL, OutputEventFrameBoolsPOS, OutputEventFrameBoolsNEG);
        
        
        //Other
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



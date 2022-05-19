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

// patch D x D
#define PATCH_D 7

// max patch D origin 0,0 postion
#define PATCH_X_MAX (MAXFRAME_X - PATCH_D)
#define PATCH_Y_MAX (MAXFRAME_Y - PATCH_D)
#define PATCH_X_MIN 0
#define PATCH_Y_MIN 0
// 32 -7 = 25 , can go 0 - 24 in both dimensions

#define B_FEATURES 4


int binary_features[B_FEATURES];

void features_binary_patches(int f_packet_size, long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[]);

void features_binary_patches(int f_packet_size, long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[])
{
    // Zero Patch Origin Coords
    int patch_o_px[B_FEATURES] = {0};
    int patch_o_py[B_FEATURES] = {0};
    int patch_o_nx[B_FEATURES] = {0};
    int patch_o_ny[B_FEATURES] = {0};
    
    // Zero Patch Max Coords
    int patch_m_px[B_FEATURES] = {0};
    int patch_m_py[B_FEATURES] = {0};
    int patch_m_nx[B_FEATURES] = {0};
    int patch_m_ny[B_FEATURES] = {0};
    
    
    
    
    // calculate patch origin and max coords
    for(int b = 0; b < B_FEATURES; b++)
    {
        //Positive Patch - origin coords
        patch_o_px[b] = ( rand() % (PATCH_X_MAX - PATCH_X_MIN + 1) ) + PATCH_X_MIN;
        patch_o_py[b] = ( rand() % (PATCH_Y_MAX - PATCH_Y_MIN + 1) ) + PATCH_Y_MIN;
        
        // Negative Patch - origin coords
        patch_o_nx[b] = ( rand() % (PATCH_X_MAX - PATCH_X_MIN + 1) ) + PATCH_X_MIN;
        patch_o_ny[b] = ( rand() % (PATCH_Y_MAX - PATCH_Y_MIN + 1) ) + PATCH_Y_MIN;
        
    }
    
    for(int b = 0; b < B_FEATURES; b++)
    {
        // Positive Patch - max coords
        patch_m_px[b] = patch_o_px[b] + PATCH_D;
        patch_m_py[b] = patch_o_py[b] + PATCH_D;
        
        // Negative Patch - max coords
        patch_m_nx[b] = patch_o_px[b] + PATCH_D;
        patch_m_ny[b] = patch_o_py[b] + PATCH_D;
        
        // Zero the counters
        binary_features[b] = 0;
    }
    
    
    
    
    
    for(int e = 0; e < f_packet_size; e++) //for every event in the packet
    {
        for(int i = 0; i < MAXFRAME_X; i++) //for each packet event x coord
        {
            for(int j = 0; j < MAXFRAME_Y; j++) //for each pachet event y coord
            {
                
                if( (EventPacketX[e] == i) &&  ( EventPacketY[e] == j) ) // check if there's an event at packet coords x y
                {
                    // Check Positive Patches
                    for(int p = 0; p < B_FEATURES; p++)
                    {
            
                        for(int k = patch_o_px[p]; k < patch_m_px[p]; k++) // for each patch x coord
                        {
                        
                            for(int l = patch_o_py[p]; l < patch_m_py[p]; k++) // for each patch y coord
                            {
                                
                               if( (EventPacketX[e] == k) && (EventPacketY[e] == l) )
                               {
                                   
                                   binary_features[p]++;
                                   
                               }
                                
                            } // end of patch y coords
           
                        } // end of patch x coords
                        
                    }// End check positive patch
                    
                    
                    // Check Negative Patches
                    for(int n = 0; n < B_FEATURES; n++)
                    {
                        
                        for(int k = patch_o_nx[n]; k < patch_m_nx[n]; k++) // for each patch x coord
                        {
                        
                            for(int l = patch_o_ny[n]; l < patch_m_ny[n]; k++) // for each patch y coord
                            {
                                
                               if( (EventPacketX[e] == k) && (EventPacketY[e] == l) )
                               {
                                   
                                   binary_features[n]--;

                               }
                              
                            } // end of patch y coords
          
                            
                        } // end of patch x coords
                        
                        
                    }// End check negative patch
                    
                    
                } //end if event is in patch
             
            } // end of packet event y coords
            
        } // end of packet event x coords
        
    } // end of packet events
        
}





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


 


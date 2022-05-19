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

#define B_FEATURES 128

int output_binary_literals[B_FEATURES];
int binary_features_count[B_FEATURES];
int patch_o_px[B_FEATURES];
int patch_o_py[B_FEATURES];
int patch_o_nx[B_FEATURES];
int patch_o_ny[B_FEATURES];
int patch_m_px[B_FEATURES];
int patch_m_py[B_FEATURES];
int patch_m_nx[B_FEATURES];
int patch_m_ny[B_FEATURES];

void features_zero_binary_variables(int output_binary_literals[], int binary_features_count[]);

void features_zero_patch_variables(int patch_o_px[],int patch_o_py[], int patch_o_nx[], int patch_o_ny[],
                                   int patch_m_px[],int patch_m_py[], int patch_m_nx[], int patch_m_ny[]);

void features_binary_patch_variables(int patch_o_px[], int patch_o_py[], int patch_o_nx[], int patch_o_ny[],
                                     int patch_m_px[],int patch_m_py[], int patch_m_nx[], int patch_m_ny[]);

void features_positive_binary_patch(int binary_features_count[], long int EventPacketX[], long int EventPacketY[],
                                    int patch_o_px[], int patch_o_py[], int patch_m_px[], int patch_m_py[]);

void features_negative_binary_patch(int binary_features_count[], long int EventPacketX[], long int EventPacketY[],
                                    int patch_o_nx[], int patch_o_ny[], int patch_m_nx[], int patch_m_ny[]);

void features_binary_patches_output(int output_binary_literals[], int binary_features_count[],
                                    int f_packet_size, long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[]);

void features_zero_binary_variables(int output_binary_literals[], int binary_features_count[])
{
    //Zero them first
    for(int b = 0; b < B_FEATURES; b++)
    {
        output_binary_literals[b] = 0;
        binary_features_count[b] = 0;
        
       
    }
    
}

void features_zero_patch_variables(int patch_o_px[],int patch_o_py[], int patch_o_nx[], int patch_o_ny[],
                                   int patch_m_px[],int patch_m_py[], int patch_m_nx[], int patch_m_ny[])
{
    //Zero them first
    for(int b = 0; b < B_FEATURES; b++)
    {
       
        patch_o_px[b] = 0;
        patch_o_py[b] = 0;
        patch_o_nx[b] = 0;
        patch_o_ny[b] = 0;
        
        patch_m_px[b] = 0;
        patch_m_py[b] = 0;
        patch_m_nx[b] = 0;
        patch_m_ny[b] = 0;
    }
    
}
                                   

void features_binary_patch_variables(int patch_o_px[], int patch_o_py[], int patch_o_nx[], int patch_o_ny[],
                                     int patch_m_px[],int patch_m_py[], int patch_m_nx[], int patch_m_ny[])
{

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

    }
    
}

void features_positive_binary_patch(int binary_features_count[],
                                    long int EventPacketX[], long int EventPacketY[],
                                    int patch_o_px[], int patch_o_py[], int patch_m_px[], int patch_m_py[])
{
    
    
    long int x = *EventPacketX;
    long int y = *EventPacketY;
    
    // Check Positive Patches
    for(int p = 0; p < B_FEATURES; p++)
    {

        for(int k = patch_o_px[p]; k < patch_m_px[p]; k++) // for each patch x coord
        {
        
            for(int l = patch_o_py[p]; l < patch_m_py[p]; l++) // for each patch y coord
            {
                
               if( (x == k) && (y == l) )
               {
                   
                   binary_features_count[p]++;
                   
               }
                
            } // end of patch y coords

        } // end of patch x coords
        
    }// End check positive patch
    
    
    
    
    
}

void features_negative_binary_patch(int binary_features_count[],
                                    long int EventPacketX[], long int EventPacketY[],
                                    int patch_o_nx[], int patch_o_ny[], int patch_m_nx[], int patch_m_ny[])
{
    
    long int x = *EventPacketX;
    long int y = *EventPacketY;
    
    
    // Check Negative Patches
    for(int n = 0; n < B_FEATURES; n++)
    {
        
        for(int i = patch_o_nx[n]; i < patch_m_nx[n]; i++) // for each patch x coord
        {
        
            for(int j = patch_o_ny[n]; j < patch_m_ny[n]; j++) // for each patch y coord
            {
                
               if( (x == i) && (y == j) )
               {
                   
                   binary_features_count[n]--;

               }
              
            } // end of patch y coords

            
        } // end of patch x coords
        
        
    }// End check negative patch

}


void features_binary_patches_output(int output_binary_literals[], int binary_features_count[], int f_packet_size,
                                    long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[])
{

    for(int e = 0; e < f_packet_size; e++) //for every event in the packet
    {
        for(int i = 0; i < MAXFRAME_X; i++) //for each packet event x coord
        {
            for(int j = 0; j < MAXFRAME_Y; j++) //for each pachet event y coord
            {
                
                if( (EventPacketX[e] == i) &&  ( EventPacketY[e] == j) ) // check if there's an event at packet coords x y
                {
                   
                    features_positive_binary_patch(binary_features_count, EventPacketX, EventPacketY, patch_o_px, patch_m_px, patch_o_py, patch_m_py);
                    
                    features_negative_binary_patch(binary_features_count, EventPacketX, EventPacketY, patch_o_nx, patch_m_nx, patch_o_ny, patch_m_ny);
                    
                    
                } //end if event is in patch
             
            } // end of packet event y coords
            
        } // end of packet event x coords
        
    } // end of packet events
        
    
    for ( int b = 0; b < B_FEATURES; b++)
    {
        
     if( binary_features_count[b] >= 1)
     {
         
         output_binary_literals[b] = 1;
        
     } else
     {
         
         
         output_binary_literals[b] = 0;
         
         
     }
        
        
        
    }
    
}





void process_event_data(int sample_events,int packet_size, int packet_overlap, int packets_req, int last_packet_size, int c,
                        long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[])
{

    int byte_no = 0;
    int f_packet_size = 0;
    
    int event_no = 0;
    int packet_event_no = 0;
    
    
    
    
    features_zero_patch_variables(patch_o_px,patch_o_py, patch_o_nx, patch_o_ny,
                                  patch_m_px,patch_m_py, patch_m_nx, patch_m_ny);

    features_binary_patch_variables(patch_o_px,patch_o_py, patch_o_nx, patch_o_ny,
                                    patch_m_px,patch_m_py, patch_m_nx, patch_m_ny);
    
                                        
    features_zero_PrevEventFrameCounts(PrevEventFrameCountALL, PrevEventFrameCountPOS, PrevEventFrameCountNEG);
    
    
    
    
    // Run for N number of packets to extract all data
    for(int packet_no = 0; packet_no < packets_req; packet_no++)
    {
        // Zero binary ouutput variables
        features_zero_binary_variables(output_binary_literals, binary_features_count);
        
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
        
        
        
       
 

        features_binary_patches_output(output_binary_literals, binary_features_count, f_packet_size, EventPacketX, EventPacketY, EventPacketP,EventPacketT);
        
        
        
        
      
        
            printf("PN %d\t", packet_no);
            
            for(int i = 0; i < B_FEATURES; i++)
            {
                
                printf("%d", output_binary_literals[i]);
        
            }
            printf("\n");
            
        
        
        
        // PACKET-TO-PACKET FEATURES
        features_eframe_continuous_bool(EventFrameCountALL, EventFrameCountPOS, EventFrameCountNEG,
                                        PrevEventFrameCountALL, PrevEventFrameCountPOS, PrevEventFrameCountNEG,
                                        OutputEventFrameBoolsALL, OutputEventFrameBoolsPOS, OutputEventFrameBoolsNEG);
        
        
        
        
        // PRINT - comment out as necessary

        //features_print_event_frame_count(f_packet_size, &packet_event_no,
        //                                        EventFrameCountALL, EventFrameCountPOS, EventFrameCountNEG,
        //                                        EventPacketX, EventPacketY, EventPacketP, EventPacketT);
        
        //features_print_event_frame_density(EventFrameDensityALL, EventFrameDensityPOS, EventFrameDensityNEG);
        
        //features_print_eframe_continuous_bool(OutputEventFrameBoolsALL, OutputEventFrameBoolsPOS, OutputEventFrameBoolsNEG);
        
        
        
        
        
        
        
        
        
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


 


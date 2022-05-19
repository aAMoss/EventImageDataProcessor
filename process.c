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



void process_event_data(int sample_events,int packet_size, int packet_overlap, int packets_req, int last_packet_size, int c,
                        long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[])
{

    // process event data initial variables
    int byte_no = 0;
    int f_packet_size = 0;
    int event_no = 0;
    int packet_event_no = 0;
    
    
    
    // patch binary feature extraction
    pbfe_zero_patch_variables(patch_o_px,patch_o_py, patch_o_nx, patch_o_ny,
                                  patch_m_px,patch_m_py, patch_m_nx, patch_m_ny);

    pbfe_binary_patch_variables(patch_o_px,patch_o_py, patch_o_nx, patch_o_ny,
                                    patch_m_px,patch_m_py, patch_m_nx, patch_m_ny);
    
    // homebrew feature extraction
    idfe_zero_PrevEventFrameCounts(PrevEventFrameCountALL, PrevEventFrameCountPOS, PrevEventFrameCountNEG);
    
    
    
    
    // Run for N number of packets to extract all data
    for(int packet_no = 0; packet_no < packets_req; packet_no++)
    {
        // Zeroing variables
        
        // patch binary feature extraction
        pbfe_zero_binary_variables(output_binary_literals, binary_features_count);
        
        // homebrew feature extraction
        dataio_zero_event_packet_arrays(EventPacketX,EventPacketY, EventPacketP,EventPacketT);
        idfe_zero_EventFrameCounts(EventFrameCountALL, EventFrameCountPOS, EventFrameCountNEG);
        idfe_zero_OutputEventFrameBools(OutputEventFrameBoolsALL, OutputEventFrameBoolsPOS, OutputEventFrameBoolsNEG);
        idfe_zero_EventFrameDensity(EventFrameDensityALL, EventFrameDensityPOS, EventFrameDensityNEG);
        
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
        
        
        // raw literals
        features_literals_raw_data(EventPacketX, EventPacketY, EventPacketP, EventPacketT,f_packet_size, c, literals_raw);
        dataio_print_to_file_literals_raw(Processed_Data_Output_File, literals_raw, p_f_packet_size);
        
        
        // patch binary feature extraction
        pbfe_binary_patches_output(output_binary_literals, binary_features_count, f_packet_size, EventPacketX, EventPacketY, EventPacketP,EventPacketT);
        
        
        printf("PN %d\t", packet_no);
        
        for(int i = 0; i < B_FEATURES; i++)
        {
            
            printf("%d", output_binary_literals[i]);
    
        }
        printf("\n");
            
    
        
        // homebrew feature extraction
        idfe_event_frame_count(f_packet_size, &packet_event_no,
                                          EventFrameCountALL, EventFrameCountPOS, EventFrameCountNEG,
                                          EventPacketX, EventPacketY, EventPacketP, EventPacketT);
        
        idfe_event_frame_density(f_packet_size, &packet_event_no,
                                     EventFrameDensityALL, EventFrameDensityPOS, EventFrameDensityNEG,
                                     EventPacketX, EventPacketY, EventPacketP, EventPacketT);
       
        idfe_eframe_continuous_bool(EventFrameCountALL, EventFrameCountPOS, EventFrameCountNEG,
                                        PrevEventFrameCountALL, PrevEventFrameCountPOS, PrevEventFrameCountNEG,
                                        OutputEventFrameBoolsALL, OutputEventFrameBoolsPOS, OutputEventFrameBoolsNEG);
        
        //idfe_print_event_frame_count(f_packet_size, &packet_event_no,
        //                                        EventFrameCountALL, EventFrameCountPOS, EventFrameCountNEG,
        //                                        EventPacketX, EventPacketY, EventPacketP, EventPacketT);
        
        //idfe_print_event_frame_density(EventFrameDensityALL, EventFrameDensityPOS, EventFrameDensityNEG);
        
        //idfe_print_eframe_continuous_bool(OutputEventFrameBoolsALL, OutputEventFrameBoolsPOS, OutputEventFrameBoolsNEG);
       
 

        // Other
//       // Print to terminal for checking output and debug
//       for(int a = 0; a < f_packet_size; a++)
//       {
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


 


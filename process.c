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


// can be 2, 4, 8, 16, 32  giving 4, 16, 64, 256, 1024 features respectively
#define S_FEATURES 2

int inter_frame_events[MAXFRAME_X][MAXFRAME_Y];
int seg_iframe_events[S_FEATURES][S_FEATURES];


void idfe_inter_frame_events_counter(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                                          int inter_frame_events[MAXFRAME_X][MAXFRAME_Y]);
void idfe_print_inter_frame_events_counter(int inter_frame_events[MAXFRAME_X][MAXFRAME_Y]);
void idfe_zero_inter_frame_events_counter(int inter_frame_events[MAXFRAME_X][MAXFRAME_Y]);


void idfe_inter_frame_events_segment_count(int inter_frame_events[MAXFRAME_X][MAXFRAME_Y],
                                           int seg_iframe_events[S_FEATURES][S_FEATURES])
{
    
    
    for(int i = 0; i < S_FEATURES; i++)
    {
        for(int j = 0; j < S_FEATURES; j++)
        {
            
            
            count_segment_events(i, j, inter_frame_events);
            
            
        }
        
    }
    
}


void count_segment_events(int seg_x, int seg_y, int inter_frame_events[][] )
{
    
    for(int i = seg_x; i < (seg_x * (MAXFRAME_X / S_FEATURES))
    
    
    
    
    
    
    
}





void process_event_data(int sample_events,int packet_size, int packet_overlap, int packets_req, int last_packet_size, int c,
                        long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[],
                        int fe_mode, int features_number)
{

    // process event data initial variables
    int byte_no = 0;
    int f_packet_size = 0;
    int event_no = 0;
    int packet_event_no = 0;
    
    // case 1 BPFE variables
    int packets_min0_count = 0;
    int pbfe_output_packet_literals[packets_req][B_FEATURES];
    
    switch(fe_mode) // Zeroing variables I
    {
            
            
            
            
            
        case 0: // RAW
            
            // Run for N number of packets to extract all data
            for(int packet_no = 0; packet_no < packets_req; packet_no++)
            {
               
                // Zero
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
                
                // Extract
                dataio_extract_event_packets(Sample_Input_File, byte_no, f_packet_size, &packet_event_no, EventPacketX,EventPacketY, EventPacketP,EventPacketT);
                
                // Process
                raw_literals_data(EventPacketX, EventPacketY, EventPacketP, EventPacketT,f_packet_size, c, literals_raw);
                
                // Print
                dataio_print_to_file_literals_raw(Processed_Data_Output_File, literals_raw, p_f_packet_size);

             
            }
            
            
            break;
        
            
        
            
            
        case 1: // PBFE
            
            // Zero
            pbfe_zero_patch_variables(patch_o_px,patch_o_py, patch_o_nx, patch_o_ny,
                                  patch_m_px,patch_m_py, patch_m_nx, patch_m_ny);

            pbfe_binary_patch_variables(patch_o_px,patch_o_py, patch_o_nx, patch_o_ny,
                                    patch_m_px,patch_m_py, patch_m_nx, patch_m_ny);
            
            
            // Run for N number of packets to extract all data
            for(int packet_no = 0; packet_no < packets_req; packet_no++)
            {
                 // Zero
                dataio_zero_event_packet_arrays(EventPacketX,EventPacketY, EventPacketP,EventPacketT);
                pbfe_zero_binary_variables(output_binary_literals, binary_features_count);
                        
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
                
                
                // Extract - retrieves the event data from the input sample file, separating it into separate arrays of ints
                dataio_extract_event_packets(Sample_Input_File, byte_no, f_packet_size, &packet_event_no, EventPacketX,EventPacketY, EventPacketP,EventPacketT);
                
                // Process - creates literals for each sample packet of events using binary patch feature extraction
                pbfe_binary_patches_output(output_binary_literals, binary_features_count, f_packet_size, EventPacketX, EventPacketY, EventPacketP,EventPacketT);
                
                // Print - for when printing the literals of every packet
                //pbfe_print_to_file_pbfe_literals(Processed_Data_Output_File, output_binary_literals);
                
                // Minimization 0 - rejects processed sample packets that produced zero literals,
                pbfe_output_packet_literals_min0(output_binary_literals, pbfe_output_packet_literals, &packets_min0_count);
                
                // For when going for a single set of output literals, comment out if printing the literals of every packet
                pbfe_correct_zero_packet_literals(output_binary_literals, pbfe_output_packet_literals,  &packets_min0_count);

            
                
                // Debug
                //pbfe_print_to_terminal(output_binary_literals, packet_no);
                
                
                
            } // packet loop ends
            
            // Minimization 1 - reduces to a single set of literals for the sample
            pbfe_output_packet_literals_min1(pbfe_final_output, pbfe_output_packet_literals, &packets_min0_count);
               

            // prints minimized literals
            pbfe_print_to_file_pbfe_min_literals(Processed_Data_Output_File, pbfe_final_output);
            
            
            
            break;
        
            
            
            
            
        case 2:  //IDFE
    
            // Zero
            idfe_zero_prev_event_frame(PrevEventFrameCountALL);
            idfe_zero_inter_frame_events_counter(inter_frame_events);
            //idfe_zero_inter_frame_events_count
            
            // Run for N number of packets to extract all data
            for(int packet_no = 0; packet_no < packets_req; packet_no++)
            {
                
                // Zero
                dataio_zero_event_packet_arrays(EventPacketX,EventPacketY, EventPacketP,EventPacketT);
                
                idfe_zero_event_frames(EventFrameCountALL);
                
                idfe_zero_inter_frame_events(OutputEventFrameBoolsALL);
                // idfe_zero_inter_frame_events
                
                
               
                        
  
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
                
                
                // Extract
                dataio_extract_event_packets(Sample_Input_File, byte_no, f_packet_size, &packet_event_no, EventPacketX,EventPacketY, EventPacketP,EventPacketT);
                
                // Process
                // Counts all the events in an event frame at each location
                idfe_event_frame_count(f_packet_size, &packet_event_no, EventFrameCountALL,
                                       EventPacketX, EventPacketY, EventPacketP, EventPacketT);
                
                //called every packet - changes every packet to packet
                idfe_create_inter_frame_events(EventFrameCountALL, PrevEventFrameCountALL,OutputEventFrameBoolsALL);
                
                idfe_inter_frame_events_counter(OutputEventFrameBoolsALL, inter_frame_events);

            
                
                // Debug
                //idfe_print_event_frame_count(f_packet_size, &packet_event_no, EventFrameCountALL,
                //                          EventPacketX, EventPacketY, EventPacketP, EventPacketT);

                //idfe_print_inter_frame_events(OutputEventFrameBoolsALL);

                
                
            } // end packet loop
            
            idfe_print_inter_frame_events_counter(inter_frame_events);
            
            
            
            
            
            
            
            
            
            // need a function to segment and count events in each segment
            
            // need a function to threshold the inter frame events counter to produce a 1 or 0
            
            
            
            // need print functions to verify
            
            
            // and a print to output file function
            
            
            
            
            
            
            
            
            
            
            
            break;
            
            
            
            
            
        default:
            
            puts("ERROR: NO FEATURE EXTRACTION MODE SELECTED!");
            exit(EXIT_FAILURE);
            
            break;
            
            
            
            
            
    }
    
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

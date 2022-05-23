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



void pbfe_output_packet_literals_min0(int output_binary_literals[], int pbfe_output_packet_literals[packets_req][B_FEATURES], int *packets_min0_count);

void pbfe_output_packet_literals_min0(int output_binary_literals[], int pbfe_output_packet_literals[packets_req][B_FEATURES], int *packets_min0_count)
{
    
    // Process - Check literals for zeros and ones
    int countzeros = 0;
    int countones = 0;
    
    for(int i = 0; i < B_FEATURES; i++)
    {
        if( output_binary_literals[i] == 0)
        {
            countzeros++;
        }
        
        if( output_binary_literals[i] == 1)
        {
            countones++;
        }
    }
    
   
    // packets with zero literals are rejected
    if( countzeros != B_FEATURES)
    {
        for(int i = 0; i < B_FEATURES; i++)
        {
            pbfe_output_packet_literals[*packets_min0_count][i] = output_binary_literals[i];
        }
        *packets_min0_count = *packets_min0_count + 1;
    }
    
    
}

int bpfe_final_output[B_FEATURES];
void pbfe_output_packet_literals_min1(int bpfe_final_output[], int pbfe_output_packet_literals[packets_req][B_FEATURES], int *packets_min0_count)
{
    
    
    
    
    
    
    
    
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
                
                // Minimization 0 - rejects processed sample packets that produced zero literals,
                pbfe_output_packet_literals_min0(output_binary_literals, pbfe_output_packet_literals, &packets_min0_count);
               
                
                // Debug
                //pbfe_print_to_terminal(output_binary_literals, packet_no);
                
                
                
            } // packet loop ends
            
            
            // Prints the processed packet samples with literals
            for(int i = 0; i < packets_min0_count; i++)
            {
                printf("Packet No %d\t", i);
                for(int j = 0; j < B_FEATURES; j++)
                {
                    
                    
                    printf("%d", pbfe_output_packet_literals[i][j]);
                    
                    
                }
                printf("\n");
            }
           
            
            // going to count the number of literals in each of the output sample packets,
            
//            //pbfe_packet_literals_nozeros[packets_with_literals_counter][i] contains the final array of packet literals
//            // from packet 0 to packet n-1, which is less than packets_req
//
//            int packet_literals_counters[packets_with_literals_counter];
//            for(int i = 0; i < packets_with_literals_counter; i ++)
//            {
//
//                packet_literals_counters[i] = 0;
//
//
//
//            }
//            // counts the number of literals in each packet
//            for(int i = 0; i < packets_with_literals_counter; i++)
//            {
//                for(int j = 0; j < B_FEATURES; j++)
//                {
//                    if( pbfe_packet_literals_nozeros[i][j] == 1)
//                    {
//                       packet_literals_counters[i]++;
//                    }
//                }
//            }
//
//            //check which packet literals counter is higher and print the packet with those literals
//
//            int check_counter = 0;
//            int hold_counter = 0;
//            for(int i = 0; i < packets_with_literals_counter; i++)
//            {
//                check_counter = packet_literals_counters[i];
//                if (check_counter > hold_counter)
//                {
//                    hold_counter = check_counter;
//                }
//            }
//
//
//            printf("Final Output Packet Number %d\t", pbfe_packet_literals_nozeros[hold_counter]);
//
//            // This is it, after this it's print to file, and some other dynamics for a log file,
//            // will implement the same for the other function, and then create data samples
//
//
//
//
//            // print statement for
//            for(int i = 0; i < B_FEATURES; i++)
//            {
//
//                for(int i = 0; i < B_FEATURES; i++)
//                {
//
//                    printf("%d",pbfe_packet_literals_nozeros[hold_counter][i]);
//
//                }
//                printf("\n");
//            }
//
//
//
            
            
            
            
            break;
        
            
            
            
            
        case 2:  //IDFE
    
            // Zero
            idfe_zero_PrevEventFrameCounts(PrevEventFrameCountALL, PrevEventFrameCountPOS, PrevEventFrameCountNEG);
            
            // Run for N number of packets to extract all data
            for(int packet_no = 0; packet_no < packets_req; packet_no++)
            {
                
                // Zero
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
                
                
                // Extract
                dataio_extract_event_packets(Sample_Input_File, byte_no, f_packet_size, &packet_event_no, EventPacketX,EventPacketY, EventPacketP,EventPacketT);
                
                // Process
                idfe_event_frame_count(f_packet_size, &packet_event_no,
                                                  EventFrameCountALL, EventFrameCountPOS, EventFrameCountNEG,
                                                  EventPacketX, EventPacketY, EventPacketP, EventPacketT);
                
                idfe_event_frame_density(f_packet_size, &packet_event_no,
                                             EventFrameDensityALL, EventFrameDensityPOS, EventFrameDensityNEG,
                                             EventPacketX, EventPacketY, EventPacketP, EventPacketT);
               
                idfe_eframe_continuous_bool(EventFrameCountALL, EventFrameCountPOS, EventFrameCountNEG,
                                                PrevEventFrameCountALL, PrevEventFrameCountPOS, PrevEventFrameCountNEG,
                                                OutputEventFrameBoolsALL, OutputEventFrameBoolsPOS, OutputEventFrameBoolsNEG);
                
                // Print
                idfe_print_event_frame_count(f_packet_size, &packet_event_no,
                                                        EventFrameCountALL, EventFrameCountPOS, EventFrameCountNEG,
                                                        EventPacketX, EventPacketY, EventPacketP, EventPacketT);
                
                idfe_print_event_frame_density(EventFrameDensityALL, EventFrameDensityPOS, EventFrameDensityNEG);
                
                idfe_print_eframe_continuous_bool(OutputEventFrameBoolsALL, OutputEventFrameBoolsPOS, OutputEventFrameBoolsNEG);
                        

            }
            
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


 


// process.c

// Standard Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//Posix Headers
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Program Specific Headers
#include "process.h"







void process_event_data(int sample_events,int packet_size, int packet_overlap, int packets_req, int last_packet_size, int c,
                        long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[],
                        int fe_mode, int type)
{
    
    //For timing the function
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    
    
    
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
            idfe_zero_seg_iframe_events(seg_iframe_events);
            
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
            
            //idfe_print_inter_frame_events_counter(inter_frame_events);
            
            idfe_inter_frame_events_segment_count(inter_frame_events, seg_iframe_events);
            
            
            //idfe_print_inter_frame_events_per_segment(seg_iframe_events);
            
            idfe_threshold_create_literals(seg_iframe_events, idfe_output_literals);
            
            idfe_print_to_file_idfe_literals(Processed_Data_Output_File, idfe_output_literals);
            
            
            
            break;
            
            
            
            
            
        default:
            
            puts("ERROR: NO FEATURE EXTRACTION MODE SELECTED!");
            exit(EXIT_FAILURE);
            
            break;
            
            
            
            
            
    }
    

    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    eidp_print_log_file2(EIDP_LOG_FILE_TEST, EIDP_LOG_FILE_TRAIN,
                         type, fe_mode, cpu_time_used);
    
}


 









// log file stuff

// Opens log file
FILE *eidp_open_log_file_test(FILE *EIDP_LOG_FILE_TEST, char *output_dir_label)
{
    char *s = "./";
    char *output_file = "_eidp_test_log.txt";
    char out_file_path[300] = "";
    
    // Creates the file path name using strcat
    strcat(out_file_path, s);
    strcat(out_file_path, output_dir_label);
    strcat(out_file_path, output_file);


    // Open file stream for the sample file, in read mode, binary
    EIDP_LOG_FILE_TEST= fopen(out_file_path,"w");

    
    if(EIDP_LOG_FILE_TEST == NULL)
    {
        puts("Unable to create the output file");
        exit(EXIT_FAILURE);
    }
    
    return EIDP_LOG_FILE_TEST;
}

// Opens log file
FILE *eidp_open_log_file_train(FILE *EIDP_LOG_FILE_TRAIN, char *output_dir_label)
{
    char *s = "./";
    char *output_file = "_eidp_train_log.txt";
    char out_file_path[300] = "";
    
    // Creates the file path name using strcat
    strcat(out_file_path, s);
    strcat(out_file_path, output_dir_label);
    strcat(out_file_path, output_file);


    // Open file stream for the sample file, in read mode, binary
    EIDP_LOG_FILE_TRAIN= fopen(out_file_path,"w");

    
    if(EIDP_LOG_FILE_TRAIN == NULL)
    {
        puts("Unable to create the output file");
        exit(EXIT_FAILURE);
    }
    
    return EIDP_LOG_FILE_TRAIN;
}



void eidp_print_log_file0_test(FILE *EIDP_LOG_FILE_TEST, char *output_dir_label, int fe_mode)
{
    fprintf(EIDP_LOG_FILE_TEST, "%s_eidp_test_log.txt\n\n", output_dir_label);
    fprintf(EIDP_LOG_FILE_TEST, "Method %d\n\n", fe_mode);
    fprintf(EIDP_LOG_FILE_TEST, "Class, Bytes, Events, PacketSize, PacketOverlap, PacketReq,");
    fprintf(EIDP_LOG_FILE_TEST, "LastZeros, LastSize, features, memsize, time s\n");
}

void eidp_print_log_file0_train(FILE *EIDP_LOG_FILE_TRAIN, char *output_dir_label, int fe_mode)
{
    fprintf(EIDP_LOG_FILE_TRAIN, "%s_eidp_train_log.txt\n\n", output_dir_label);
    fprintf(EIDP_LOG_FILE_TRAIN, "Method %d\n\n", fe_mode);
    fprintf(EIDP_LOG_FILE_TRAIN, "Class, Bytes, Events, PacketSize, PacketOverlap, PacketReq,");
    fprintf(EIDP_LOG_FILE_TRAIN, "LastZeros, LastSize, features, memsize, time s\n");
}



void eidp_print_log_file1_test(FILE *EIDP_LOG_FILE_TEST, int class,
                          long int sample_bytes, long int sample_events,
                          int packet_size, int packet_overlap, int packets_req,
                          int packet_events_overshoot, int last_packet_zeros, int last_packet_size)
{
    
    fprintf(EIDP_LOG_FILE_TEST, "%d,", class);
    fprintf(EIDP_LOG_FILE_TEST, "%ld,%ld,",sample_bytes, sample_events);
    fprintf(EIDP_LOG_FILE_TEST, "%d,%d,%d,", packet_size, packet_overlap, packets_req);
    fprintf(EIDP_LOG_FILE_TEST, "%d,%d,%d,",packet_events_overshoot, last_packet_zeros, last_packet_size);
    //fprintf(EIDP_LOG_FILE_TEST, "\n");
    
}

void eidp_print_log_file1_train(FILE *EIDP_LOG_FILE_TRAIN, int class,
                          long int sample_bytes, long int sample_events,
                          int packet_size, int packet_overlap, int packets_req,
                          int packet_events_overshoot, int last_packet_zeros, int last_packet_size)
{
    
    fprintf(EIDP_LOG_FILE_TRAIN, "%d,", class);
    fprintf(EIDP_LOG_FILE_TRAIN, "%ld,%ld,",sample_bytes, sample_events);
    fprintf(EIDP_LOG_FILE_TRAIN, "%d,%d,%d,", packet_size, packet_overlap, packets_req);
    fprintf(EIDP_LOG_FILE_TRAIN, "%d,%d,%d,",packet_events_overshoot, last_packet_zeros, last_packet_size);
    //fprintf(EIDP_LOG_FILE_TRAIN, "\n");
    
}





void eidp_print_log_file2(FILE *EIDP_LOG_FILE_TEST, FILE *EIDP_LOG_FILE_TRAIN,
                          int type, int fe_mode, double cpu_time_used)
{
  
            
            
        if(type == 0 && fe_mode == 1)
        {
            
            fprintf(EIDP_LOG_FILE_TEST, "%d,", B_FEATURES);
            fprintf(EIDP_LOG_FILE_TEST, "%d,", (B_FEATURES * 2) - 1);
            fprintf(EIDP_LOG_FILE_TEST, "%lf,", cpu_time_used);
            fprintf(EIDP_LOG_FILE_TEST, "\n");
        }
            
        if(type == 0 && fe_mode == 2)
        {
            
            fprintf(EIDP_LOG_FILE_TEST, "%d,", S_FEATURES);
            fprintf(EIDP_LOG_FILE_TEST, "%d,", (S_FEATURES * 2) - 1);
            fprintf(EIDP_LOG_FILE_TEST, "%lf,", cpu_time_used);
            fprintf(EIDP_LOG_FILE_TEST, "\n");
        }
         
            
        if(type == 1 && fe_mode == 1)
        {
            
            fprintf(EIDP_LOG_FILE_TRAIN, "%d,", B_FEATURES);
            fprintf(EIDP_LOG_FILE_TRAIN, "%d,", (B_FEATURES * 2) - 1);
            fprintf(EIDP_LOG_FILE_TRAIN, "%lf,", cpu_time_used);
            fprintf(EIDP_LOG_FILE_TRAIN, "\n");
            
            
        }
            
        if(type == 1 && fe_mode == 2)
        {
            
            fprintf(EIDP_LOG_FILE_TRAIN, "%d,", S_FEATURES);
            fprintf(EIDP_LOG_FILE_TRAIN, "%d,", (S_FEATURES * 2) - 1);
            fprintf(EIDP_LOG_FILE_TRAIN, "%lf,", cpu_time_used);
            fprintf(EIDP_LOG_FILE_TRAIN, "\n");
            
        }
       

    
}
    


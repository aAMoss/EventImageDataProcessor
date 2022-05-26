// eidp.c

// Standard Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

//Posix Headers
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Program Specific Headers
#include "eidp.h"




int main(void)
{
    
    // Sets the name for the output data
    dataio_get_out_dir_label(output_dir_label);
    
    // Creates the output data directories
    dataio_create_output_dir(output_dir_label, output_dir_name);
    
    // Sets the packet variables: size and overlap
    dataio_set_event_packet_vars(&packet_size, &packet_overlap);
    
    dataio_set_features_mode(&fe_mode);
    
    
    EIDP_LOG_FILE_TEST = eidp_open_log_file_test(EIDP_LOG_FILE_TEST, output_dir_label);
    
    
    eidp_print_log_file0_test(EIDP_LOG_FILE_TEST, output_dir_label, fe_mode);
 
    printf("\nPROCESS TEST DATA START\n\n");
    // Runs for everyone of the test data classes
    for(int c = 0; c < CLASSES; c++)
    {
        int type = 0;
        printf("Processing Test Class %d\n", c);
               
        // Opens the input directory of the N-MNIST Dataset
        Data_Input_Dir = dataio_open_data_input_dir_test(Data_Input_Dir, c);
        
        //Opens the output directory for the processed data
        Data_Output_Dir = dataio_open_data_output_dir_test(Data_Output_Dir, output_dir_name, c);
        
        while(  (Data_Input_Dir_Entry = readdir(Data_Input_Dir)) )
        {

            if(strcmp(Data_Input_Dir_Entry->d_name, ".") != 0 && strcmp(Data_Input_Dir_Entry->d_name, "..") != 0 &&
               strcmp(Data_Input_Dir_Entry->d_name, ".DS_Store"))
            {
        
               // printf("%s\n",Data_Input_Dir_Entry->d_name);
                
                
                Sample_Input_File = dataio_open_data_input_file_test(Data_Input_Dir, Sample_Input_File, c);
                Processed_Data_Output_File = dataio_open_data_output_file_test(Data_Output_Dir, output_dir_name, Processed_Data_Output_File, c);
                
               // puts("Input and output files opened!");
                
                dataio_get_input_sample_var(Sample_Input_File, &sample_bytes, &sample_events);
                
                datio_set_secondary_event_packet_vars(sample_events, packet_size, packet_overlap, &packets_req,
                                                      &packet_events_overshoot, &last_packet_zeros, &last_packet_size);

//                printf("Bytes\tEvents\tpacket_size\tpacket_overlap\tpackets_req\tOverShoot\tlast_packet_zeros\tlast_packet_size\n");
//                printf("%ld\t%ld\t%d\t\t%d\t\t%d\t\t",sample_bytes, sample_events, packet_size, packet_overlap, packets_req);
//                printf("%d\t\t%d\t\t\t%d\n",packet_events_overshoot, last_packet_zeros, last_packet_size);
                
                eidp_print_log_file1_test(EIDP_LOG_FILE_TEST, c,sample_bytes, sample_events,
                                          packet_size, packet_overlap, packets_req,
                                          packet_events_overshoot, last_packet_zeros, last_packet_size);
                
                
                process_event_data(sample_events, packet_size, packet_overlap, packets_req, last_packet_size, c,
                                   EventPacketX, EventPacketY, EventPacketP, EventPacketT, fe_mode, type);
                
                
                fclose(Processed_Data_Output_File);
                fclose(Sample_Input_File);
                
            } // close if
        
        } // close while
        
        closedir(Data_Output_Dir);
        closedir(Data_Input_Dir);
        
    } // End Classes For Loop
    printf("\nPROCESS TEST DATA COMPLETE\n\n");
    
    fclose(EIDP_LOG_FILE_TEST);
    
    
    
    
    
    EIDP_LOG_FILE_TRAIN = eidp_open_log_file_train(EIDP_LOG_FILE_TRAIN, output_dir_label);
    
    eidp_print_log_file0_train(EIDP_LOG_FILE_TRAIN, output_dir_label, fe_mode);

    
    printf("\nPROCESS TRAINING DATA START\n\n");
    // Runs for everyone of the training data classes
    for(int c = 0; c < CLASSES; c++)
    {
        int type = 1;
        printf("Processing Training Class %d\n", c);
        // Opens the input directory of the N-MNIST Dataset
        Data_Input_Dir = dataio_open_data_input_dir_train(Data_Input_Dir, c);
        
        //Opens the output directory for the processed data
        Data_Output_Dir = dataio_open_data_output_dir_train(Data_Output_Dir, output_dir_name, c);
        
        while(  (Data_Input_Dir_Entry = readdir(Data_Input_Dir)) )
        {

            if(strcmp(Data_Input_Dir_Entry->d_name, ".") != 0 && strcmp(Data_Input_Dir_Entry->d_name, "..") != 0 &&
               strcmp(Data_Input_Dir_Entry->d_name, ".DS_Store"))
            {
        
                //printf("%s\n",Data_Input_Dir_Entry->d_name);
                
                
                Sample_Input_File = dataio_open_data_input_file_train(Data_Input_Dir, Sample_Input_File, c);
                Processed_Data_Output_File = dataio_open_data_output_file_train(Data_Output_Dir, output_dir_name, Processed_Data_Output_File, c);
                
               // puts("Input and output files opened!");
                
                dataio_get_input_sample_var(Sample_Input_File, &sample_bytes, &sample_events);
                
                datio_set_secondary_event_packet_vars(sample_events, packet_size, packet_overlap, &packets_req,
                                                      &packet_events_overshoot, &last_packet_zeros, &last_packet_size);

//                printf("Bytes\tEvents\tpacket_size\tpacket_overlap\tpackets_req\tOverShoot\tlast_packet_zeros\tlast_packet_size\n");
//                printf("%ld\t%ld\t%d\t\t%d\t\t%d\t\t",sample_bytes, sample_events, packet_size, packet_overlap, packets_req);
//                printf("%d\t\t%d\t\t\t%d\n",packet_events_overshoot, last_packet_zeros, last_packet_size);
//
                
                eidp_print_log_file1_train(EIDP_LOG_FILE_TRAIN, c,sample_bytes, sample_events,
                                          packet_size, packet_overlap, packets_req,
                                          packet_events_overshoot, last_packet_zeros, last_packet_size);
                
                
                process_event_data(sample_events, packet_size, packet_overlap, packets_req, last_packet_size, c,
                                   EventPacketX, EventPacketY, EventPacketP, EventPacketT, fe_mode, type);
                
                
                fclose(Processed_Data_Output_File);
                fclose(Sample_Input_File);
                
            } // close if
        
        } // close while
        
        closedir(Data_Output_Dir);
        closedir(Data_Input_Dir);
        
    } // End Classes For Loop
    printf("\nPROCESS TRAINING DATA COMPLETE\n\n");
    
    fclose(EIDP_LOG_FILE_TRAIN);
    
    
    return 0;
}











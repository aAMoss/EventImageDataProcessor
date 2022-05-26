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




long int total_req_packets_test;
long int count_test_samples;
long int total_bytes_test;
long int total_events_test;


long int total_req_packets_train;
long int count_train_samples;
long int total_bytes_train;
long int total_events_train;



// log file stuff
FILE *eidp_open_log_file_test(FILE *EIDP_LOG_FILE_TEST, char *output_dir_label);
FILE *eidp_open_log_file_train(FILE *EIDP_LOG_FILE_TRAIN, char *output_dir_label);

void eidp_print_log_file0_test(FILE *EIDP_LOG_FILE_TEST, char *output_dir_label, int fe_mode);
void eidp_print_log_file1_test(FILE *EIDP_LOG_FILE_TEST, int class,
                               int packet_size, int packet_overlap,
                               long int total_req_packets_test,
                               long int count_test_samples,
                               long int total_bytes_test,
                               long int total_events_test,
                               double cpu_time_used);

void eidp_print_log_file0_train(FILE *EIDP_LOG_FILE_TRAIN, char *output_dir_label, int fe_mode);
void eidp_print_log_file1_train(FILE *EIDP_LOG_FILE_TRAIN, int class,
                               int packet_size, int packet_overlap,
                               long int total_req_packets_train,
                               long int count_train_samples,
                               long int total_bytes_train,
                               long int total_events_train,
                                double cpu_time_used);


int main(void)
{

    clock_t start, end;
    double cpu_time_used;
    
    
    
    
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
        
        total_req_packets_test = 0;
        count_test_samples = 0;
        total_bytes_test = 0;
        total_events_test = 0;
        
        
        start = clock();
        
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

                
                total_req_packets_test += packets_req;
                count_test_samples++;
                total_bytes_test += sample_bytes;
                total_events_test += sample_events;
          
                
                
//                printf("Bytes\tEvents\tpacket_size\tpacket_overlap\tpackets_req\tOverShoot\tlast_packet_zeros\tlast_packet_size\n");
//                printf("%ld\t%ld\t%d\t\t%d\t\t%d\t\t",sample_bytes, sample_events, packet_size, packet_overlap, packets_req);
//                printf("%d\t\t%d\t\t\t%d\n",packet_events_overshoot, last_packet_zeros, last_packet_size);
                
               
                
                process_event_data(sample_events, packet_size, packet_overlap, packets_req, last_packet_size, c,
                                   EventPacketX, EventPacketY, EventPacketP, EventPacketT, fe_mode, type);
                
                
                fclose(Processed_Data_Output_File);
                fclose(Sample_Input_File);
                
            } // close if
        
        } // close while
        
        closedir(Data_Output_Dir);
        closedir(Data_Input_Dir);
        
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        
        
        eidp_print_log_file1_test(EIDP_LOG_FILE_TEST, c,
                                       packet_size, packet_overlap,
                                       total_req_packets_test,
                                       count_test_samples,
                                       total_bytes_test,
                                       total_events_test,
                                       cpu_time_used);
        
                
    } // End Classes For Loop
    printf("\nPROCESS TEST DATA COMPLETE\n\n");
    
    fclose(EIDP_LOG_FILE_TEST);
    
    
    
    
    
    EIDP_LOG_FILE_TRAIN = eidp_open_log_file_train(EIDP_LOG_FILE_TRAIN, output_dir_label);
    
    eidp_print_log_file0_train(EIDP_LOG_FILE_TRAIN, output_dir_label, fe_mode);

    
    printf("\nPROCESS TRAINING DATA START\n\n");
    // Runs for everyone of the training data classes
    for(int c = 0; c < CLASSES; c++)
    {
        
        total_req_packets_train = 0;
        count_train_samples = 0;
        total_bytes_train = 0;
        total_events_train = 0;
        
        
        start = clock();
        
        
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
                // Stats
              
                
                total_req_packets_train += packets_req;
                count_train_samples++;
                total_bytes_train += sample_bytes;
                total_events_train += sample_events;
          
                
                
                
                
                process_event_data(sample_events, packet_size, packet_overlap, packets_req, last_packet_size, c,
                                   EventPacketX, EventPacketY, EventPacketP, EventPacketT, fe_mode, type);
                
                
                fclose(Processed_Data_Output_File);
                fclose(Sample_Input_File);
                
            } // close if
        
        } // close while
        
        closedir(Data_Output_Dir);
        closedir(Data_Input_Dir);
        
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        
        eidp_print_log_file1_train(EIDP_LOG_FILE_TRAIN, c,
                                       packet_size, packet_overlap,
                                       total_req_packets_train,
                                       count_train_samples,
                                       total_bytes_train,
                                        total_events_train,
                                       cpu_time_used);
        
        
        
        
        
        
    } // End Classes For Loop
    printf("\nPROCESS TRAINING DATA COMPLETE\n\n");
    
    fclose(EIDP_LOG_FILE_TRAIN);
    
    
    return 0;
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
    fprintf(EIDP_LOG_FILE_TEST, "Class, PacketSize, PacketOverlap, Class Req Packets, Class Samples, Class Bytes, Class Events,");
    fprintf(EIDP_LOG_FILE_TEST, "Class Time\n");
}

void eidp_print_log_file1_test(FILE *EIDP_LOG_FILE_TEST, int class,
                               int packet_size, int packet_overlap,
                               long int total_req_packets_test,
                               long int count_test_samples,
                               long int total_bytes_test,
                               long int total_events_test,
                               double cpu_time_used)
{
    
    fprintf(EIDP_LOG_FILE_TEST, "%d,", class);
    fprintf(EIDP_LOG_FILE_TEST, "%d,%d,", packet_size, packet_overlap);
    fprintf(EIDP_LOG_FILE_TEST, "%ld,", total_req_packets_test);
    fprintf(EIDP_LOG_FILE_TEST, "%ld,", count_test_samples);
    fprintf(EIDP_LOG_FILE_TEST, "%ld,", total_bytes_test);
    fprintf(EIDP_LOG_FILE_TEST, "%ld,", total_events_test);
    fprintf(EIDP_LOG_FILE_TEST, "%lf,", cpu_time_used);
    fprintf(EIDP_LOG_FILE_TEST, "\n");
    
}


    
    
void eidp_print_log_file0_train(FILE *EIDP_LOG_FILE_TRAIN, char *output_dir_label, int fe_mode)
{
    fprintf(EIDP_LOG_FILE_TRAIN, "%s_eidp_train_log.txt\n\n", output_dir_label);
    fprintf(EIDP_LOG_FILE_TRAIN, "Method %d\n\n", fe_mode);
    fprintf(EIDP_LOG_FILE_TRAIN, "Class, PacketSize, PacketOverlap, Class Req Packets, Class Samples, Class Bytes, Class Events,");
    fprintf(EIDP_LOG_FILE_TRAIN, "Class Time\n");
}

void eidp_print_log_file1_train(FILE *EIDP_LOG_FILE_TRAIN, int class,
                               int packet_size, int packet_overlap,
                               long int total_req_packets_train,
                               long int count_train_samples,
                               long int total_bytes_train,
                               long int total_events_train,
                               double cpu_time_used)
{
    
    fprintf(EIDP_LOG_FILE_TRAIN, "%d,", class);
    fprintf(EIDP_LOG_FILE_TRAIN, "%d,%d,", packet_size, packet_overlap);
    fprintf(EIDP_LOG_FILE_TRAIN, "%ld,", total_req_packets_train);
    fprintf(EIDP_LOG_FILE_TRAIN, "%ld,", count_train_samples);
    fprintf(EIDP_LOG_FILE_TRAIN, "%ld,", total_bytes_train);
    fprintf(EIDP_LOG_FILE_TRAIN, "%ld,", total_events_train);
    fprintf(EIDP_LOG_FILE_TRAIN, "%lf,", cpu_time_used);
    fprintf(EIDP_LOG_FILE_TRAIN, "\n");
    
}


                

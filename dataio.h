// dataio.h

#ifndef DATAIO_H
#define DATAIO_H


// Program Specific Headers
#include "eidp.h"
#include "raw.h"




// Function Prototypes
void dataio_get_out_dir_label(char *output_dir_label);
void dataio_create_output_dir(char *output_dir_label, char *output_dir_name);
void dataio_set_event_packet_vars(int *packet_size, int *packet_overlap);
void dataio_set_features_mode(int *fe_mode);
void dataio_set_features_number(int *features_number);

DIR *dataio_open_data_input_dir_test(DIR *Data_Input_Dir, int c);
DIR *dataio_open_data_input_dir_train(DIR *Data_Input_Dir, int c);

DIR *dataio_open_data_output_dir_test(DIR *Data_Output_Dir, char* output_dir_name, int c);
DIR *dataio_open_data_output_dir_train(DIR *Data_Output_Dir, char* output_dir_name, int c);

FILE *dataio_open_data_input_file_test(DIR *Data_Input_Dir, FILE *Sample_Input_File, int c );
FILE *dataio_open_data_input_file_train(DIR *Data_Input_Dir, FILE *Sample_Input_File, int c );

FILE *dataio_open_data_output_file_test(DIR *Data_Output_Dir, char* output_dir_name, FILE *Processed_Data_Output_File, int c);
FILE *dataio_open_data_output_file_train(DIR *Data_Output_Dir, char* output_dir_name, FILE *Processed_Data_Output_File, int c);



void dataio_get_input_sample_var(FILE *Sample_Input_File, long int *sample_bytes, long int *sample_events);
void datio_set_secondary_event_packet_vars(long int sample_events, int packet_size, int packet_overlap, int *packets_req,
                                           int *packet_events_overshoot, int *last_packet_zeros, int *last_packet_size);



void dataio_zero_event_packet_arrays(long int EventPacketX[],long int EventPacketY[],long int EventPacketP[],long int EventPacketT[]);
void dataio_extract_event_packets(FILE *Sample_Input_File, int byte_no, int f_packet_size, int *packet_event_no,long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[]);
void dataio_print_to_file_literals_raw(FILE *Processed_Data_Output_File, int literals_raw[RAW_BOOL_MAX][*p_f_packet_size], int *p_f_packet_size);

#endif //DATAIO_H

// eidp.h

#ifndef EIDP_H
#define EIDP_H


// DEFINITIONS EIDP

#include "hyper.h"



// EXTERN VARIABLES EIDP
extern long int total_req_packets_test;
extern long int count_test_samples;
extern long int total_bytes_test;
extern long int total_events_test;


extern long int total_req_packets_train;
extern long int count_train_samples;
extern long int total_bytes_train;
extern long int total_events_train;



// EXTERN VARIABLES DATAIO

// Directory Objects and Structures
extern DIR *Data_Input_Dir;
extern struct dirent *Data_Input_Dir_Entry;
extern DIR *Data_Output_Dir;
extern struct dirent *Data_Output_Dir_Entry;

// File Objects
extern FILE *Sample_Input_File;
extern FILE *Processed_Data_Output_File;
extern FILE *EIDP_LOG_FILE_TEST;
extern FILE *EIDP_LOG_FILE_TRAIN;

// Packet Variables - User specified
extern int packet_size;
extern int packet_overlap;

// Feature Extraction Mode
extern int fe_mode;
extern int features_number;

// Number of Features

// Packet Variables II - Determined by input sample file
extern long int sample_bytes;
extern long int sample_events;

// Packet Variables III - Calculated using I and II above
extern int packets_req;
extern int packet_events_overshoot;
extern int last_packet_zeros;
extern int last_packet_size;

// Event Packet Varaibles - 1 array each for the co-ordinates, polarity,
//and timestamp (in us) of each event
extern long int EventPacketX[EVENTS_PER_SAMPLE_MAX];
extern long int EventPacketY[EVENTS_PER_SAMPLE_MAX];
extern long int EventPacketP[EVENTS_PER_SAMPLE_MAX];
extern long int EventPacketT[EVENTS_PER_SAMPLE_MAX];

// Directory label names - User specified, names the output directory
extern char output_dir_label[(DATA_OUT_NAME_MAX /2)];
extern char output_dir_name[DATA_OUT_NAME_MAX];

// Pointer for dataio_print_to_file_literals_raw
extern int *p_f_packet_size;



// EXTERN VARIABLES PROCESS - NONE



// EXTERN VARIABLES RAW


// EXTERN VARIABLES PBFE
extern int output_binary_literals[B_FEATURES];
extern int binary_features_count[B_FEATURES];
extern int patch_o_px[B_FEATURES];
extern int patch_o_py[B_FEATURES];
extern int patch_o_nx[B_FEATURES];
extern int patch_o_ny[B_FEATURES];
extern int patch_m_px[B_FEATURES];
extern int patch_m_py[B_FEATURES];
extern int patch_m_nx[B_FEATURES];
extern int patch_m_ny[B_FEATURES];
extern int pbfe_final_output[B_FEATURES];


// EXTERN VARIABLES IDFE

extern int inter_frame_events[MAXFRAME_X][MAXFRAME_Y];
extern int seg_iframe_events[S_FEATURES][S_FEATURES];
extern int idfe_output_literals[S_FEATURES][S_FEATURES];

extern int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y];
extern int PrevEventFrameCountALL[MAXFRAME_X][MAXFRAME_Y];
extern int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y];
extern int MiniEventFrameBoolsALL[MIN_FRAME_X][MIN_FRAME_Y];


#endif //EIDP_H

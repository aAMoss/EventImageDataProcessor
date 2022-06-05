// eidp.h

#ifndef EIDP_H
#define EIDP_H


// DEFINITIONS EIDP



// DEFINITIONS DATAIO

// Definitions - Input directory paths for the N-MNIST data set (choose between the full set or a smaller test set)
#define TEST_IN_DIR "./N-MNIST_test/Test/"
#define TRAIN_IN_DIR "./N-MNIST_test/Train/"
//#define TEST_IN_DIR "./N-MNIST/Test/"
//#define TRAIN_IN_DIR "./N-MNIST/Train/"

#define EVENTS_PER_SAMPLE_MAX 10000
#define DATA_IN_NAME_MAX 200
#define FEATURES_MAX 1024
#define FEATURES_MIN 4

#define MAXFRAME_X 32
#define MAXFRAME_Y 32
#define F_DIV 2
#define REG_X 8
#define REG_Y 8
#define MIN_FRAME_X (MAXFRAME_X / F_DIV)
#define MIN_FRAME_Y (MAXFRAME_Y / F_DIV)

#define PACKET_MAX 1500
#define PACKET_MIN 100
#define EVENT_BUFF_SIZE 5
#define DATA_OUT_NAME_MAX 200
#define CLASSES 10


// DEFINITIONS PROCESS - NONE



// DEFINITIONS RAW
#define RAW_XY_BOOL 6
#define RAW_P_BOOL 1
#define RAW_T_BOOL 24
#define RAW_C_BOOL 4
#define RAW_BOOL_MAX ((2*RAW_XY_BOOL) + RAW_P_BOOL + RAW_T_BOOL + RAW_C_BOOL) //41


// DEFINITIONS PBFE

// patch D x D
#define PATCH_D 7

// max patch D origin 0,0 postion
#define PATCH_X_MAX (MAXFRAME_X - PATCH_D)
#define PATCH_Y_MAX (MAXFRAME_Y - PATCH_D)
#define PATCH_X_MIN 0
#define PATCH_Y_MIN 0

// must be between 4 and 1024, a multiple of 4, and a perfect square root: 4, 16, 64, 256, 1024
#define B_FEATURES 64
#define B_FEATURES_STRING (B_FEATURES + 1)
#define B_FEATURES_CLASS (B_FEATURES + 4)

// DEFINITIONS IDFE
#define S_FEATURES 64	// 4, 16, 64, 256, 1024 features respectively
#define THRESHOLD_DIV 3
#define SEG_X (sqrt(S_FEATURES))
#define SEG_Y (sqrt(S_FEATURES))
#define SEG_A_X (MAXFRAME_X / SEG_X)
#define SEG_A_Y (MAXFRAME_Y / SEG_Y)




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

// Event Packet Varaibles - 1 array each for the co-ordinates, polarity, and timestamp (in us) of each event
extern long int EventPacketX[EVENTS_PER_SAMPLE_MAX]; // will store the event packet x values
extern long int EventPacketY[EVENTS_PER_SAMPLE_MAX]; // will store the event packet y values
extern long int EventPacketP[EVENTS_PER_SAMPLE_MAX]; // will store the event packet p values
extern long int EventPacketT[EVENTS_PER_SAMPLE_MAX]; // will store the event packet t values

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

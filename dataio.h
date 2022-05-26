// dataio.h

// Program Specific Headers
#include "raw.h"



// Definitions - Input directory paths for the N-MNIST data set (choose between the full set or a smaller test set)
#define TEST_IN_DIR "./N-MNIST_test/Test/"
#define TRAIN_IN_DIR "./N-MNIST_test/Train/"
//#define TEST_IN_DIR "./N-MNIST/Test/"
//#define TRAIN_IN_DIR "./N-MNIST/Train/"

// Definitions - Variables
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

// Directory Objects and Structures
DIR *Data_Input_Dir;
struct dirent *Data_Input_Dir_Entry;
DIR *Data_Output_Dir;
struct dirent *Data_Output_Dir_Entry;

// File Objects
FILE *Sample_Input_File;
FILE *Processed_Data_Output_File;

// Packet Variables - User specified
int packet_size;
int packet_overlap;

// Feature Extraction Mode
int fe_mode;
int features_number;

// Number of Features

// Packet Variables II - Determined by input sample file
long int sample_bytes;
long int sample_events;

// Packet Variables III - Calculated using I and II above
int packets_req;
int packet_events_overshoot;
int last_packet_zeros;
int last_packet_size;

// Event Packet Varaibles - 1 array each for the co-ordinates, polarity, and timestamp (in us) of each event
long int EventPacketX[EVENTS_PER_SAMPLE_MAX]; // will store the event packet x values
long int EventPacketY[EVENTS_PER_SAMPLE_MAX]; // will store the event packet y values
long int EventPacketP[EVENTS_PER_SAMPLE_MAX]; // will store the event packet p values
long int EventPacketT[EVENTS_PER_SAMPLE_MAX]; // will store the event packet t values

// Directory label names - User specified, names the output directory
char output_dir_label[(DATA_OUT_NAME_MAX /2)];
char output_dir_name[DATA_OUT_NAME_MAX];

// Pointer for dataio_print_to_file_literals_raw
int *p_f_packet_size;

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


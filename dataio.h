// dataio.h

// Directory paths for the input data
#define TEST_IN_DIR "./N-MNIST_test/Test/"
#define TRAIN_IN_DIR "./N-MNIST_test/Train/"

#define EVENTS_PER_SAMPLE_MAX 10000
#define DATA_IN_NAME_MAX 200
#define EVENT_BUFF_SIZE 5
#define DATA_OUT_NAME_MAX 200
#define CLASSES 10

// Directory Objects and Structures
DIR *Data_Input_Dir;
struct dirent *Data_Input_Dir_Entry;



// File Objects
FILE *Sample_Input_File;


// Variables
int packet_size;
int packet_overlap;

long int sample_bytes;
long int sample_events;
int packets_req;
int packet_events_overshoot;
int last_packet_zeros;
int last_packet_size;

long int EventPacketX[EVENTS_PER_SAMPLE_MAX]; // will store the event packet x values
long int EventPacketY[EVENTS_PER_SAMPLE_MAX]; // will store the event packet y values
long int EventPacketP[EVENTS_PER_SAMPLE_MAX]; // will store the event packet p values
long int EventPacketT[EVENTS_PER_SAMPLE_MAX]; // will store the event packet t values

char output_dir_label[(DATA_OUT_NAME_MAX /2)];
char output_dir_name[DATA_OUT_NAME_MAX];



// Function Prototypes
void config_get_out_dir_label(char *output_dir_label);
void config_create_output_dir(char *output_dir_label, char *output_dir_name);
void config_set_event_packet_vars(int *packet_size, int *packet_overlap);

DIR *dataio_open_data_input_dir(DIR *Data_Input_Dir, int c);
FILE *dataio_open_data_input_file(DIR *Data_Input_Dir, FILE *Sample_Input_File, int c );
void dataio_get_input_sample_var(FILE *Sample_Input_File, long int *sample_bytes, long int *sample_events);
void datio_set_secondary_event_packet_vars(long int sample_events, int packet_size, int packet_overlap, int *packets_req,
                                           int *packet_events_overshoot, int *last_packet_zeros, int *last_packet_size);
void dataio_zero_event_packet_arrays(long int EventPacketX[],long int EventPacketY[],long int EventPacketP[],long int EventPacketT[]);
void dataio_extract_event_packets(FILE *Sample_Input_File, int byte_no, int f_packet_size, int *packet_event_no,long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[]);






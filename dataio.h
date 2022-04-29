// dataio.h

// Directory paths for the input data
#define TEST_IN_DIR "./N-MNIST_test/Test/"
#define TRAIN_IN_DIR "./N-MNIST_test/Train/"


#define EVENT_BUFF_SIZE 5

// Directory Objects and Structures
DIR *Data_Input_Dir;
struct dirent *Data_Input_Dir_Entry;



// File Objects
FILE *Sample_Input_File;


// Function Prototypes
DIR *dataio_open_data_input_dir(DIR *Data_Input_Dir, int c);
FILE *dataio_open_data_input_file(DIR *Data_Input_Dir, FILE *Sample_Input_File, int c );
void dataio_get_input_sample_var(FILE *Sample_Input_File, long int *sample_bytes, long int *sample_events);
void datio_set_secondary_event_packet_vars(long int sample_events, int packet_size, int packet_overlap, int *packets_req,
                                           int *packet_events_overshoot, int *last_packet_zeros, int *last_packet_size);


long int sample_bytes;
long int sample_events;
int packets_req;
int packet_events_overshoot;
int last_packet_zeros;
int last_packet_size;

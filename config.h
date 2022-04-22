// config.h



// Defines
#define DATA_OUT_NAME_MAX 200

// Variables
char output_dir_label[DATA_OUT_NAME_MAX];
int packet_size = 0;
int packet_overlap = 0;

// Function Prototypes
void config_get_out_dir_label(char *output_dir_label);
void config_set_event_packet_vars(int *packet_size, int *packet_overlap);





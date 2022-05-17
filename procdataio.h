// procdataio.h

// Standard Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Posix Headers
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


// Definitions
#define TEST_DATA_NAME_MAX 200
#define NMNIST_TEST_SAMPLES 10000
#define NMNIST_TRAIN_SAMPLES 60000
#define CLASSES 10

#define MAX_TEST_SAMPLES 10000
#define MAX_TRAIN_SAMPLES 60000
#define MAX_SAMPLES_STATUS 10000 // needs to be larger than the maximum number of samples in a class
#define TOTAL_SAMPLES (MAX_TEST_SAMPLES + MAX_TRAIN_SAMPLES)


// Variables
int d_flag;
int l_flag;
long int test_samples;
long int train_samples;
long int class_test_samples;
long int class_train_samples;
long int total_test_samples;
long int total_train_samples;
long int total_nmnist_samples;

char dataset_dir_label[(TEST_DATA_NAME_MAX /2)];


// Directory Objects and Structures
DIR *DATASET_INPUT_DIR;
struct dirent *Dataset_Input_Dir_Entry;

// File Objects
FILE *NMNIST_DATA_SAMPLE;
FILE *TEST_DATA_OUTPUT;
FILE *TRAIN_DATA_OUTPUT;
FILE *TMDA_LOG_FILE;



// Function Prototypes
void tmda_get_dataset_dir_label(char *dataset_dir_label);
void tmda_set_data_samples(int *d_flag, long int *test_samples, long int *train_samples);

void tmda_get_data_sample_per_class(long int test_samples, long int train_samples,
                                    long int *class_test_samples, long int *class_train_samples,
                                    long int *total_test_samples, long int *total_train_samples, long int *total_nmnist_samples);

DIR *tmda_open_dataset_input_dir_test(DIR *DATASET_INPUT_DIR, char *dataset_dir_label, int c);
DIR *tmda_open_dataset_input_dir_train(DIR *DATASET_INPUT_DIR, char *dataset_dir_label, int c);

FILE *tmda_open_data_output_file_testdata(FILE *TEST_DATA_OUTPUT, char *dataset_dir_label);
FILE *tmda_open_data_output_file_traindata(FILE *TRAIN_DATA_OUTPUT, char *dataset_dir_label);

FILE *tmda_open_data_input_file_test(DIR *DATASET_INPUT_DIR, FILE *NMNIST_DATA_SAMPLE,char *dataset_dir_label, int c );
FILE *tmda_open_data_input_file_train(DIR *DATASET_INPUT_DIR, FILE *NMNIST_DATA_SAMPLE,char *dataset_dir_label, int c );

FILE *tmda_open_log_file(FILE *TMDA_LOG_FILE, char *dataset_dir_label);

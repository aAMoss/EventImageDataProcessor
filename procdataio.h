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
#define CLASSES 10
#define MAX_TEST_SAMPLES 10000
#define MAX_TRAIN_SAMPLES 60000
#define TOTAL_SAMPLES 70000

// Variables
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



// Function Prototypes
void tmda_get_dataset_dir_label(char *dataset_dir_label);
void tmda_set_data_samples(long int *test_samples, long int *train_samples);

void tmda_get_data_sample_per_class(long int test_samples, long int train_samples,
                                    long int *class_test_samples, long int *class_train_samples,
                                    long int *total_test_samples, long int *total_train_samples, long int *total_nmnist_samples);

DIR *tmda_open_dataset_input_dir_test(DIR *DATASET_INPUT_DIR, char *dataset_dir_label, int c);
DIR *tmda_open_dataset_input_dir_train(DIR *DATASET_INPUT_DIR, char *dataset_dir_label, int c);

// tmda.h

#ifndef TMDA_H
#define TMDA_H

// Program Specific Headers



// DEFINITIONS TMDA

// DEFINITIONS PROCDATAIO
#define TEST_DATA_NAME_MAX 200
#define NMNIST_TEST_SAMPLES 10000
#define NMNIST_TRAIN_SAMPLES 60000
#define CLASSES 10

#define MAX_TEST_SAMPLES 10000
#define MAX_TRAIN_SAMPLES 60000
#define MAX_SAMPLES_STATUS 10000 // needs to be larger than the maximum number of samples in a class
#define TOTAL_SAMPLES (MAX_TEST_SAMPLES + MAX_TRAIN_SAMPLES)

#define MIN_CLASS 0
#define MAX_CLASS 9
#define FEATURES 64
#define MIN_POS 0
#define SAMPLE_STAT 1
#define MAX_LINE (FEATURES * 2)


//EXTERN VARIABLES TMDA


// EXTERN VARIABLES PROCDATIO

// Variables
extern int d_flag;
extern int l_flag;
extern long int test_samples;
extern long int train_samples;
extern long int class_test_samples;
extern long int class_train_samples;
extern long int total_test_samples;
extern long int total_train_samples;
extern long int total_nmnist_samples;

extern char dataset_dir_label[(TEST_DATA_NAME_MAX /2)];

extern int test_class_sample_count[CLASSES];
extern int train_class_sample_count[CLASSES];

extern int random_class;
extern long int random_class_sample_count;
extern long int random_dir_pos;
extern long int tell_random_dir;
extern long int seek_random_dir;
extern int rflag;
extern int pos_count;

extern int copied_test_samples;
extern int count_test_class_samples[CLASSES];
extern int copied_train_samples;
extern int count_train_class_samples[CLASSES];


// Directory Objects and Structures
extern DIR *DATASET_INPUT_DIR;
extern struct dirent *Dataset_Input_Dir_Entry;
extern struct stat Dir_Entry_Statbuf;

// File Objects
extern FILE *NMNIST_DATA_SAMPLE;
extern FILE *TEST_DATA_OUTPUT;
extern FILE *TRAIN_DATA_OUTPUT;
extern FILE *TMDA_LOG_FILE;







#endif //TMDA_H

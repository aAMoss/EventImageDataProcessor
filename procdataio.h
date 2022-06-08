// procdataio.h

#ifndef PROCDATAIO_H
#define PROCDATAIO_H

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

// Program Specific Headers
#include "tmda.h"


// Function Prototypes
void tmda_get_dataset_dir_label(char *dataset_dir_label);
void tmda_set_data_samples(long int *test_samples, long int *train_samples);

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

void tmda_print_log_file_1(FILE *TMDA_LOG_FILE, char *dataset_dir_label,
                           long int test_samples, long int train_samples,
                           long int class_test_samples, long int class_train_samples,
                           long int total_test_samples, long int total_train_samples,
                           long int total_nmnist_samples );
void tmda_print_log_file_2(FILE *TMDA_LOG_FILE, int test_class_sample_count[CLASSES], int train_class_sample_count[CLASSES]);

void tmda_print_log_file_x(FILE *TMDA_LOG_FILE, int count_test_class_samples[CLASSES], int count_train_class_samples[CLASSES]);


#endif //PROCDATAIO_H

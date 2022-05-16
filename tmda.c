// tmda.c


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


// Going to need some counters???
// Will certainly need to calculate the total number of lines of booleans/literals for the raw bool data.
// This is because the TM program treats each line of booleans as an individual data sample, my initial hypothesis requires the event data
// to be input unprocessed as bools. Each sample of N-MNIST is several thousand lines of bools. SO will need to calculate the total lines (from the selected data samples)
// to ensure I ahve a value that can be entered into the TM

// to avoid over-training will have it so that equal numbers of each class are selected

// all samples have an individual number unique for the training and test sets, maybe use some kind of string comparison to avoid picking the same samples

// going to need a function to read the appropriate directory
// goind to need a function to open a file from the dataset (in said directory)
// going to need a function to create the output test and train files for the TM
// going to need a function to copy the contents of the dataset file to the appropriate test and train files... basically concatenating them together.


// will first count the number of files in the directory and record the entries
// will then rewind to the directory start
//  will randomly step through the directory selecting samples, will record the name of selected samples
// willuse the recorded name to ensure duplicates of samples aren't selected

#define MIN_CLASS 0
#define MAX_CLASS 9
#define MIN_POS 0
#define SAMPLE_STAT 1
#define MAX_LINE 82




int copied_test_samples;
int count_test_class_samples[CLASSES] = {0};
int copied_train_samples;
int count_train_class_samples[CLASSES] = {0};

int test_class_sample_count[CLASSES] = {0};
int train_class_sample_count[CLASSES] = {0};

int test_class_status[CLASSES];
int train_class_status[CLASSES];

int random_class;
long int random_class_sample_count;
long int random_dir_pos;
long int tell_random_dir;
long int seek_random_dir;

void tmda_print_log_file_1(FILE *TMDA_LOG_FILE, char *dataset_dir_label, int d_flag,
                           long int test_samples, long int train_samples,
                           long int class_test_samples, long int class_train_samples,
                           long int total_test_samples, long int total_train_samples,
                           long int total_nmnist_samples );
void tmda_print_log_file_2(FILE *TMDA_LOG_FILE, int test_class_sample_count[CLASSES], int train_class_sample_count[CLASSES]);






int main(void)
{
    
    srand(time(NULL));
    
    
    
    tmda_get_dataset_dir_label(dataset_dir_label);
    
    tmda_set_data_samples(&d_flag,&test_samples, &train_samples);
    
    tmda_get_data_sample_per_class(test_samples, train_samples, &class_test_samples, &class_train_samples,
                                   &total_test_samples, &total_train_samples, &total_nmnist_samples);
    
    
    TMDA_LOG_FILE = tmda_open_log_file(TMDA_LOG_FILE,  dataset_dir_label);
    
    
    tmda_print_log_file_1(TMDA_LOG_FILE, dataset_dir_label, d_flag, test_samples,  train_samples,
                          class_test_samples, class_train_samples, total_test_samples, total_train_samples,total_nmnist_samples );
    

    
    // Gets the number of samples of test data and training data in each class from the dataset
    for(int c = 0; c < CLASSES; c++)
    {
        DATASET_INPUT_DIR = tmda_open_dataset_input_dir_test(DATASET_INPUT_DIR, dataset_dir_label, c);
        rewinddir(DATASET_INPUT_DIR);
        
        while(  (Dataset_Input_Dir_Entry = readdir(DATASET_INPUT_DIR)) )
        {
            if(strcmp(Dataset_Input_Dir_Entry->d_name, ".") != 0 && strcmp(Dataset_Input_Dir_Entry->d_name, "..") != 0 &&
               strcmp(Dataset_Input_Dir_Entry->d_name, ".DS_Store"))
            {
                test_class_sample_count[c]++;
            }
        }
        closedir(DATASET_INPUT_DIR);
        
        
        DATASET_INPUT_DIR = tmda_open_dataset_input_dir_train(DATASET_INPUT_DIR, dataset_dir_label, c);
        rewinddir(DATASET_INPUT_DIR);
        
        while(  (Dataset_Input_Dir_Entry = readdir(DATASET_INPUT_DIR)) )
        {
            if(strcmp(Dataset_Input_Dir_Entry->d_name, ".") != 0 && strcmp(Dataset_Input_Dir_Entry->d_name, "..") != 0 &&
               strcmp(Dataset_Input_Dir_Entry->d_name, ".DS_Store"))
            {
                train_class_sample_count[c]++;
            }
        }
        closedir(DATASET_INPUT_DIR);
    }
    
    tmda_print_log_file_2(TMDA_LOG_FILE, test_class_sample_count, train_class_sample_count);
    
    
    
    // FUCK FUCK FUCK need to figure out how to do this!!!
    
    
    TEST_DATA_OUTPUT = tmda_open_data_output_file_testdata(TEST_DATA_OUTPUT, dataset_dir_label);
    puts("\nOpened Data Output File!\n");
    
    
    while(copied_test_samples < total_test_samples)
    {
        
        // Selects a random class, 0 to 9
        random_class = ( rand() % (MAX_CLASS - MIN_CLASS + 1) ) + MIN_CLASS;
        
        // Gets the number of data samples available of the random class
        random_class_sample_count = test_class_sample_count[random_class];
        
        //  Selects a random directory position (as a long int) from 0 to random_class_sample_count
        random_dir_pos = ( rand() % (random_class_sample_count - MIN_POS + 1) ) + MIN_POS;
        tell_random_dir = 0;
        
   
        int test_sample_status[CLASSES][random_class_sample_count];
        
        printf("random_class %d\tlocal_class_sample_count %ld\trandom_dir_pos %ld\n\n", random_class, random_class_sample_count, random_dir_pos );
        
        // Opens the input directory of the randomly chosen class
        DATASET_INPUT_DIR = tmda_open_dataset_input_dir_test(DATASET_INPUT_DIR, dataset_dir_label, random_class);
        
        puts("Opened Data Input Directory!\n");
        
        while(  (Dataset_Input_Dir_Entry = readdir(DATASET_INPUT_DIR)) )
        {
            
            
            if(strcmp(Dataset_Input_Dir_Entry->d_name, ".") != 0 && strcmp(Dataset_Input_Dir_Entry->d_name, "..") != 0 &&
               strcmp(Dataset_Input_Dir_Entry->d_name, ".DS_Store"))
            {
                
                // gets the current directory position (as a long int) from 0 to random_class_sample_count
                tell_random_dir = telldir(DATASET_INPUT_DIR);
                
                // executes if the directory position matches that of the chosen sample, and it that sample hasn't been selected before (status = 0)
                if( (tell_random_dir == random_dir_pos) && (d_flag == 1) ) // || (tell_random_dir == random_dir_pos) && (d_flag == 0) && )
                {
                    printf("seekdir position %ld\n", random_dir_pos);
                    puts("Sample found!");
                    NMNIST_DATA_SAMPLE = tmda_open_data_input_file_test(DATASET_INPUT_DIR, NMNIST_DATA_SAMPLE, dataset_dir_label, random_class);
                    puts("Sample File Opened!");
                    
                    char ch_buf[MAX_LINE];
                    while (feof(NMNIST_DATA_SAMPLE) != 1)
                    {
                        fgets(ch_buf, sizeof(ch_buf),NMNIST_DATA_SAMPLE);
                        fputs(ch_buf, TEST_DATA_OUTPUT);
                    }
                    
                    fclose(NMNIST_DATA_SAMPLE);
                    puts("Sample File Closed!");
                    
                    
                    count_test_class_samples[random_class]++;
                    copied_test_samples++;
                    
                    printf("Test Samples Copied: %d\n", copied_test_samples);
                    
                }
                
               
            }
            
        }
        
        
        
        closedir(DATASET_INPUT_DIR);
        puts("Input Directory Closed!");
    }
    
    fclose(TMDA_LOG_FILE);

    return 0;
}










void tmda_print_log_file_1(FILE *TMDA_LOG_FILE, char *dataset_dir_label, int d_flag,
                           long int test_samples, long int train_samples,
                           long int class_test_samples, long int class_train_samples,
                           long int total_test_samples, long int total_train_samples,
                           long int total_nmnist_samples )
{
 
    fprintf(TMDA_LOG_FILE, "%s_tmda_logfile.txt\n\n", dataset_dir_label);
    fprintf(TMDA_LOG_FILE, "Duplicates, Set Test Samples, Set Train Samples,");
    fprintf(TMDA_LOG_FILE, "Samples per Test Class, Samples per Train Class, Total Test Samples, Total Train Samples, Total NMNIST Samples\n");
    fprintf(TMDA_LOG_FILE, "%d,%ld,%ld,%ld,%ld,%ld,%ld,%ld\n\n", d_flag, test_samples, train_samples, class_test_samples, class_train_samples,
            total_test_samples, total_train_samples, total_nmnist_samples);
    
}



void tmda_print_log_file_2(FILE *TMDA_LOG_FILE, int test_class_sample_count[CLASSES], int train_class_sample_count[CLASSES])
{
    
    fprintf(TMDA_LOG_FILE, "Class No, Dataset Test Samples, Dataset Training Samples\n");
    for(int i = 0; i < CLASSES; i++)
    {
        fprintf(TMDA_LOG_FILE, "%d,%d,%d\n", i, test_class_sample_count[i], train_class_sample_count[i]);
        
    }
    
    
}



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


#define MIN_CLASS 0
#define MAX_CLASS 9
#define MIN_POS 0
#define SAMPLE_STAT 1
#define MAX_LINE 82


int test_class_sample_count[CLASSES] = {0};
int train_class_sample_count[CLASSES] = {0};

int random_class;
long int random_class_sample_count;
long int random_dir_pos;
long int tell_random_dir;
long int seek_random_dir;


int copied_test_samples;
int count_test_class_samples[CLASSES] = {0};
int copied_train_samples;
int count_train_class_samples[CLASSES] = {0};

void tmda_print_log_file_1(FILE *TMDA_LOG_FILE, char *dataset_dir_label,
                           long int test_samples, long int train_samples,
                           long int class_test_samples, long int class_train_samples,
                           long int total_test_samples, long int total_train_samples,
                           long int total_nmnist_samples );
void tmda_print_log_file_2(FILE *TMDA_LOG_FILE, int test_class_sample_count[CLASSES], int train_class_sample_count[CLASSES]);






int main(void)
{
    
    srand(time(NULL));
    
    
    
    tmda_get_dataset_dir_label(dataset_dir_label);
    
    tmda_set_data_samples(&test_samples, &train_samples);
    
    tmda_get_data_sample_per_class(test_samples, train_samples, &class_test_samples, &class_train_samples,
                                   &total_test_samples, &total_train_samples, &total_nmnist_samples);
    
    
    TMDA_LOG_FILE = tmda_open_log_file(TMDA_LOG_FILE,  dataset_dir_label);
    
    
    tmda_print_log_file_1(TMDA_LOG_FILE, dataset_dir_label, test_samples,  train_samples,
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
    
    
    
    
    
    


    
    TEST_DATA_OUTPUT = tmda_open_data_output_file_testdata(TEST_DATA_OUTPUT, dataset_dir_label);
    puts("\nOpened TestData Output File!\n");
    
    
    while(copied_test_samples < test_samples)
    {
        
        // Selects a random class, 0 to 9
        random_class = ( rand() % (MAX_CLASS - MIN_CLASS + 1) ) + MIN_CLASS;
        
        // Gets the number of data samples available of the random class
        random_class_sample_count = test_class_sample_count[random_class];
        
        //  Selects a random directory position (as a long int) from 0 to random_class_sample_count
        random_dir_pos = ( rand() % (random_class_sample_count - MIN_POS + 1) ) + MIN_POS;
        tell_random_dir = 0;
        
   
       
        printf("random_class %d\tlocal_test_class_sample_count %ld\trandom_dir_pos %ld\n", random_class, random_class_sample_count, random_dir_pos);
        
        // Opens the input directory of the randomly chosen test class
        DATASET_INPUT_DIR = tmda_open_dataset_input_dir_test(DATASET_INPUT_DIR, dataset_dir_label, random_class);
        
        while(  (Dataset_Input_Dir_Entry = readdir(DATASET_INPUT_DIR)) )
        {
            
            
            if(strcmp(Dataset_Input_Dir_Entry->d_name, ".") != 0 && strcmp(Dataset_Input_Dir_Entry->d_name, "..") != 0 &&
               strcmp(Dataset_Input_Dir_Entry->d_name, ".DS_Store"))
            {
                
                // gets the current directory position (as a long int) from 0 to random_class_sample_count
                tell_random_dir = telldir(DATASET_INPUT_DIR);
                
                // executes if the directory position matches that of the chosen sample, and it that sample hasn't been selected before (status = 0)
                if(  tell_random_dir == random_dir_pos )
                {
                    
                    
                    NMNIST_DATA_SAMPLE = tmda_open_data_input_file_test(DATASET_INPUT_DIR, NMNIST_DATA_SAMPLE, dataset_dir_label, random_class);
                  
                    
                    char ch_buf[MAX_LINE];
                    while (feof(NMNIST_DATA_SAMPLE) != 1)
                    {
                        fgets(ch_buf, sizeof(ch_buf),NMNIST_DATA_SAMPLE);
                        fputs(ch_buf, TEST_DATA_OUTPUT);
                    }
                    
                    fclose(NMNIST_DATA_SAMPLE);
                    
                    
                    count_test_class_samples[random_class]++;
                    copied_test_samples++;
                    
                    printf("Test Samples Copied: %d\n", copied_test_samples);
                    
                }
                
               
            }
            
        }
        
        
        
        closedir(DATASET_INPUT_DIR);

    }
    
    fclose(TEST_DATA_OUTPUT);
    
    
    TEST_DATA_OUTPUT = tmda_open_data_output_file_traindata(TEST_DATA_OUTPUT, dataset_dir_label);
    puts("\nOpened Train Data Output File!\n");
    
    while(copied_train_samples < train_samples)
    {
        
        // Selects a random class, 0 to 9
        random_class = ( rand() % (MAX_CLASS - MIN_CLASS + 1) ) + MIN_CLASS;
        
        // Gets the number of data samples available of the random class
        random_class_sample_count = train_class_sample_count[random_class];
        
        //  Selects a random directory position (as a long int) from 0 to random_class_sample_count
        random_dir_pos = ( rand() % (random_class_sample_count - MIN_POS + 1) ) + MIN_POS;
        tell_random_dir = 0;
        
   
       
        printf("random_class %d\tlocal_train_class_sample_count %ld\trandom_dir_pos %ld\n", random_class, random_class_sample_count, random_dir_pos);
        
        // Opens the input directory of the randomly chosen train class
        DATASET_INPUT_DIR = tmda_open_dataset_input_dir_train(DATASET_INPUT_DIR, dataset_dir_label, random_class);
        
        while(  (Dataset_Input_Dir_Entry = readdir(DATASET_INPUT_DIR)) )
        {
            
            
            if(strcmp(Dataset_Input_Dir_Entry->d_name, ".") != 0 && strcmp(Dataset_Input_Dir_Entry->d_name, "..") != 0 &&
               strcmp(Dataset_Input_Dir_Entry->d_name, ".DS_Store"))
            {
                
                // gets the current directory position (as a long int) from 0 to random_class_sample_count
                tell_random_dir = telldir(DATASET_INPUT_DIR);
                
                // executes if the directory position matches that of the chosen sample, and it that sample hasn't been selected before (status = 0)
                if(  tell_random_dir == random_dir_pos )
                {
                    
                    
                    NMNIST_DATA_SAMPLE = tmda_open_data_input_file_train(DATASET_INPUT_DIR, NMNIST_DATA_SAMPLE, dataset_dir_label, random_class);
                  
                    
                    char ch_buf[MAX_LINE];
                    while (feof(NMNIST_DATA_SAMPLE) != 1)
                    {
                        fgets(ch_buf, sizeof(ch_buf),NMNIST_DATA_SAMPLE);
                        fputs(ch_buf, TEST_DATA_OUTPUT);
                    }
                    
                    fclose(NMNIST_DATA_SAMPLE);
                    
                    
                    count_train_class_samples[random_class]++;
                    copied_train_samples++;
                    
                    printf("Train Samples Copied: %d\n", copied_test_samples);
                    
                }
                
               
            }
            
        }
        
        
        
        closedir(DATASET_INPUT_DIR);

    }
    
    fclose(TEST_DATA_OUTPUT);
    
    fclose(TMDA_LOG_FILE);
    
    printf("Test Samples Copied: %d\n", copied_test_samples);
    printf("Train Samples Copied: %d\n", copied_test_samples);
    
    return 0;
}










void tmda_print_log_file_1(FILE *TMDA_LOG_FILE, char *dataset_dir_label,
                           long int test_samples, long int train_samples,
                           long int class_test_samples, long int class_train_samples,
                           long int total_test_samples, long int total_train_samples,
                           long int total_nmnist_samples )
{
 
    fprintf(TMDA_LOG_FILE, "%s_tmda_logfile.txt\n\n", dataset_dir_label);
    fprintf(TMDA_LOG_FILE, "Set Test Samples, Set Train Samples,");
    fprintf(TMDA_LOG_FILE, "Samples per Test Class, Samples per Train Class, Total Test Samples, Total Train Samples, Total NMNIST Samples\n");
    fprintf(TMDA_LOG_FILE, "%ld,%ld,%ld,%ld,%ld,%ld,%ld\n\n", test_samples, train_samples, class_test_samples, class_train_samples,
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



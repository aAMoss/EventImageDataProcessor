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




int copied_test_samples;
int copied_train_samples;

int test_class_sample_count[CLASSES] = {0};
int train_class_sample_count[CLASSES] = {0};

int test_class_status[CLASSES];
int train_class_status[CLASSES];





int main(void)
{
    
    srand(time(NULL));
    
    tmda_get_dataset_dir_label(dataset_dir_label);
    
    tmda_set_data_samples(&test_samples, &train_samples);
    
    tmda_get_data_sample_per_class(test_samples, train_samples, &class_test_samples, &class_train_samples,
                                   &total_test_samples, &total_train_samples, &total_nmnist_samples);
    
    
    // Counts the number of samples in each class for the test and train data
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
    
    printf("Class\tTest\tTrain\n");
    printf("No\tSamples\tSamples\n");
    for(int i = 0; i < CLASSES; i++)
    {
        printf("%d\t%d\t%d\n", i, test_class_sample_count[i], train_class_sample_count[i]);
        
    }
    
    printf("Data Directory Name:\t%s\n", dataset_dir_label);
    printf("Test Samples: %ld\nTraining Samples: %ld\n", test_samples, train_samples);
    printf("Samples per test class: %ld\nSamples per train class: %ld\n", class_test_samples, class_train_samples);
    printf("Total test samples: %ld\nTotal train samples: %ld\n", total_test_samples, total_train_samples);
    printf("Total nmnist samples: %ld\n", total_nmnist_samples);
  
    
    
    printf("random_class\ttest_pos\ttrain_pos\n");
    
    
    
    
    for(int i = 0; i < CLASSES; i++)
    {
        
        
    }
    
    
    copied_test_samples = 0;
    
    
    
    
    
    while(copied_test_samples < class_test_samples)
    {
        
        int random_class = ( rand() % (MAX_CLASS - MIN_CLASS + 1) ) + MIN_CLASS;
        
        int local_class_sample_count = test_class_sample_count[random_class];
        
        long int dir_pos = ( rand() % (test_class_sample_count[random_class] - MIN_POS + 1) ) + MIN_POS;
        
        int class_status[ (test_class_sample_count[random_class]) ];

        
        DATASET_INPUT_DIR = tmda_open_dataset_input_dir_test(DATASET_INPUT_DIR, dataset_dir_label, random_class);

        seekdir(DATASET_INPUT_DIR, dir_pos);
        
        while(  (Dataset_Input_Dir_Entry = readdir(DATASET_INPUT_DIR)) )
        {
           if(strcmp(Dataset_Input_Dir_Entry->d_name, ".") != 0 && strcmp(Dataset_Input_Dir_Entry->d_name, "..") != 0 &&
              strcmp(Dataset_Input_Dir_Entry->d_name, ".DS_Store"))
           {
               
               for(int i = 0; i < test_class_sample_count[random_class]; i ++)
               {
                   
                   if( class_status[i] == 0 )
                   {
                       
                       //open input sample file
                       //copy input sample contents to the output file
                       
                       class_status[i]++;
                       copied_test_samples++;
                       break;
                   }
                   
                   break;
                   
               }

           }
            
        }
        
  
        
      

    }
    
    

    return 0;
}



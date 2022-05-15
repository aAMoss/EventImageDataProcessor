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

// Definitions
#define TEST_DATA_NAME_MAX 200
#define CLASSES 10
#define MAX_TEST_SAMPLES 10000
#define MAX_TRAIN_SAMPLES 60000
#define TOTAL_SAMPLES 70000

// Variables
long int test_samples;
long int train_samples;
char test_dir_label[(TEST_DATA_NAME_MAX /2)];

long int class_test_samples;
long int class_train_samples;

long int total_test_samples;
long int total_train_samples;
long int total_nmnist_samples;

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



// Function Prototypes
void tmda_get_test_dir_label(char *test_dir_label);
void tmda_set_data_samples(long int *test_samples, long int *train_samples);

void tmda_get_data_sample_per_class(long int test_samples, long int train_samples,
                                    long int *class_test_samples, long int *class_train_samples,
                                    long int *total_test_samples, long int *total_train_samples, long int *total_nmnist_samples)
                                    
{
    
    // Calculates the number of samples that will be taken from each class
    *class_test_samples = test_samples / CLASSES;
    *class_train_samples = train_samples / CLASSES;
    
    // Calculates the total number of samples selected
    // Accounts for descrepencies when choosing numbers of samples that aren't multiples of 10
    *total_test_samples = *class_test_samples * CLASSES;
    *total_train_samples = *class_train_samples * CLASSES;
    *total_nmnist_samples = (*total_test_samples) + (*total_train_samples);
    
    
}




int main(void)
{
    
    tmda_get_test_dir_label(test_dir_label);
    
    tmda_set_data_samples(&test_samples, &train_samples);
    
    tmda_get_data_sample_per_class(test_samples, train_samples, &class_test_samples, &class_train_samples, &total_test_samples, &total_train_samples, &total_nmnist_samples);
   
    
    printf("Data Directory Name:\t%s\n", test_dir_label);
    printf("Test Samples: %ld\nTraining Samples: %ld\n", test_samples, train_samples);
    printf("Samples per test class: %ld\nSamples per train class: %ld\n", class_test_samples, class_train_samples);
    printf("Total test samples: %ld\nTotal train samples: %ld\n", total_test_samples, total_train_samples);
    printf("Total nmnist samples: %ld\n", total_nmnist_samples);
    
    
    //function to open the directory... recursively maybe a loop similar to the main program
    
    // function to open the sample file
    
    // function to copy/append the sample file to the output file
    
    // rinse and repeat for the number of samples required
    
    
    return 0;
}

void tmda_get_test_dir_label(char *test_dir_label)
{
    char user_input[TEST_DATA_NAME_MAX];

    
    puts("Please enter the name of the data test data directory.");

    fgets(user_input, (TEST_DATA_NAME_MAX), stdin);
    user_input[strcspn(user_input, "\n")] = '\0'; // removes the return key
    strcat(test_dir_label, user_input);
}



void tmda_set_data_samples(long int *test_samples, long int *train_samples)
{
    long int test = 0;
    long int train = 0;
    int test_flag = 0;
    int train_flag = 0;
    
    while(test_flag < 1)
    {
        printf("Please enter the required number of test samples.\nValue must be at least 1.\n");
       
        scanf("%ld", &test);
        
        if(test < 1 || test > MAX_TEST_SAMPLES)
        {
            printf("ERROR: Must select between 1 and %d samples!\n", MAX_TEST_SAMPLES);
        }
        else
        if (test >= 1)
        {
            *test_samples = test;
            test_flag++;
        }
    }
    
    while(train_flag < 1)
    {
        printf("Please enter the required number of training samples.\nValue must be at least 1.\n");
       
        scanf("%ld", &train);
        
        if(train < 1 || train > MAX_TRAIN_SAMPLES)
        {
            printf("ERROR: Must select between 1 and %d samples!\n", MAX_TRAIN_SAMPLES);
        }
        else
        if (train >= 1)
        {
            *train_samples = train;
            train_flag++;
        }
    }
}


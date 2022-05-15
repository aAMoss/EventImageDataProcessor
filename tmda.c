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









int main(void)
{
    
    tmda_get_dataset_dir_label(dataset_dir_label);
    
    tmda_set_data_samples(&test_samples, &train_samples);
    
    tmda_get_data_sample_per_class(test_samples, train_samples, &class_test_samples, &class_train_samples,
                                   &total_test_samples, &total_train_samples, &total_nmnist_samples);
    
    // Going to create / open the output files here
    
    // Selecting Test Data
    for(int c = 0; c < CLASSES; c++)
    {
        
        DATASET_INPUT_DIR = tmda_open_dataset_input_dir_test(DATASET_INPUT_DIR, dataset_dir_label, c);
        
        
        // will first count the number of files in the directory and record the entries
        // will then rewind to the directory start
        //  will randomly step through the directory selecting samples, will record the name of selected samples
        // willuse the recorded name to ensure duplicates of samples aren't selected
        
        
        
        
        // going to open  the input files here
        
        //
        
        //close file here
        closedir(DATASET_INPUT_DIR);
        
        
    }
    
    // Selecting Training Data
    for(int c = 0; c < CLASSES; c++)
    {
        
        DATASET_INPUT_DIR = tmda_open_dataset_input_dir_train(DATASET_INPUT_DIR, dataset_dir_label, c);
        
        
        closedir(DATASET_INPUT_DIR);
        
        
    }
    
    
    
    
    printf("Data Directory Name:\t%s\n", dataset_dir_label);
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



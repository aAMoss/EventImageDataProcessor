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


// Variables

long int test_samples;
long int train_samples;
char test_dir_label[(TEST_DATA_NAME_MAX /2)];



// Function Prototypes
void tmda_get_test_dir_label(char *test_dir_label);
void tmda_set_data_samples(long int *test_samples, long int *train_samples);


int main(void)
{
    
    tmda_get_test_dir_label(test_dir_label);
    
    tmda_set_data_samples(&test_samples, &train_samples);
    
    printf("Data Directory Name:\t%s\n", test_dir_label);
    printf("Selected:\t%ld Test Samples\t%ld Training Samples\n", test_samples, train_samples);
    
    
    
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
        
        if(test < 1)
        {
            printf("ERROR: Must have at least 1 sample!\n");
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
        
        if(train < 1)
        {
            printf("ERROR: Must have at least 1 sample!\n");
        }
        else
        if (train >= 1)
        {
            *train_samples = train;
            train_flag++;
        }
    }
}



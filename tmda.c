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



int test_samples;
int train_samples;

void tmda_set_data_samples(int *test_samples, int *train_samples);

int main(void)
{
    
    
    tmda_set_data_samples(&test_samples, &train_samples);
    
    printf("Selected:\t%d Test Samples\t%d Training Samples\n", test_samples, train_samples);
    
    
    return 0;
}




void tmda_set_data_samples(int *test_samples, int *train_samples)
{
    int test = 0;
    int train = 0;
    int test_flag = 0;
    int train_flag = 0;
    
    while(test_flag < 1)
    {
        printf("Please enter the required number of test samples.\nValue must be at least 1.\n");
       
        scanf("%d", &test);
        
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
       
        scanf("%d", &train);
        
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

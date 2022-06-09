// procdataio.c

// Program Specific Headers
#include "procdataio.h"


// Variables
int d_flag;
int l_flag;
long int test_samples;
long int train_samples;
long int class_test_samples;
long int class_train_samples;
long int total_test_samples;
long int total_train_samples;
long int total_nmnist_samples;

char dataset_dir_label[(TEST_DATA_NAME_MAX /2)];

int test_class_sample_count[CLASSES];
int train_class_sample_count[CLASSES];

int random_class;
long int random_class_sample_count;
long int random_dir_pos;
long int tell_random_dir;
long int seek_random_dir;
int rflag;
int pos_count;

int copied_test_samples;
int count_test_class_samples[CLASSES];
int copied_train_samples;
int count_train_class_samples[CLASSES];




// Directory Objects and Structures
DIR *DATASET_INPUT_DIR;
struct dirent *Dataset_Input_Dir_Entry;
struct stat Dir_Entry_Statbuf;

// File Objects
FILE *NMNIST_DATA_SAMPLE;
FILE *TEST_DATA_OUTPUT;
FILE *TRAIN_DATA_OUTPUT;
FILE *TMDA_LOG_FILE;



void tmda_get_dataset_dir_label(char *dataset_dir_label)
{
    char user_input[TEST_DATA_NAME_MAX] ="";
    puts("Please enter the name of the data test data directory.");
    fgets(user_input, (TEST_DATA_NAME_MAX), stdin);
    user_input[strcspn(user_input, "\n")] = '\0'; // removes the return key
    strcat(dataset_dir_label, user_input);
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
        
        if(train < 1 || train > MAX_TRAIN_SAMPLES )
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


DIR *tmda_open_dataset_input_dir_test(DIR *DATASET_INPUT_DIR, char *dataset_dir_label, int c)
{
    char *s0 = "./";
    char *s1 = "/Test/";
    char *s2 = "/";
    char class_num[2] = "";
    char input_dir_name[200] = "";
    
    sprintf(class_num, "%d", c);
    strcat(input_dir_name, s0);
    strcat(input_dir_name, dataset_dir_label);
    strcat(input_dir_name, s1);
    strcat(input_dir_name, class_num);
    strcat(input_dir_name, s2);

    DATASET_INPUT_DIR = opendir(input_dir_name);
    
    if(DATASET_INPUT_DIR == NULL)
    {
        puts("ERROR: Unable to read directory!");
        exit(EXIT_FAILURE);
    }
    
    
    return DATASET_INPUT_DIR;
    
}

DIR *tmda_open_dataset_input_dir_train(DIR *DATASET_INPUT_DIR, char *dataset_dir_label, int c)
{
    char *s0 = "./";
    char *s1 = "/Train/";
    char *s2 = "/";
    char class_num[2] = "";
    char input_dir_name[200] = "";
    
    sprintf(class_num, "%d", c);
    strcat(input_dir_name, s0);
    strcat(input_dir_name, dataset_dir_label);
    strcat(input_dir_name, s1);
    
    strcat(input_dir_name, class_num);
    strcat(input_dir_name, s2);
    
    DATASET_INPUT_DIR = opendir(input_dir_name);
    
    if(DATASET_INPUT_DIR == NULL)
    {
        puts("ERROR: Unable to read directory!");
        exit(EXIT_FAILURE);
    }
    
    return DATASET_INPUT_DIR;
    
}



// Opens processed train data output file
FILE *tmda_open_data_output_file_testdata(FILE *TEST_DATA_OUTPUT, char *dataset_dir_label)
{
    char *s = "./";
    char *output_file = "_EIDPTestData.txt";
    char out_file_path[300] = "";
    
    // Creates the file path name using strcat
    strcat(out_file_path, s);
    strcat(out_file_path, dataset_dir_label);
    strcat(out_file_path, output_file);


    // Open file stream for the sample file, in read mode, binary
    TEST_DATA_OUTPUT = fopen(out_file_path,"w");

    
    if(TEST_DATA_OUTPUT == NULL)
    {
        puts("Unable to create the output file");
        exit(EXIT_FAILURE);
    }
    
    return TEST_DATA_OUTPUT;
}





// Opens processed train data output file
FILE *tmda_open_data_output_file_traindata(FILE *TRAIN_DATA_OUTPUT, char *dataset_dir_label)
{
    char *s = "./";
    char *output_file = "_EIDPTrainData.txt";
    char out_file_path[300] = "";
    
    // Creates the file path name using strcat
    strcat(out_file_path, s);
    strcat(out_file_path, dataset_dir_label);
    strcat(out_file_path, output_file);


    // Open file stream for the sample file, in read mode, binary
    TRAIN_DATA_OUTPUT = fopen(out_file_path,"w");

    
    if(TRAIN_DATA_OUTPUT == NULL)
    {
        puts("Unable to create the output file");
        exit(EXIT_FAILURE);
    }
    
    return TRAIN_DATA_OUTPUT;
}








// Opens test data input file,
FILE *tmda_open_data_input_file_test(DIR *DATASET_INPUT_DIR, FILE *NMNIST_DATA_SAMPLE,char *dataset_dir_label, int c )
{
    char *s0 = "./";
    char *s1 = "/Test/";
    char *s2 = "/";
    char class_num[2] = "";
    char input_file_path[300] = "";
    
    sprintf(class_num, "%d", c);
    strcat(input_file_path, s0);
    strcat(input_file_path, dataset_dir_label);
    strcat(input_file_path, s1);
    strcat(input_file_path, class_num);
    strcat(input_file_path, s2);
    strcat(input_file_path, Dataset_Input_Dir_Entry->d_name);
    
    
    // Open file stream for the sample file, in read mode, binary
    NMNIST_DATA_SAMPLE = fopen(input_file_path,"rb");

    if(NMNIST_DATA_SAMPLE == NULL)
    {
        puts("Unable to open the file");
        exit(EXIT_FAILURE);
    }
    
    
    printf("%s\n", input_file_path);
    
    return NMNIST_DATA_SAMPLE;
}

// Opens test data input file,
FILE *tmda_open_data_input_file_train(DIR *DATASET_INPUT_DIR, FILE *NMNIST_DATA_SAMPLE, char *dataset_dir_label, int c )
{
    char *s0 = "./";
    char *s1 = "/Train/";
    char *s2 = "/";
    char class_num[2] = "";
    char input_file_path[300] = "";
    
    sprintf(class_num, "%d", c);
    strcat(input_file_path, s0);
    strcat(input_file_path, dataset_dir_label);
    strcat(input_file_path, s1);
    strcat(input_file_path, class_num);
    strcat(input_file_path, s2);
    strcat(input_file_path, Dataset_Input_Dir_Entry->d_name);
    
    
    // Open file stream for the sample file, in read mode, binary
    NMNIST_DATA_SAMPLE = fopen(input_file_path,"rb");

    if(NMNIST_DATA_SAMPLE == NULL)
    {
        puts("Unable to open the file");
        exit(EXIT_FAILURE);
    }
    
    
    printf("%s\n", input_file_path);
    
    return NMNIST_DATA_SAMPLE;
}



// Opens log file
FILE *tmda_open_log_file(FILE *TMDA_LOG_FILE, char *dataset_dir_label)
{
    char *s = "./";
    char *output_file = "_tmda_logfile.txt";
    char out_file_path[300] = "";
    
    // Creates the file path name using strcat
    strcat(out_file_path, s);
    strcat(out_file_path, dataset_dir_label);
    strcat(out_file_path, output_file);


    // Open file stream for the sample file, in read mode, binary
    TMDA_LOG_FILE = fopen(out_file_path,"w");

    
    if(TMDA_LOG_FILE == NULL)
    {
        puts("Unable to create the output file");
        exit(EXIT_FAILURE);
    }
    
    return TMDA_LOG_FILE;
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
    
    fprintf(TMDA_LOG_FILE, "\n");
    
}


void tmda_print_log_file_x(FILE *TMDA_LOG_FILE, int count_test_class_samples[CLASSES], int count_train_class_samples[CLASSES])
{
    
    fprintf(TMDA_LOG_FILE, "Class No, Copied Test Samples, Copied Training Samples\n");
    for(int i = 0; i < CLASSES; i++)
    {
        fprintf(TMDA_LOG_FILE, "%d,%d,%d\n", i, count_test_class_samples[i], count_train_class_samples[i]);
        
    }
    
    fprintf(TMDA_LOG_FILE, "\n");
    
}

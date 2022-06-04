// dataio.c

// Standard Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

//Posix Headers
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Program Specific Headers
#include "dataio.h"


// VARIABLES 
DIR *Data_Input_Dir;				// Directory objects and structures
struct dirent *Data_Input_Dir_Entry;
DIR *Data_Output_Dir;
struct dirent *Data_Output_Dir_Entry;

FILE *Sample_Input_File;			// File objects
FILE *Processed_Data_Output_File;
FILE *EIDP_LOG_FILE_TEST;
FILE *EIDP_LOG_FILE_TRAIN;

int packet_size; 				// Packet Variables - User specified
int packet_overlap;	

int fe_mode;					// Feature Extraction Mode
int features_number;

long int sample_bytes;				// Packet Variables II - Determined by input sample file
long int sample_events;

int packets_req;				// Packet Variables III - Calculated using I and II above
int packet_events_overshoot;
int last_packet_zeros;
int last_packet_size;

long int EventPacketX[EVENTS_PER_SAMPLE_MAX]; 	// will store the event packet x,y,p,t values
long int EventPacketY[EVENTS_PER_SAMPLE_MAX]; 	
long int EventPacketP[EVENTS_PER_SAMPLE_MAX]; 	
long int EventPacketT[EVENTS_PER_SAMPLE_MAX]; 	

char output_dir_label[(DATA_OUT_NAME_MAX /2)];	// Directory label names - User specified
char output_dir_name[DATA_OUT_NAME_MAX];
int *p_f_packet_size;				// Pointer for dataio_print_to_file_literals_raw



// FUNCTIONS

// Allows the user to set the name of the output data (data that has been processed and booleanized)
void dataio_get_out_dir_label(char *output_dir_label)
{
    char user_input[(DATA_OUT_NAME_MAX/4)];
    char time_string[100] = "";
    
    time_t t = time(NULL);
    strftime(time_string, sizeof(time_string), "%Y%m%d_%H%M%S_", localtime(&t));
    strcat(output_dir_label, time_string);
    
    puts("Please enter a name for the data output directory.\n");
    printf("The name must be no more than %d characters.\n\n", (DATA_OUT_NAME_MAX/4));

    fgets(user_input, (DATA_OUT_NAME_MAX/4), stdin);
    user_input[strcspn(user_input, "\n")] = '\0'; // removes the return key
    strcat(output_dir_label, user_input);
}

// Allows the user to set the number of events in each packet to be processed, and the overlap of the event packets (in number of events)
void dataio_set_event_packet_vars(int *packet_size, int *packet_overlap)
{
    int p_s = 0;
    int p_o = 0;
    int p_s_flag = 0;
    int p_o_flag = 0;
    
    while(p_s_flag < 1)
    {
        printf("\nPlease enter the Event Packet Size.\nValue must be in the range %d to %d.\n\n", PACKET_MIN, PACKET_MAX);
       
        scanf("%d", &p_s);
        
        if(p_s < PACKET_MIN || p_s > PACKET_MAX)
        {
            printf("\nERROR: Event Packet Size must be between %d and %d!\n\n", PACKET_MIN, PACKET_MAX);
        }
        else
        if (p_s >= PACKET_MIN && p_s <= PACKET_MAX)
        {
            *packet_size = p_s;
            p_s_flag++;
        }
    }
    
    while(p_o_flag < 1)
    {
        if(p_s == 1)
        {
            *packet_overlap = 0;
            break;
        }
        
        printf("\nPlease enter the Event Packet Overlap.\nValue must be in the range 0 to %d.\n\n", (p_s - 1) );
       
        scanf("%d", &p_o);
        
        if(p_o < 0 || p_o > (p_s - 1) )
        {
            printf("\nERROR: Event Packet Overlap must be between 0 and %d!\n\n", (p_s - 1) );
        }
        else if (p_o >= 0 && p_o < p_s)
        {
            *packet_overlap = p_o;
            p_o_flag++;
        }
    }
}




// Select feature extraction mode
void dataio_set_features_mode(int *fe_mode)
{
    
    int mode = 0;
    int mode_flag = 0;
    
    int num_features = 0;
    int f_flag = 0;
    
    while(mode_flag < 1)
    {
        printf("Please select the Feature Extraction Method by entering 0, 1, or 2\n\n");
        printf("0 --- RAW  --- Creates boolean literals from unprocessed event data samples, there is no pre-processing.\n\n");
        printf("1 --- PBFE --- Packet Binary Feature Extraction\n\n");
        printf("2 --- IDFE --- Inter(-packet) Dynamics Feature Extraction\n\n");
        
        scanf("%d", &mode);
        
        if(mode < 0 || mode > 2)
        {
            printf("\nERROR: Please select a valid Feature Extraction Method!\n\n");
        }
        else
        if ( mode >= 0 || mode <= 2)
        {
            *fe_mode = mode;
            mode_flag++;
        }
    }
    
}

/*
// set number of features of output data: 4, 16, 64, 256, 1024
void dataio_set_features_number(int *features_number)
{
    int num = 0;
    int fn_flag = 0;
    
    while(fn_flag < 1)
    {
        printf("\nPlease enter the number of output features/literals.\n\nValue must be in the range %d to %d, and", FEATURES_MIN, FEATURES_MAX);
        printf("be a perfect square number!\n\n");
        scanf("%d", &num);
        
        int inum = 0;
        float fnum = 0;
        fnum = sqrt( (double)num );
        inum = fnum;
              
        if(fnum < FEATURES_MIN || fnum > PACKET_MAX)
        {
            printf("\nERROR: Number of Features must be between %d and %d!\n\n", FEATURES_MIN, FEATURES_MAX);
        }
        else
        if ( inum == fnum )
        {
            *features_number = num;
            fn_flag++;
        }
        else
        {
            printf("\nERROR: You selected %d, the number of features must be a perfect square!\n\n", num);
        }
        
        
    }

    
}
*/


// Function to create the new output directories
void dataio_create_output_dir(char *output_dir_label, char *output_dir_name)
{
    // Static Strings
    char *s0 = "./";
    char *s1 = "/Test/";
    char *s2 = "/Train/";
    
    // Strings
    char s3[10] = "";
    char local_dir_name1[DATA_OUT_NAME_MAX] = "mkdir -p ";
    char local_dir_name2[DATA_OUT_NAME_MAX] = "mkdir -p ";
    
    // create directory path ./output_dir_name/
    strcat(output_dir_name, s0);
    strcat(output_dir_name, output_dir_label);


    // create directory ./output_dir_name/Test/
    strcat(local_dir_name1, output_dir_name);
    strcat(local_dir_name1, s1);
    system(local_dir_name1);

    // create directory ./output_dir_name/Train/
    strcat(local_dir_name2, output_dir_name);
    strcat(local_dir_name2, s2);
    system(local_dir_name2);

    // create directory ./output_dir_name/Test/CLASSES .. 0 1 2 3 ... 9
    // create directory ./output_dir_name/Train/CLASSES .. 0 1 2 3 ... 9
    for(int i = 0; i<CLASSES; i++)
    {
        sprintf(s3, "%d", i);
        strcat(local_dir_name1, s3);
        strcat(local_dir_name2, s3);

        system(local_dir_name1);
        system(local_dir_name2);

        local_dir_name1[strlen(local_dir_name1)-1] = '\0'; // removing the last character, the class number
        local_dir_name2[strlen(local_dir_name2)-1] = '\0';
    }
}





// Opens data input directory, for the test data
DIR *dataio_open_data_input_dir_test(DIR *Data_Input_Dir, int c)
{
    char *s = "/";
    char class_num[2] = "";
    char input_dir_name[200] = "";
    
    sprintf(class_num, "%d", c);
    strcat(input_dir_name, TEST_IN_DIR);
    
    strcat(input_dir_name, class_num);
    strcat(input_dir_name, s);
    
    Data_Input_Dir = opendir(input_dir_name);
    
    if(Data_Input_Dir == NULL)
    {
        puts("ERROR: Unable to read directory!");
        exit(EXIT_FAILURE);
    }
    
    //printf("%s\n", input_dir_name);
    
    return Data_Input_Dir;
}

// Opens data input directory, for the training data
DIR *dataio_open_data_input_dir_train(DIR *Data_Input_Dir, int c)
{
    char *s = "/";
    char class_num[2] = "";
    char input_dir_name[200] = "";
    
    sprintf(class_num, "%d", c);
    strcat(input_dir_name, TRAIN_IN_DIR);
    
    strcat(input_dir_name, class_num);
    strcat(input_dir_name, s);
    
    Data_Input_Dir = opendir(input_dir_name);
    
    if(Data_Input_Dir == NULL)
    {
        puts("ERROR: Unable to read directory!");
        exit(EXIT_FAILURE);
    }
    
    //printf("%s\n", input_dir_name);
    
    return Data_Input_Dir;
}





// Opens data output directory, for the processed test data
DIR *dataio_open_data_output_dir_test(DIR *Data_Output_Dir, char* output_dir_name, int c)
{
    char *s = "/";
    char class_num[2] = "";
    char out_dir_name[200] = "";
    char *test = "/Test/";
    
    sprintf(class_num, "%d", c);
    strcat(out_dir_name, output_dir_name);
    strcat(out_dir_name, test);
    strcat(out_dir_name, class_num);
    strcat(out_dir_name, s);
    
    Data_Output_Dir = opendir(out_dir_name);
    
    if(Data_Output_Dir == NULL)
    {
        puts("ERROR: Unable to read directory!");
        exit(EXIT_FAILURE);
    }
    
    return Data_Output_Dir;

}

// Opens data output directory, for the processed train data
DIR *dataio_open_data_output_dir_train(DIR *Data_Output_Dir, char* output_dir_name, int c)
{
    char *s = "/";
    char class_num[2] = "";
    char out_dir_name[200] = "";
    char *train = "/Train/";
    
    sprintf(class_num, "%d", c);
    strcat(out_dir_name, output_dir_name);
    strcat(out_dir_name, train);
    strcat(out_dir_name, class_num);
    strcat(out_dir_name, s);
    
    Data_Output_Dir = opendir(out_dir_name);
    
    if(Data_Output_Dir == NULL)
    {
        puts("ERROR: Unable to read directory!");
        exit(EXIT_FAILURE);
    }
    
    return Data_Output_Dir;

}





// Opens test data input file,
FILE *dataio_open_data_input_file_test(DIR *Data_Input_Dir, FILE *Sample_Input_File, int c )
{
    char *s = "/";
    char class_num[2] = "";
    char input_file_path[200] = "";
    
    sprintf(class_num, "%d", c);
    strcat(input_file_path, TEST_IN_DIR);
    
    strcat(input_file_path, class_num);
    strcat(input_file_path, s);
    strcat(input_file_path, Data_Input_Dir_Entry->d_name);
    
    
    // Open file stream for the sample file, in read mode, binary
    Sample_Input_File = fopen(input_file_path,"rb");

    if(Sample_Input_File == NULL)
    {
        puts("Unable to open the file");
        exit(EXIT_FAILURE);
    }
    
    
   // printf("%s\n", input_file_path);
    
    return Sample_Input_File;
}

// Opens train data input file,
FILE *dataio_open_data_input_file_train(DIR *Data_Input_Dir, FILE *Sample_Input_File, int c )
{
    char *s = "/";
    char class_num[2] = "";
    char input_file_path[200] = "";
    
    sprintf(class_num, "%d", c);
    strcat(input_file_path, TRAIN_IN_DIR);
    
    strcat(input_file_path, class_num);
    strcat(input_file_path, s);
    strcat(input_file_path, Data_Input_Dir_Entry->d_name);
    
    
    // Open file stream for the sample file, in read mode, binary
    Sample_Input_File = fopen(input_file_path,"rb");

    if(Sample_Input_File == NULL)
    {
        puts("Unable to open the file");
        exit(EXIT_FAILURE);
    }
    
    
   // printf("%s\n", input_file_path);
    
    return Sample_Input_File;
}







// Opens processed test data output file
FILE *dataio_open_data_output_file_test(DIR *Data_Output_Dir, char* output_dir_name, FILE *Processed_Data_Output_File, int c)
{
    char *s = "/";
    char classnum[2] = "";
    char out_file_path[300] = "";
    char *test = "/Test/";
    
    // Creates the file path name using strcat
    sprintf(classnum, "%d", c);
    strcat(out_file_path, output_dir_name);
    strcat(out_file_path, test);
    strcat(out_file_path, classnum);
    strcat(out_file_path, s);
    strcat(out_file_path, Data_Input_Dir_Entry->d_name);
    
    // REMOVED bin from sample file path
    char *temp;
    temp = strchr(out_file_path,'b');   //Get the pointer to char token
    *temp = '\0';             //Replace token with null char
    
    
    //printf("The samplefilepath is %s\n",samplefilepathname);
    strcat(out_file_path, "txt");
    
    
    // Open file stream for the sample file, in read mode, binary
    Processed_Data_Output_File = fopen(out_file_path,"w");

    
    if(Processed_Data_Output_File == NULL)
    {
        puts("Unable to create the output file");
        exit(EXIT_FAILURE);
    }
    
    return Processed_Data_Output_File;
}

// Opens processed train data output file
FILE *dataio_open_data_output_file_train(DIR *Data_Output_Dir, char* output_dir_name, FILE *Processed_Data_Output_File, int c)
{
    char *s = "/";
    char classnum[2] = "";
    char out_file_path[300] = "";
    char *train = "/Train/";
    
    // Creates the file path name using strcat
    sprintf(classnum, "%d", c);
    strcat(out_file_path, output_dir_name);
    strcat(out_file_path, train);
    strcat(out_file_path, classnum);
    strcat(out_file_path, s);
    strcat(out_file_path, Data_Input_Dir_Entry->d_name);
    
    // REMOVED bin from sample file path
    char *temp;
    temp = strchr(out_file_path,'b');   //Get the pointer to char token
    *temp = '\0';             //Replace token with null char
    
    
    //printf("The samplefilepath is %s\n",samplefilepathname);
    strcat(out_file_path, "txt");
    
    
    // Open file stream for the sample file, in read mode, binary
    Processed_Data_Output_File = fopen(out_file_path,"w");

    
    if(Processed_Data_Output_File == NULL)
    {
        puts("Unable to create the output file");
        exit(EXIT_FAILURE);
    }
    
    return Processed_Data_Output_File;
}





// Gets number of  bytes and events from the input sample file
void dataio_get_input_sample_var(FILE *Sample_Input_File, long int *sample_bytes, long int *sample_events)
{
    fseek(Sample_Input_File, 0, SEEK_END);

        *sample_bytes = ftell(Sample_Input_File);
        *sample_events = ( ftell(Sample_Input_File) ) / EVENT_BUFF_SIZE;
}

// Sets secondary packet variables using the user input and sample file variables
void datio_set_secondary_event_packet_vars(long int sample_events, int packet_size, int packet_overlap, int *packets_req,
                                 int *packet_events_overshoot, int *last_packet_zeros, int *last_packet_size)
{
    if (packet_size == 1 && packet_overlap == 0)
    {
    *packets_req = sample_events;
    *last_packet_size = 1;
    }
    else
    {
    *packets_req = (sample_events / (packet_size - packet_overlap)) + 1;
    *packet_events_overshoot = (*packets_req) * (packet_size - packet_overlap);
    *last_packet_zeros = (*packet_events_overshoot) - sample_events;
    *last_packet_size = packet_size - (*last_packet_zeros);
    }
}





void dataio_zero_event_packet_arrays(long int EventPacketX[],long int EventPacketY[],long int EventPacketP[],long int EventPacketT[])
{
    
    for(int i = 0; i < EVENTS_PER_SAMPLE_MAX; i++)
    {
        EventPacketX[i] = 0;
        EventPacketY[i] = 0;
        EventPacketP[i] = 0;
        EventPacketT[i] = 0;
    }

}

void dataio_extract_event_packets(FILE *Sample_Input_File, int byte_no, int f_packet_size, int *packet_event_no,long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[])
{

    for(int byte_no_offset = byte_no; byte_no_offset < (byte_no + (f_packet_size * EVENT_BUFF_SIZE)); byte_no_offset += EVENT_BUFF_SIZE)
    {

        unsigned char buffer[EVENT_BUFF_SIZE];
        //Set file position
        fseek(Sample_Input_File, byte_no_offset, SEEK_SET);

        // read 5 bytes to buffer
        fread(buffer,sizeof *buffer, EVENT_BUFF_SIZE, Sample_Input_File);

        //for debug
        //printf("%u\t%u\t%u\t%u\t%u\t\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);


        int event_no = byte_no_offset / 5;


        EventPacketX[*packet_event_no] = buffer[0] + 1; // will store the event packet x values
        EventPacketY[*packet_event_no] = buffer[1] + 1; // will store the event packet y values
        EventPacketP[*packet_event_no] = buffer[2] >> 7; // will store the event packet p values
        EventPacketT[*packet_event_no] = ((buffer[2] & 127) << 16) + (buffer[3] << 8) + buffer[4] ; // will store the event packet t values

        //printf("Event number %d --> \t%lu\t%lu", *packet_event_no, EventPacketX[*packet_event_no],EventPacketY[*packet_event_no]);
        //printf("\t%lu\t%lu\n",EventPacketP[*packet_event_no],EventPacketT[*packet_event_no]);


        *packet_event_no = *packet_event_no + 1;


    }

    
}

void dataio_print_to_file_literals_raw(FILE *Processed_Data_Output_File, int literals_raw[RAW_BOOL_MAX][*p_f_packet_size], int *p_f_packet_size)
{

    char buf[2] = "";
    char *space = " ";
    char line[(2 * RAW_BOOL_MAX) + 1];
    int local_packet_size = *p_f_packet_size;
    
    for(int a = 0; a < local_packet_size; a++)
    {

        for(int b = 0; b < RAW_BOOL_MAX; b++)
        {
            sprintf(buf, "%d", literals_raw[b][a]);
            strcat(line,buf);
            memset(buf,0,sizeof(buf));
            if( b < (RAW_BOOL_MAX - 1) )
            {
            strcat(line,space);
            }
               
        }

        fprintf(Processed_Data_Output_File, "%s\n", line);
        memset(line,0,sizeof(line));

    }

}



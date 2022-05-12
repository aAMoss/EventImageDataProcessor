// dataio.c

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
#include "dataio.h"





DIR *dataio_open_data_input_dir(DIR *Data_Input_Dir, int c)
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
    
    printf("%s\n", input_dir_name);
    
    return Data_Input_Dir;

}


FILE *dataio_open_data_input_file(DIR *Data_Input_Dir, FILE *Sample_Input_File, int c )
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
    
    
    printf("%s\n", input_file_path);
    
    return Sample_Input_File;
}







void dataio_get_input_sample_var(FILE *Sample_Input_File, long int *sample_bytes, long int *sample_events)
{
    fseek(Sample_Input_File, 0, SEEK_END);

        *sample_bytes = ftell(Sample_Input_File);
        *sample_events = ( ftell(Sample_Input_File) ) / EVENT_BUFF_SIZE;
}


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


void dataio_extract_event_packets(FILE *Sample_Input_File, int byte_no, int f_packet_size, int *packet_event_no)
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

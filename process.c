// process.c

// Standard Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Posix Headers
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Program Specific Headers
#include "process.h"

void dataio_print_to_file_literals_raw(FILE *Processed_Data_Output_File, int literals_raw[RAW_BOOL_MAX][f_packet_size], int packet_size);

void process_event_data(int sample_events,int packet_size, int packet_overlap, int packets_req, int last_packet_size, int c,
                        long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[])
{

    int byte_no = 0;
    int f_packet_size = 0;
    int event_no = 0;
    int packet_event_no = 0;
    
    int literals_raw[RAW_BOOL_MAX][f_packet_size];
    
    // Run for N number of packets to extract all data
    for(int packet_no = 0; packet_no < packets_req; packet_no++)
    {
        
        
        // Zero the packet arrays
        dataio_zero_event_packet_arrays(EventPacketX,EventPacketY, EventPacketP,EventPacketT);
        
        
        // Select variables for first N-1 packets, and last Nth packet
        if(packet_no < (packets_req - 1))
        {
            byte_no = packet_no * (packet_size - packet_overlap) * EVENT_BUFF_SIZE;
            f_packet_size = packet_size;
            packet_event_no = 0;
            
        } else
        if(packet_no == (packets_req - 1))
        {
            byte_no = (sample_events - last_packet_size) * EVENT_BUFF_SIZE;
            f_packet_size = last_packet_size;
            packet_event_no = 0;
        }
        
        
        
        printf("packet_no %d\t", packet_no);
        printf("byte_no %d\t", byte_no);
        printf("f_packet_size %d\n", f_packet_size);
        
        // Extract a packets worth of event data
        dataio_extract_event_packets(Sample_Input_File, byte_no, f_packet_size, &packet_event_no, EventPacketX,EventPacketY, EventPacketP,EventPacketT);
        
        
        
        // FEATURES - Comment out as necessary
        features_literals_raw_data(EventPacketX, EventPacketY, EventPacketP, EventPacketT,f_packet_size, c, literals_raw);

        
        // PRINT TO FILE - Comment out as necessary
        dataio_print_to_file_literals_raw(Processed_Data_Output_File, literals_raw, f_packet_size);
        // will require output directory and file opening!!! see main.c and datio.c!!!
        
        
        // Print to terminal for checking output and debug
        for(int a = 0; a < f_packet_size; a++)
        {
            
            printf("Packet Event No --> %d \t%lu\t%lu", a, EventPacketX[a],EventPacketY[a]);
            printf("\t%lu\t%lu\t",EventPacketP[a],EventPacketT[a]);
            for(int b = 0; b < RAW_BOOL_MAX; b++)
            {

                printf("%d", literals_raw[b][a]);

            }

            printf("\n");
        }



    }
    
}



void dataio_print_to_file_literals_raw(FILE *Processed_Data_Output_File, int literals_raw[RAW_BOOL_MAX][f_packet_size], int packet_size)
{
    
    char buf[2] = "";
    char *space = " ";
    char line[ (2 * ((2 * RAW_XY_BOOL) + RAW_P_BOOL + RAW_T_BOOL + RAW_C_BOOL)) + 1 ] = "";
    
    for(int a = 0; a < f_packet_size; a++)
    {
        
        for(int b = 0; b < RAW_BOOL_MAX; b++)
        {
            
            sprintf(buf, "%d", literals_raw[b][a]);
            strcat(line,buf);
            strcat(line,space);
            //printf("%d", literals_raw[b][a]);
            fprintf(Processed_Data_Output_File, "%s\n", line);

        }
    
    }

}

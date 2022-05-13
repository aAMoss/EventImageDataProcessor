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


int *p_f_packet_size;

void dataio_print_to_file_literals_raw(FILE *Processed_Data_Output_File, int literals_raw[RAW_BOOL_MAX][*p_f_packet_size], int *p_f_packet_size);

void process_event_data(int sample_events,int packet_size, int packet_overlap, int packets_req, int last_packet_size, int c,
                        long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[])
{

    int byte_no = 0;
    int f_packet_size = 0;
    
    int event_no = 0;
    int packet_event_no = 0;
    
    
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
            p_f_packet_size = &f_packet_size;
            packet_event_no = 0;
            
        } else
        if(packet_no == (packets_req - 1))
        {
            byte_no = (sample_events - last_packet_size) * EVENT_BUFF_SIZE;
            f_packet_size = last_packet_size;
            p_f_packet_size = &f_packet_size;
            packet_event_no = 0;
        }
        
        
        // Arrays to store int version of the literals/booleans, has to be called after f_packet)size is set
        int literals_raw[RAW_BOOL_MAX][f_packet_size];
        
        printf("packet_no %d\t", packet_no);
        printf("byte_no %d\t", byte_no);
        printf("f_packet_size %d\n", f_packet_size);
        
        // Extract a packets worth of event data
        dataio_extract_event_packets(Sample_Input_File, byte_no, f_packet_size, &packet_event_no, EventPacketX,EventPacketY, EventPacketP,EventPacketT);
        
       
        
        
        // FEATURES - Comment out as necessary
        features_literals_raw_data(EventPacketX, EventPacketY, EventPacketP, EventPacketT,f_packet_size, c, literals_raw);

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

        
        
        // I appear to ahve done something that causes an illegal hardware instruction with dataio_print ...
        
//      // PRINT TO FILE - Comment out as necessary
        dataio_print_to_file_literals_raw(Processed_Data_Output_File, literals_raw, p_f_packet_size);
//
        



    }
    
}


// I think the illegal hardware fault has something to do with *p_f_packetsize, might have to retool all the code in processes, to accomodate
// the packet_size and final_packet_size
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
            strcat(line,space);
        }

        fprintf(Processed_Data_Output_File, "%s\n", line);
        memset(line,0,sizeof(line));

    }

}

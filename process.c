// process.c

// Standard Headers
#include <stdio.h>
#include <stdlib.h>

//Posix Headers
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "process.h"
#include "dataio.h"



void process_event_data(int sample_events,int packet_size, int packet_overlap, int packets_req, int last_packet_size,
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
        dataio_extract_event_packets(Sample_Input_File, byte_no, f_packet_size, &packet_event_no);
        
        for(int i = 0; i < f_packet_size; i++)
        {
            
            printf("Packet Vars --> %d \t%lu\t%lu", i, EventPacketX[i],EventPacketY[i]);
            printf("\t%lu\t%lu\n",EventPacketP[i],EventPacketT[i]);
            
            
        }
        
    }
    
}


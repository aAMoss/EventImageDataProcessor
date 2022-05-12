// process.c

// Standard Headers
#include <stdio.h>
#include <stdlib.h>





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
        
        
        // process to booleans
        // write to file
        
        
//        for(int byte_no_offset = byte_no; byte_no_offset < (byte_no + (f_packet_size * EVENT_BUFF_SIZE)); byte_no_offset += EVENT_BUFF_SIZE)
//        {
//
//            unsigned char buffer[EVENT_BUFF_SIZE];
//            //Set file position
//            fseek(Sample_Input_File, byte_no_offset, SEEK_SET);
//
//            // read 5 bytes to buffer
//            fread(buffer,sizeof *buffer, EVENT_BUFF_SIZE, Sample_Input_File);
//
//            //for debug
//            //printf("%u\t%u\t%u\t%u\t%u\t\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
//
//
//            event_no = byte_no_offset / 5;
//
//
//            EventPacketX[packet_event_no] = buffer[0] + 1; // will store the event packet x values
//            EventPacketY[packet_event_no] = buffer[1] + 1; // will store the event packet y values
//            EventPacketP[packet_event_no] = buffer[2] >> 7; // will store the event packet p values
//            EventPacketT[packet_event_no] = ((buffer[2] & 127) << 16) + (buffer[3] << 8) + buffer[4] ; // will store the event packet t values
//
//            printf("Event number %d --> \t%lu\t%lu", packet_event_no, EventPacketX[packet_event_no],EventPacketY[packet_event_no]);
//            printf("\t%lu\t%lu\n",EventPacketP[packet_event_no],EventPacketT[packet_event_no]);
//
//
//            packet_event_no++;
//
//
//        }
        
        
        // Data Functions to print data to file and booleanize go here!
        
    }
    
}




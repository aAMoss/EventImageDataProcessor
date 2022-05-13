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



//extern int literals_raw[RAW_BOOL_MAX][packet_size];


//void literals_raw_event_data(long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[],
//                             int f_packet_size, int c, int literals_raw[RAW_BOOL_MAX][*packet_size] );

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
        
        
//        literals_raw_event_data(EventPacketX, EventPacketY, EventPacketP, EventPacketT,
//                                     f_packet_size, c, literals_raw )
        
//        // print event packets
//        for(int i = 0; i < f_packet_size; i++)
//        {
//
//            printf("Packet Vars --> %d \t%lu\t%lu", i, EventPacketX[i],EventPacketY[i]);
//            printf("\t%lu\t%lu\n",EventPacketP[i],EventPacketT[i]);
//
//        }
//
        
        
//
//        for(int a = 0; a < f_packet_size; a++)
//        {
//            for(int b = 0; b < RAW_BOOL_MAX; b++)
//            {
//
//                printf("%d", literals_raw[b][a]);
//
//            }
//
//            printf("\n");
//        }



    }
    
}


//void literals_raw_event_data(long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[],
//                             int f_packet_size, int c, int literals_raw[RAW_BOOL_MAX][packet_size] )
//{
//    // var needs to be outside in .h or elsewhere
//    //int literals_raw[RAW_BOOL_MAX][f_packet_size];
//
//
//    for(int a = 0; a < f_packet_size; a++)
//    {
//        for(int b = 0; b < RAW_BOOL_MAX; b++)
//        {
//
//            literals_raw[b][a] = 0;
//
//        }
//
//    }
//
//
//
//    long int EventInX = 0;
//    long int EventInY = 0;
//    long int EventInP = 0;
//    long int EventInT = 0;
//    int class = c;
//
//    for(int e = 0; e < f_packet_size; e++)
//    {
//
//        //COUNTERS
//        int countX = RAW_XY_BOOL - 1;
//        int countY = (2 * RAW_XY_BOOL) - 1;
//        int countP = (2 * RAW_XY_BOOL) + RAW_P_BOOL - 1;
//        int countT = (2 * RAW_XY_BOOL) + RAW_P_BOOL + RAW_T_BOOL - 1;
//        int countC = (2 * RAW_XY_BOOL) + RAW_P_BOOL + RAW_T_BOOL + RAW_C_BOOL - 1;
//
//        EventInX = EventPacketX[e];
//        EventInY = EventPacketY[e];
//        EventInP = EventPacketP[e];
//        EventInT = EventPacketT[e];
//
//
//        //CREATE X BOOLS - counts from place 5 to place 0
//        while (EventInX >= 1)
//        {
//            literals_raw[countX][e] = EventInX % 2;
//            EventInX = EventInX / 2;
//            countX--;
//        }
//
//        // CREATE Y BOOLS - counts from place 11 to place 6
//        while (EventInY >= 1)
//        {
//            literals_raw[countY][e] = EventInY % 2;
//            EventInY = EventInY / 2;
//            countY--;
//        }
//
//        // CREATE P BOOLS - writes to place 12
//        literals_raw[countP][e] = EventInP;
//
//        // CREATE T BOOLS - counts from place 36 to place 13
//        while (EventInT >= 1)
//        {
//            literals_raw[countT][e] = EventInT % 2;
//            EventInT = EventInT / 2;
//            countT--;
//        }
//
//       //CREATE C BOOLS - counts from place 40 to place 37
//        while (class >= 1)
//        {
//            literals_raw[countC][e] = class % 2;
//            class = class / 2;
//            countC--;
//        }
//
//    }
//
//
//
//
//
//
//
//
//
//
//
//
//
//}

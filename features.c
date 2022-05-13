// features.c

// Standard Headers
#include <stdio.h>
#include <stdlib.h>

//Posix Headers
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Program Specific Headers
#include "features.h"



void features_literals_raw_data(long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[],
                             int f_packet_size, int c, int literals_raw[RAW_BOOL_MAX][f_packet_size] )
{



    for(int a = 0; a < f_packet_size; a++)
    {
        for(int b = 0; b < RAW_BOOL_MAX; b++)
        {

            literals_raw[b][a] = 0;

        }

    }



    long int EventInX = 0;
    long int EventInY = 0;
    long int EventInP = 0;
    long int EventInT = 0;
    int class = c;

    for(int e = 0; e < f_packet_size; e++)
    {

        //COUNTERS
        int countX = RAW_XY_BOOL - 1;
        int countY = (2 * RAW_XY_BOOL) - 1;
        int countP = (2 * RAW_XY_BOOL) + RAW_P_BOOL - 1;
        int countT = (2 * RAW_XY_BOOL) + RAW_P_BOOL + RAW_T_BOOL - 1;
        int countC = (2 * RAW_XY_BOOL) + RAW_P_BOOL + RAW_T_BOOL + RAW_C_BOOL - 1;

        EventInX = EventPacketX[e];
        EventInY = EventPacketY[e];
        EventInP = EventPacketP[e];
        EventInT = EventPacketT[e];


        //CREATE X BOOLS - counts from place 5 to place 0
        while (EventInX >= 1)
        {
            literals_raw[countX][e] = EventInX % 2;
            EventInX = EventInX / 2;
            countX--;
        }

        // CREATE Y BOOLS - counts from place 11 to place 6
        while (EventInY >= 1)
        {
            literals_raw[countY][e] = EventInY % 2;
            EventInY = EventInY / 2;
            countY--;
        }

        // CREATE P BOOLS - writes to place 12
        literals_raw[countP][e] = EventInP;

        // CREATE T BOOLS - counts from place 36 to place 13
        while (EventInT >= 1)
        {
            literals_raw[countT][e] = EventInT % 2;
            EventInT = EventInT / 2;
            countT--;
        }

       //CREATE C BOOLS - counts from place 40 to place 37
        while (class >= 1)
        {
            literals_raw[countC][e] = class % 2;
            class = class / 2;
            countC--;
        }

    }

}





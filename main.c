// main.c

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
#include "main.h"


#define EVENTS_PER_SAMPLE_MAX 10000

#define DATA_IN_NAME_MAX 200





//
//    // BOOLEANIZE LITERALS AND WRITE TO FILE
//    for( int s = 0; s < PacketSize; s++)
//    {
//        Features_PolarityIntegrate(EventPacketX[s], EventPacketY[s], EventPacketP[s], EventPacketT[s], EventPacketFrame,
//                                  EventPacketFramePOS, EventPacketFrameNEG);
//
//        //literals function/s called here
//        char line[ (2 * ((2 * RAW_XY_BOOL) + RAW_P_BOOL + RAW_T_BOOL + RAW_C_BOOL)) + 1 ] = "";
//        Literals_Raw(line, EventPacketX[s], EventPacketY[s], EventPacketP[s], EventPacketT[s], c, sizeof(line));
//        fprintf(BoolSampleOut, "%s\n", line);
//    }
//    display_PrintFeaturesPolarityIntegrate(EventPacketFrame);
    
    
    
    
    


//
//
//// will extract event data of last packet
//void datio_process_final_variable_packet()
//{
//
//    // FINAL (Nth) EVENT IN PACKET
//    int ByteNo = (SampleEvents - LastPacketSize) * BUFFSIZE;
//    int PacketEventCounter = 0;
//    //printf("Processing packet number %d!\n",PacketsReq - 1);
//    // LAST PACKET
//    
//
//    //packet read function goes here!!!!!!!!!!!
//   dataio_ExtractEventDataToPacket(ByteNo, PacketSize, &PacketEventCounter, EventSampleIn);
//    
//    
//    
//    // WRITE LAST PACKET TO FILE
//    for( int s = 0; s < LastPacketSize; s++)
//    {
//
//        
//        Features_PolarityIntegrate(EventPacketX[s], EventPacketY[s], EventPacketP[s], EventPacketT[s], EventPacketFrame,
//                                  EventPacketFramePOS, EventPacketFrameNEG);
//        
//        char line[ (2 * ((2 * RAW_XY_BOOL) + RAW_P_BOOL + RAW_T_BOOL + RAW_C_BOOL)) + 1 ] = "";
//        Literals_Raw(line, EventPacketX[s], EventPacketY[s], EventPacketP[s], EventPacketT[s], c, sizeof(line));
//        fprintf(BoolSampleOut, "%s\n", line);
//        
//        
//    }
//    
//    
//    
//    
//}
//
//
//
//



// Event Packet Arrays
long int EventPacketX[EVENTS_PER_SAMPLE_MAX]; // will store the event packet x values
long int EventPacketY[EVENTS_PER_SAMPLE_MAX]; // will store the event packet y values
long int EventPacketP[EVENTS_PER_SAMPLE_MAX]; // will store the event packet p values
long int EventPacketT[EVENTS_PER_SAMPLE_MAX]; // will store the event packet t values


void dataio_extract_event_data( FILE *Sample_Input_File, int byte_no, int packet_size, long int EventPacketX[], long int EventPacketY[],
                               long int EventPacketP[],long int EventPacketT[])
{

for(int byte_no_offset = byte_no; byte_no_offset < (packet_size * EVENT_BUFF_SIZE); byte_no_offset += EVENT_BUFF_SIZE)
                    {
                        
                        unsigned char buffer[EVENT_BUFF_SIZE];
                        //Set file position
                        fseek(Sample_Input_File, byte_no_offset, SEEK_SET);

                        // read 5 bytes to buffer
                        fread(buffer,sizeof *buffer, EVENT_BUFF_SIZE, Sample_Input_File);

                        //for debug
                        printf("%u\t%u\t%u\t%u\t%u\t\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
      
                        
                        int event_no = byte_no_offset / 5;
                        
                        
                        EventPacketX[event_no] = buffer[0] + 1; // will store the event packet x values
                        EventPacketY[event_no] = buffer[1] + 1; // will store the event packet y values
                        EventPacketP[event_no] = buffer[2] >> 7; // will store the event packet p values
                        EventPacketT[event_no] = ((buffer[2] & 127) << 16) + (buffer[3] << 8) + buffer[4] ; // will store the event packet t values
                        
//                        printf("Event number %d --> \t%lu\t%lu", event_no, EventPacketX[event_no],EventPacketY[event_no]);
//                        printf("\t%lu\t%lu\n",EventPacketP[event_no],EventPacketT[event_no]);
                        
                
                        
                    }

}





void datio_process_n_minus_one_packets(int packet_size, int packet_overlap, int packets_req)
{
    for(int packet_no = 0; packet_no < (packets_req - 1); packet_no++ )
    {
        
        int byte_no = packet_no * (packet_size - packet_overlap) * EVENT_BUFF_SIZE;
        
        //printf("\nPacket Number: %d / %d\n", packet_no, (packets_req - 1) );
        dataio_extract_event_data(Sample_Input_File, byte_no, packet_size, EventPacketX, EventPacketY, EventPacketP, EventPacketT);
        
        
        
    }

}

void datio_process_nth_packet(int packet_size, int packet_overlap, int packets_req)
{
    
    int byte_no = (sample_events - packet_size) * EVENT_BUFF_SIZE;
    
    printf("\nPacket Number: %d / %d\n", (packets_req - 1), (packets_req - 1) );
    dataio_extract_event_data(Sample_Input_File, byte_no, packet_size, EventPacketX, EventPacketY, EventPacketP, EventPacketT);

}

void print_sample_data(int sample_events, long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[])
{
    
    for(int i = 0; i < sample_events; i++)
    {
        
        
        printf("Event number %d --> \t%lu\t%lu", i, EventPacketX[i],EventPacketY[i]);
        printf("\t%lu\t%lu\n",EventPacketP[i],EventPacketT[i]);
        
        
        
    }
    
    
    
    
}



int main(void)
{
    
    // Sets the name for the output data
    config_get_out_dir_label(output_dir_label);
    
    // Creates the output data directories
    config_create_output_dir(output_dir_label, output_dir_name);
    
    // Sets the packet variables: size and overlap
    config_set_event_packet_vars(&packet_size, &packet_overlap);
    
    // Runs for everyone of the test data classes
    for(int c = 0; c < CLASSES; c++)
    {
        
        // Opens the input directory of the N-MNIST Dataset
        Data_Input_Dir = dataio_open_data_input_dir(Data_Input_Dir, c);

        while(  (Data_Input_Dir_Entry = readdir(Data_Input_Dir)) )
        {

            if(strcmp(Data_Input_Dir_Entry->d_name, ".") != 0 && strcmp(Data_Input_Dir_Entry->d_name, "..") != 0 &&
               strcmp(Data_Input_Dir_Entry->d_name, ".DS_Store"))
            {
        
                printf("%s\n",Data_Input_Dir_Entry->d_name);
                
                
                Sample_Input_File = dataio_open_data_input_file(Data_Input_Dir, Sample_Input_File, c);
                
                
                puts("Input and output files opened!");
                
                dataio_get_input_sample_var(Sample_Input_File, &sample_bytes, &sample_events);
                
                datio_set_secondary_event_packet_vars(sample_events, packet_size, packet_overlap, &packets_req,
                                                      &packet_events_overshoot, &last_packet_zeros, &last_packet_size);

                printf("Bytes\tEvents\tpacket_size\tpacket_overlap\tpackets_req\tOverShoot\tlast_packet_zeros\tlast_packet_size\n");
                printf("%ld\t%ld\t%d\t\t%d\t\t%d\t\t",sample_bytes, sample_events, packet_size, packet_overlap, packets_req);
                printf("%d\t\t%d\t\t\t%d\n",packet_events_overshoot, last_packet_zeros, last_packet_size);
                
                
                
                datio_process_n_minus_one_packets(packet_size, packet_overlap, packets_req);
                datio_process_nth_packet(last_packet_size, packet_overlap, packets_req);
                
                //print_sample_data(sample_events, EventPacketX, EventPacketY, EventPacketP,EventPacketT);
                
                
                fclose(Sample_Input_File);
                
            } // close if
        
        } // close while
        
        
    } // close for
    
    
    // once ready and tested will duplicate all again for training data
    
    //5589
    
    
    return 0;
}



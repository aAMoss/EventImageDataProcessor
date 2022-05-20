// eidp.c

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
#include "eidp.h"



int main(void)
{
    
    // Sets the name for the output data
    dataio_get_out_dir_label(output_dir_label);
    
    // Creates the output data directories
    dataio_create_output_dir(output_dir_label, output_dir_name);
    
    // Sets the packet variables: size and overlap
    dataio_set_event_packet_vars(&packet_size, &packet_overlap);
    
    dataio_set_features_mode(&fe_mode);
                
    // Runs for everyone of the test data classes
    for(int c = 0; c < CLASSES; c++)
    {
        
        // Opens the input directory of the N-MNIST Dataset
        Data_Input_Dir = dataio_open_data_input_dir_test(Data_Input_Dir, c);
        
        //Opens the output directory for the processed data
        Data_Output_Dir = dataio_open_data_output_dir_test(Data_Output_Dir, output_dir_name, c);
        
        while(  (Data_Input_Dir_Entry = readdir(Data_Input_Dir)) )
        {

            if(strcmp(Data_Input_Dir_Entry->d_name, ".") != 0 && strcmp(Data_Input_Dir_Entry->d_name, "..") != 0 &&
               strcmp(Data_Input_Dir_Entry->d_name, ".DS_Store"))
            {
        
                printf("%s\n",Data_Input_Dir_Entry->d_name);
                
                
                Sample_Input_File = dataio_open_data_input_file_test(Data_Input_Dir, Sample_Input_File, c);
                Processed_Data_Output_File = dataio_open_data_output_file_test(Data_Output_Dir, output_dir_name, Processed_Data_Output_File, c);
                
                puts("Input and output files opened!");
                
                dataio_get_input_sample_var(Sample_Input_File, &sample_bytes, &sample_events);
                
                datio_set_secondary_event_packet_vars(sample_events, packet_size, packet_overlap, &packets_req,
                                                      &packet_events_overshoot, &last_packet_zeros, &last_packet_size);

                printf("Bytes\tEvents\tpacket_size\tpacket_overlap\tpackets_req\tOverShoot\tlast_packet_zeros\tlast_packet_size\n");
                printf("%ld\t%ld\t%d\t\t%d\t\t%d\t\t",sample_bytes, sample_events, packet_size, packet_overlap, packets_req);
                printf("%d\t\t%d\t\t\t%d\n",packet_events_overshoot, last_packet_zeros, last_packet_size);
                
                
                process_event_data(sample_events, packet_size, packet_overlap, packets_req, last_packet_size, c,
                                   EventPacketX, EventPacketY, EventPacketP, EventPacketT, fe_mode);
                
                fclose(Sample_Input_File);
                fclose(Processed_Data_Output_File);
                
            } // close if
        
        } // close while
        
        closedir(Data_Output_Dir);
        closedir(Data_Input_Dir);
        
    } // End Classes For Loop
    
    
    
    
    // Runs for everyone of the training data classes
    for(int c = 0; c < CLASSES; c++)
    {
        
        // Opens the input directory of the N-MNIST Dataset
        Data_Input_Dir = dataio_open_data_input_dir_train(Data_Input_Dir, c);
        
        //Opens the output directory for the processed data
        Data_Output_Dir = dataio_open_data_output_dir_train(Data_Output_Dir, output_dir_name, c);
        
        while(  (Data_Input_Dir_Entry = readdir(Data_Input_Dir)) )
        {

            if(strcmp(Data_Input_Dir_Entry->d_name, ".") != 0 && strcmp(Data_Input_Dir_Entry->d_name, "..") != 0 &&
               strcmp(Data_Input_Dir_Entry->d_name, ".DS_Store"))
            {
        
                printf("%s\n",Data_Input_Dir_Entry->d_name);
                
                
                Sample_Input_File = dataio_open_data_input_file_train(Data_Input_Dir, Sample_Input_File, c);
                Processed_Data_Output_File = dataio_open_data_output_file_train(Data_Output_Dir, output_dir_name, Processed_Data_Output_File, c);
                
                puts("Input and output files opened!");
                
                dataio_get_input_sample_var(Sample_Input_File, &sample_bytes, &sample_events);
                
                datio_set_secondary_event_packet_vars(sample_events, packet_size, packet_overlap, &packets_req,
                                                      &packet_events_overshoot, &last_packet_zeros, &last_packet_size);

                printf("Bytes\tEvents\tpacket_size\tpacket_overlap\tpackets_req\tOverShoot\tlast_packet_zeros\tlast_packet_size\n");
                printf("%ld\t%ld\t%d\t\t%d\t\t%d\t\t",sample_bytes, sample_events, packet_size, packet_overlap, packets_req);
                printf("%d\t\t%d\t\t\t%d\n",packet_events_overshoot, last_packet_zeros, last_packet_size);
                
                
                process_event_data(sample_events, packet_size, packet_overlap, packets_req, last_packet_size, c,
                                   EventPacketX, EventPacketY, EventPacketP, EventPacketT, fe_mode);
                
                fclose(Sample_Input_File);
                fclose(Processed_Data_Output_File);
                
            } // close if
        
        } // close while
        
        closedir(Data_Output_Dir);
        closedir(Data_Input_Dir);
        
    } // End Classes For Loop
    
    
    
    
    
    return 0;
}




//void PostProcessingDataRecord()
//{
//
////Create data processing information file here
//
////Will have two functions eventually, one to create the file and one to update/populate it
//
//FILE *PostProcData;
//
//// will modify this so it dynamically creates a name with the current date and time
//const char* fname = "./DataOUT/PostProcessingData.txt"; // or tmpnam(NULL);
//
//time_t systemtime;
//struct tm *calendarinfo;
//char buftime[80];
//
//time(&systemtime);
//calendarinfo = localtime( &systemtime );
//strftime(buftime,80,"%A %d %Y -- %H:%M:%S", calendarinfo);
//
//
//
//PostProcData = fopen(fname,"w");
//rewind(PostProcData);
//

//
//#define MAXFRAME_X 32
//#define MAXFRAME_Y 32
//
//int EventPacketFrame[MAXFRAME_X][MAXFRAME_Y];
//int EventPacketFramePOS[MAXFRAME_X][MAXFRAME_Y];
//int EventPacketFrameNEG[MAXFRAME_X][MAXFRAME_Y];
//
//
//
//







//void dataio_ZeroEventPacketArrays(unsigned long int EventPacket[SAMPLEMAXSIZE])
//{
//
//    for(int i = 0; i < SAMPLEMAXSIZE; i++)
//    {
//        EventPacket[i] = 0;
//    }
//
//                //Old version
//                // // ZERO EVENT PACKET ARRAYS
//                // for(int i = 0; i < SAMPLEMAXSIZE; i++)
//                // {
//                //     EventPacketX[i] = 0;
//                //     EventPacketY[i] = 0;
//                //     EventPacketP[i] = 0;
//                //     EventPacketT[i] = 0;
//                // }
//
//}

//void DisplayEventPacket()
//{
//
//    int x = 32;
//    int y = 32;
//
//    int frame[x][y] = {0};
//
//
//
//    for(int i = 0; i < x; i++)
//    {
//        for(int j = 0; j < y; j++)
//        {
//            printf("%d     ", frame[i][j]);
//        }
//        printf("\n");
//    }
//
//}



//int row, columns;
//for (row=0; row<numberOfLines; row++)
//{
//    for(columns=0; columns<numberColumns; columns++)
//    {
//         printf("%d     ", matrix[row][columns]);
//    }
//    printf("\n");
//}




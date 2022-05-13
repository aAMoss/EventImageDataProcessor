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


int main(void)
{
    
    // Sets the name for the output data
    dataio_get_out_dir_label(output_dir_label);
    
    // Creates the output data directories
    dataio_create_output_dir(output_dir_label, output_dir_name);
    
    // Sets the packet variables: size and overlap
    dataio_set_event_packet_vars(&packet_size, &packet_overlap);
    
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
                
                
                process_event_data(sample_events, packet_size, packet_overlap, packets_req, last_packet_size, c,
                                   EventPacketX, EventPacketY, EventPacketP, EventPacketT);
        
                
                
                fclose(Sample_Input_File);
                
            } // close if
        
        } // close while
        
        
    } // close for
    
    
    // once ready and tested will duplicate all again for training data
    
    //5589
    
    
    return 0;
}



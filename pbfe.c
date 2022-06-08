// pbfe.c - packet binary feature extractor

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
#include "pbfe.h"



// VARIABLES 
int output_binary_literals[B_FEATURES];
int binary_features_count[B_FEATURES];
int patch_o_px[B_FEATURES];
int patch_o_py[B_FEATURES];
int patch_o_nx[B_FEATURES];
int patch_o_ny[B_FEATURES];
int patch_m_px[B_FEATURES];
int patch_m_py[B_FEATURES];
int patch_m_nx[B_FEATURES];
int patch_m_ny[B_FEATURES];
int pbfe_final_output[B_FEATURES];



void pbfe_zero_binary_variables(int output_binary_literals[], int binary_features_count[])
{
    //Zero them first
    for(int b = 0; b < B_FEATURES; b++)
    {
        output_binary_literals[b] = 0;
        binary_features_count[b] = 0;
        
       
    }
    
}

void pbfe_zero_patch_variables(int patch_o_px[],int patch_o_py[], int patch_o_nx[], int patch_o_ny[],
                                   int patch_m_px[],int patch_m_py[], int patch_m_nx[], int patch_m_ny[])
{
    //Zero them first
    for(int b = 0; b < B_FEATURES; b++)
    {
       
        patch_o_px[b] = 0;
        patch_o_py[b] = 0;
        patch_o_nx[b] = 0;
        patch_o_ny[b] = 0;
        
        patch_m_px[b] = 0;
        patch_m_py[b] = 0;
        patch_m_nx[b] = 0;
        patch_m_ny[b] = 0;
    }
    
}
                                   

void pbfe_binary_patch_variables(int patch_o_px[], int patch_o_py[], int patch_o_nx[], int patch_o_ny[],
                                     int patch_m_px[],int patch_m_py[], int patch_m_nx[], int patch_m_ny[])
{

    // calculate patch origin and max coords
    for(int b = 0; b < B_FEATURES; b++)
    {
        //Positive Patch - origin coords
        patch_o_px[b] = ( rand() % (PATCH_X_MAX - PATCH_X_MIN + 1) ) + PATCH_X_MIN;
        patch_o_py[b] = ( rand() % (PATCH_Y_MAX - PATCH_Y_MIN + 1) ) + PATCH_Y_MIN;
        
        // Negative Patch - origin coords
        patch_o_nx[b] = ( rand() % (PATCH_X_MAX - PATCH_X_MIN + 1) ) + PATCH_X_MIN;
        patch_o_ny[b] = ( rand() % (PATCH_Y_MAX - PATCH_Y_MIN + 1) ) + PATCH_Y_MIN;
        
    }
    
    for(int b = 0; b < B_FEATURES; b++)
    {
        // Positive Patch - max coords
        patch_m_px[b] = patch_o_px[b] + PATCH_D;
        patch_m_py[b] = patch_o_py[b] + PATCH_D;
        
        // Negative Patch - max coords
        patch_m_nx[b] = patch_o_px[b] + PATCH_D;
        patch_m_ny[b] = patch_o_py[b] + PATCH_D;

    }
    
}

void pbfe_positive_binary_patch(int binary_features_count[],
                                    long int EventPacketX[], long int EventPacketY[],
                                    int patch_o_px[], int patch_o_py[], int patch_m_px[], int patch_m_py[])
{
    
    
    long int x = *EventPacketX;
    long int y = *EventPacketY;
    
    // Check Positive Patches
    for(int p = 0; p < B_FEATURES; p++)
    {

        for(int k = patch_o_px[p]; k < patch_m_px[p]; k++) // for each patch x coord
        {
        
            for(int l = patch_o_py[p]; l < patch_m_py[p]; l++) // for each patch y coord
            {
                
               if( (x == k) && (y == l) )
               {
                   
                   binary_features_count[p]++;
                   
               }
                
            } // end of patch y coords

        } // end of patch x coords
        
    }// End check positive patch
    
    
    
    
    
}

void pbfe_negative_binary_patch(int binary_features_count[],
                                    long int EventPacketX[], long int EventPacketY[],
                                    int patch_o_nx[], int patch_o_ny[], int patch_m_nx[], int patch_m_ny[])
{
    
    long int x = *EventPacketX;
    long int y = *EventPacketY;
    
    
    // Check Negative Patches
    for(int n = 0; n < B_FEATURES; n++)
    {
        
        for(int i = patch_o_nx[n]; i < patch_m_nx[n]; i++) // for each patch x coord
        {
        
            for(int j = patch_o_ny[n]; j < patch_m_ny[n]; j++) // for each patch y coord
            {
                
               if( (x == i) && (y == j) )
               {
                   
                   binary_features_count[n]--;

               }
              
            } // end of patch y coords

            
        } // end of patch x coords
        
        
    }// End check negative patch

}


void pbfe_binary_patches_output(int output_binary_literals[], int binary_features_count[], int f_packet_size,
                                    long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[])
{

    for(int e = 0; e < f_packet_size; e++) //for every event in the packet
    {
        for(int i = 0; i < MAXFRAME_X; i++) //for each packet event x coord
        {
            for(int j = 0; j < MAXFRAME_Y; j++) //for each pachet event y coord
            {
                
                if( (EventPacketX[e] == i) &&  ( EventPacketY[e] == j) ) // check if there's an event at packet coords x y
                {
                   
                    pbfe_positive_binary_patch(binary_features_count, EventPacketX, EventPacketY, patch_o_px, patch_m_px, patch_o_py, patch_m_py);
                    
                    pbfe_negative_binary_patch(binary_features_count, EventPacketX, EventPacketY, patch_o_nx, patch_m_nx, patch_o_ny, patch_m_ny);
                    
                    
                } //end if event is in patch
             
            } // end of packet event y coords
            
        } // end of packet event x coords
        
    } // end of packet events
        
    
    for ( int b = 0; b < B_FEATURES; b++)
    {
        
     if( binary_features_count[b] >= 1)
     {
         
         output_binary_literals[b] = 1;
        
     } else
     {
         
         
         output_binary_literals[b] = 0;
         
         
     }
        
        
        
    }
    
}


void pbfe_print_to_terminal(int output_binary_literals[], int packet_no)
{
    
    
    
    for(int i = 0; i < B_FEATURES; i++)
    {
        
        if (i == 0)
        {
            
            //Print to Terminal / Debug
            printf("PN %d\t", packet_no);
            
            
        }
        
        printf("%d", output_binary_literals[i]);

        
    }
    printf("\n");
    
    
}





void pbfe_output_packet_literals_min0(int output_binary_literals[], int pbfe_output_packet_literals[packets_req][B_FEATURES], int *packets_min0_count)
{
    
    // Process - Check literals for zeros and ones
    int countzeros = 0;
    int countones = 0;
    
    for(int i = 0; i < B_FEATURES; i++)
    {
        if( output_binary_literals[i] == 0)
        {
            countzeros++;
        }
        
        if( output_binary_literals[i] == 1)
        {
            countones++;
        }
    }
    
   
    // packets with zero literals are rejected
    if( countzeros != B_FEATURES)
    {
        for(int i = 0; i < B_FEATURES; i++)
        {
            pbfe_output_packet_literals[*packets_min0_count][i] = output_binary_literals[i];
        }
        *packets_min0_count = *packets_min0_count + 1;
    }
    
    

    
    
    
}

void pbfe_correct_zero_packet_literals(int output_binary_literals[], int pbfe_output_packet_literals[packets_req][B_FEATURES], int *packets_min0_count)
{
    
    if(*packets_min0_count == 0)
    {
        
        
        for(int i = 0; i < B_FEATURES; i++)
        {
            pbfe_output_packet_literals[0][i] = output_binary_literals[i];
        }
        
        *packets_min0_count = 1;
    }
    
    
    
    
    
}



void pbfe_output_packet_literals_min1(int pbfe_final_output[], int pbfe_output_packet_literals[packets_req][B_FEATURES], int *packets_min0_count)
{
    
    int min0_literals_counters[*packets_min0_count];
    
    
    
    
    
    for(int i = 0; i < *packets_min0_count; i++) // count through the number of packets from min0
    {
        int count_literals = 0;
        
        for(int j = 0; j< B_FEATURES; j++)
        {
            
            if( pbfe_output_packet_literals[i][j] == 1)
            {
                
                count_literals++;
                
                
            }
            
            
            
            
        }
        
        min0_literals_counters[i] = count_literals++;
        
        
    }
    
    //check which packet literals counter is higher and print the packet with those literals

    int check_counter = 0;
    int hold_counter = 0;
    int packet_number = 0;
    
    for(int i = 0; i < *packets_min0_count; i++)
    {
          check_counter = min0_literals_counters[i];
          if (check_counter > hold_counter)
          {
              hold_counter = check_counter;
              packet_number = i;
          }
        
    }

    
    
    // write the sample with the most literals to the output array
    
    for(int i = 0; i < B_FEATURES; i++)
    {
        
        pbfe_final_output[i] = pbfe_output_packet_literals[packet_number][i];
        
        
    }
    
    
}




void pbfe_print_to_file_pbfe_min_literals(FILE *Processed_Data_Output_File, int pbfe_final_output[])
{

    char buf[2] = "";
    char *space = " ";
    char line[(2 * B_FEATURES) + 1];
    
    memset(line,0,sizeof(line));

    for(int a = 0; a < B_FEATURES; a++)
    {
        
        sprintf(buf, "%d", pbfe_final_output[a]);
        strcat(line,buf);
        memset(buf,0,sizeof(buf));
        
        
        if( a < (B_FEATURES - 1) )
        {
        strcat(line,space);
        }
 
    }

    fprintf(Processed_Data_Output_File, "%s\n", line);
    memset(line,0,sizeof(line));


}


void pbfe_print_to_file_pbfe_literals(FILE *Processed_Data_Output_File, int output_binary_literals[])
{

    char buf[2] = "";
    char *space = " ";
    char line[(2 * B_FEATURES) + 1];

    memset(line,0,sizeof(line));
    
    for(int a = 0; a < B_FEATURES; a++)
    {

        sprintf(buf, "%d", output_binary_literals[a]);
        strcat(line,buf);
        memset(buf,0,sizeof(buf));
        
        
        if( a < (B_FEATURES - 1) )
        {
        strcat(line,space);
        }
        
    }

    fprintf(Processed_Data_Output_File, "%s\n", line);
    memset(line,0,sizeof(line));


}


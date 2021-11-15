/*
	
	Project for Systems Arquitecture wc_base.c

      Used to define functions that were declared in 
    wc_base.h. This file executes all the the base 
    functionalities of the Wifi_collector program.
 
	Álvaro Vos Graciá 100454754
	Ana Foncubierta Criado 100429398

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include of the header itself
#include "../inc/wc_base.h"

/* 
     Function to exit the program, the user is asked if he want to exit.
    If the answer is not recognized, the program goes back to the menu.
*/
void wc_quit()
{

    printf("Are you sure you want to exit? [y/N]: ");
    char selection = getchar();

    /*
		Checking what did the user introduced, if 'y' or 'Y' was introduced the program will end
		execution, but if any other thing was introduced the program will continue
	*/
    switch(selection)
    {
        case 'y':
        case 'Y':
            printf("\nGoodbye!\n");
            exit(0);
            break;
        case 'n':
        case 'N':
            break;
        default:
            printf("\nUnrecognized option, please try again later.\n");
            break;
    }
}


/*
     Function that reads a cell
*/
void get_cell(net *net_ptr, FILE * f)
{
    fscanf(f, input_format, net_ptr->cell, net_ptr->address, net_ptr->essid, net_ptr->mode,
           net_ptr->channel, net_ptr->key, net_ptr->quality, net_ptr->frequency, net_ptr->signal_lvl);
}

/*
     Function that prints a net
*/
void print_net(net net_node)
{
    printf("Cell %d: %s %s %s %d %s %d/%d %.3f %d \n", *net_node.cell, net_node.address, net_node.essid,
            net_node.mode, *net_node.channel, net_node.key, *net_node.quality, *net_node.edge_quality, 
            *net_node.frequency, *net_node.signal_lvl);
}

/*
     Function that collects the network information of an info_cell file selected by the user.
*/
bool wc_collect(dym_arr **net_list, int *current_pos, char num[])
{
    char file[MAX_STRING_LENGHT];
    strcat(strcpy(file, input_dir), file_name_format);
    strcat(file, num);
    strcat(file,".txt");

    FILE * f = fopen(file, "r");

    /*
         If the file is not empty, it reads all the cells in the info_cell file with get_cell(), 
        until there are no more cells to read and then closes the file.
    */
    if(f != NULL)
    {
        while(!feof(f))
        {
            if((*current_pos) % 5 == 0 && (*current_pos) != 0)
            {
                printf("\nRunning out of allocated memory for the data storage. Proceding to fix the isssue...\n");
                add_x_positions(5, net_list);
            }

            get_cell(&(*(*net_list)).array[*current_pos], f);
            printf("\nData read from %s (added to position %d of the database)\n", file, *current_pos);
            print_net((*net_list)->array[*current_pos]);
            (*current_pos)++;
        }

        fclose(f);
        return True;
    } 
    else
    {
        printf("\nUnrecognized option, please try again.\n");
        return False;
    }
}

/*
      Fuction that prints the information of an info_cell file if the cells 
     had already been stored (using wc_collect() in the application).
*/

bool wc_display(dym_arr *net_list, char num[])
{
    int num_int = atoi(num);
    bool is_null = True;

    for(int i = 0; i < net_list->used_positions; i++)
    {
        if(*(net_list->array[i].cell) == num_int)     
        {
            print_net(net_list->array[i]);
            is_null = False;
        }
    }

    if(is_null)
    {
        printf("Not recognised\n");
        return False;
    }
    
    return True;
}
   
/*
     Prints the information of all the cells stored in the application
*/
void wc_display_all(dym_arr *net_list, int current_pos)
{
    for(int i=0;i<current_pos;i++)
    {  
        //Checks if the cells are empty, and if so it breaks the loop.
        if(*(net_list->array[i].cell) == 0) break;
        print_net(net_list->array[i]);
        
    }
}

/*
     Deletes a net if the ESSID of that net is stored in the application, if not the program 
     let the user know that the ESSID has not been found.
*/
bool wc_delete_net(char* essid_name,dym_arr *net_list, int *current_pos)
{
    int counter=0;
    //Loop to find if the ESSID is stored, if so the loops finishes
    for(int i = 0; i < net_list->used_positions; i++)
    {
        if(strcmp(net_list->array[i].essid,essid_name) == 0)
        {
            printf("Found ESSID %s at position %d, proceding to delete it\n", essid_name, i);
            delete_pos(i,net_list, current_pos);
            counter--;

            // Uncomment if desired behaviour of delete net is to delete just the first seen net
            //break;
        }
        else counter++;
    
    }

    // Return True if the net was successfully deleted or False if something went wrong
    if(counter==net_list->used_positions)
    {
        printf("\nThe ESSID couldn't be found, please try again later.\n");
        return False;
    }
    else return True;
}

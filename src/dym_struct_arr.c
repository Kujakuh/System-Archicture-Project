/*
	
	Project for Systems Arquitecture dym_struct_arr.c
	
     This file initialize the dynamic array and allocates its memory. Also implements the 
    functions used to interactuate with the dynamic array.

	Álvaro Vos Graciá 100454754
	Ana Foncubierta Criado 100429398

*/

#include <stdio.h>
#include <stdlib.h>

#include "../inc/dym_struct_arr.h"

/*
    Allocates the memory of the net and its variables
*/
struct net_data* net_init()
{
    struct net_data *retr_net = (net*)malloc(SIZE_STRUCT(net));

    retr_net->cell = (int*)malloc(sizeof(int));
    retr_net->address = (char*)malloc(MAX_STRING_LENGHT + 1);
    retr_net->essid = (char*)malloc(MAX_STRING_LENGHT + 1);
    retr_net->mode = (char*)malloc(MAX_STRING_LENGHT + 1);
    retr_net->channel = (int*)malloc(sizeof(int));
    retr_net->key = (char*)malloc(MAX_STRING_LENGHT + 1);
    retr_net->edge_quality = (int*)malloc(sizeof(int));
    retr_net->quality = (int*)malloc(sizeof(int));
    retr_net->frequency = (float*)malloc(sizeof(float));
    retr_net->signal_lvl = (int*)malloc(sizeof(int));

    return retr_net;
}

/*
     Function that inicialitates the array
 */
void init_arr(dym_arr *arr, size_t init_size)
{
    // Initial size times the size of the data
    arr->array = (net*)malloc(init_size * SIZE_STRUCT(net));

    // Allocate corresponding memory to each position of the array
    for(int i=0;i<init_size;i++)
    {
        net a = *net_init();
        arr->array[i] = a;
    }
    arr->used_positions = init_size - 1;
}
/*
    Function that increases in num_add_pos new elements each time that you do not have enough memory
*/
void add_x_positions(int num_add_pos, dym_arr **arr)
{
    (*arr)->array = (net*)realloc((*arr)->array, (num_add_pos + (*arr)->used_positions + 1) * SIZE_STRUCT(net));
    int pos = (*arr)->used_positions;

    for(int i = pos; i < pos + num_add_pos; i++)
    {
        net *a = net_init();
        (*arr)->used_positions++;
        (*arr)->array[(*arr)->used_positions] = *a;
    }
}
/*
    This function recibes a position to be deleted, after that the next net occupies that position 
    (so that there are no free positions)
*/
void delete_pos(int pos_to_delt, dym_arr *arr, int *current_pos)
{
    dym_arr *tmp = arr;
    for(int i = pos_to_delt; i < arr->used_positions; i++)
    {
        if(i == arr->used_positions)
        {
            arr->array[arr->used_positions] = *net_init();
        }
        else
        {
            arr->array[i] = tmp->array[i+1];
        }
    }
    
    arr->array[arr->used_positions] = *net_init();
    arr->used_positions--;
    (*current_pos)--;
}

/*
    Frees the whole array
*/
void free_array(dym_arr **arr)
{
    for(int i = 0; i < (*arr)->used_positions; i++)
    {
        free((*arr)->array[i].cell);
        free((*arr)->array[i].address);
        free((*arr)->array[i].essid);
        free((*arr)->array[i].mode);
        free((*arr)->array[i].channel);
        free((*arr)->array[i].key);
        free((*arr)->array[i].edge_quality);
        free((*arr)->array[i].quality);
        free((*arr)->array[i].frequency);
        free((*arr)->array[i].signal_lvl);
    }

    (*arr)->array = NULL;
    free((*arr)->array);
    (*arr)->used_positions = 0;
}

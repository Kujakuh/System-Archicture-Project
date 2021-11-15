/*
	
	Project for Systems Arquitecture dym_struct_arr.h

     This header file is the one who describes the format of a dynamic array 
    and the net. Also describes the functions used to interactuate with the
    dynamic array.
	 
	Álvaro Vos Graciá 100454754
	Ana Foncubierta Criado 100429398

*/

#include <stddef.h>

//Avoiding multiple definitions
#ifndef DYM_STRUC_ARR_SEEN
#define DYM_STRUC_ARR_SEEN

//Calculate size of structure
#define SIZE_STRUCT(x) sizeof(x)

#define MAX_STRING_LENGHT 80

//Format of the net
typedef struct net_data
{
    int *cell;
    char *address;
    char *essid;
    char *mode;
    int *channel;
    char *key;
    int *edge_quality;
    int *quality;
    float *frequency;
    int *signal_lvl;
    
} net;

// Definition of the dynamic array
typedef struct
{
    net *array;
    size_t used_positions;

} dym_arr;

//Declaration of the functions used to interactuate with the dynamic array
struct net_data* net_init();
void init_arr(dym_arr *arr, size_t init_size);
void add_x_positions(int num_add_pos, dym_arr **arr);
void delete_pos(int pos_to_delt, dym_arr *arr, int *current_pos);
void free_array(dym_arr **arr);

#endif /*DYM_STRUC_ARR_SEEN*/

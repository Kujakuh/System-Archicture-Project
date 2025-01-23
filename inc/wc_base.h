/*

    Project for Systems Arquitecture wc_base.h
 
     Header file used to declare all the functions that are used to modify the dynamic array
    of the Wifi_collector program.

    Álvaro Vos Graciá 100454754
	Ana Foncubierta Criado 100429398

 */

//Avoiding multiple definitions
#ifndef WC_BASE_SEEN
#define WC_BASE_SEEN

// Include of the dynamic struct array type
#include "../inc/dym_struct_arr.h"

//Stablishing constants
static const char input_dir[] = "./cells/";
static const char file_name_format[] = "info_cell_";
static const char input_format[] = "%*s %d %*s %s %*[^:]: %s %*[^:]: %s %*[^:]: %d %*s %*[^:]: %s %*[^=]= %d %*[^0]0 "
                                    "%*[^:]: %f %*s %*s %*[^=]= %d %*s ";

//Creation of booleans
typedef enum
{
    False = 0,
    True = 1,
}bool;

//Functions declarations
void wc_quit();
bool wc_collect(dym_arr **net_list, int *current_pos, char num[]);
/*
    Functions not yet implemented
    void wc_one_net_data();  
    void wc_get_best();    
    void wc_sort();  
    void wc_export();  
    void wc_import(); 
*/
bool wc_delete_net(char* essid_name, dym_arr *net_list, int *current_pos);
bool wc_display(dym_arr *net_list, char num[]);
void wc_display_all(dym_arr *net_list, int current_pos);

#endif /* WC_BASE_SEEN */

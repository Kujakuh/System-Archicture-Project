/*
	
	Project for Systems Arquitecture main.c

	 
	 This file contains the main function of the program, which is the function that is first executed,
	the main function manages the main menu and asks the option to be selected, then it calls the
	correspondant function of the wc_base file.

	Álvaro Vos Graciá 100454754
	Ana Foncubierta Criado 100429398

*/

#include <stdio.h>
#include <stdlib.h>

//Including programmes that needs variables declared above
#include "../inc/wc_base.h"

/*
	Clears the input buffer and checks if the used entered exit&, if so it returns true
*/
bool clearBuffer(){

	//Reading the buffer until a /n is read
	char last_char = getchar();
	bool exit = False;
	while (last_char != '\n'){
		if(last_char == '&') exit = True;
		last_char = getchar();
	}
	return exit;
}

/* 
	Main function
*/
int main()
{
	bool bool_check = True;
    int option;
	int current = 0;
	int bufsize = 8; char buffer[bufsize];
	char* aux;
	char cell_num[4];
	char essid_name[10];
	char repeat_check;

	//Creating the dynamic array and initialising it to size 5
	dym_arr net_data, *net_list;
	net_list = &net_data;
	init_arr(net_list, 5);

	do{
		
		/*Printing the main menu and reading the terminal as character, but converting it to
		an integer to be able to work with it*/
		
		printf(
		"\n[2021] SUCEM S.L. Wifi Collector \n [1] wificollector_quit"
		"\n [2] wificollector_collect\n [3] wificollector_show_data_one_network"
		"\n [4] wificollector_select_best\n [5] wificollector_delete_net \n [6] "
		"wificollector_sort\n [7] wificollector_export\n [8] wificollector_import\n [9] wificollector_display"
		"\n [10] wificollector_display_all\n\nOption: ");

		aux = fgets(buffer, bufsize, stdin);
		option = atoi(aux);

		switch(option){

			//Option wificollector_quit was selected
			case 1:
				wc_quit();
				clearBuffer();
				break;

			//Option wificollector_collect was selected
			case 2:
				/*
					 Loop that makes sure if the user wants to add more cells, the loops ends
					if the user types 'n' or 'N'
				*/

				do
				{
					printf("\nWhat cell do you want to collect: ");
					scanf("%s", cell_num);
					clearBuffer();
					wc_collect(&net_list, &current, cell_num);
					
					do
					{
						printf("\nDo you want to add another cell? [y/N]: ");
						repeat_check = getchar();
						clearBuffer();

						switch(repeat_check)
						{
							case 'y':
							case 'Y':
								bool_check = True;
								break;
							case 'n':
							case 'N':
								bool_check = False;
								break;
							default:
								printf("\nNot recognised");
								
						}
					}
					while(repeat_check != 'y' && repeat_check != 'Y' &&
						  repeat_check != 'n' && repeat_check != 'N');
				}
				while(bool_check);
				printf("\nPress enter to go back to the menu.\n");
				clearBuffer();

				break;

			//Option wificollector_show_data_one_network was selected
			case 3:
				printf("\nOption not yet implemented\n");
				break;

			//Option wificollector_select_best was selected
			case 4:
				printf("\nOption not yet implemented\n");
				break;

			//Option wificollector_delete_net was selected
			case 5:
				/*
					  Asks the user the ESSID, he wants to eliminate.
				*/
				printf("\nIndicate the ESSID (use \"\"): ");
				scanf("%s",essid_name);

				// Return True if the net was successfully deleted
				wc_delete_net(essid_name, net_list, &current);

				getchar();
				clearBuffer();
				break;

			//Option wificollector_sort was selected
			case 6:
				printf("\nOption not yet implemented\n");
				break;

			//Option wificollector_export was selected
			case 7:
				printf("\nOption not yet implemented\n");
				break;

			//Option wificollector_import was selected
			case 8:
				printf("\nOption not yet implemented\n");
				break;
			
			//Option wificollector_display was selected
			case 9:
				/*
					  Prints the information of the info_cell file selected if it has already been stored, 
					 the loop exits in case the user wants to print more cells, it ends if 
					 the user types 'n' or 'N'
				*/
				do
				{
					printf("Indicate the number of the cell for which you want to "
					"know its information (1 - 21): ");
					scanf("%s",cell_num);
					wc_display(net_list,cell_num);
					clearBuffer();
					
					do
					{
						printf("Do you want to print the information of another cell? [y|N]:");
						repeat_check = getchar();
						clearBuffer();

						switch(repeat_check)
						{
							case 'y':
							case 'Y':
								bool_check = True;
								break;
							case 'n':
							case 'N':
								bool_check = False;
								break;
							default:
								printf("\nNot recognised\n");
								
						}
					}
					while(repeat_check != 'y' && repeat_check != 'Y' &&
								repeat_check != 'n' &&repeat_check != 'N');				
				}
				while (bool_check);
				printf("\nPress enter to go back to the menu.\n");
				clearBuffer();
			
				break;

			//Option wificollector_display_all was selected
			case 10:
				/*
					  Prints the whole information of the cells already stored.
				*/
            	wc_display_all(net_list, current);
				printf("\nPress enter to go back to the menu.\n");
				getchar();
				break;

			//Option not defined was selected
			default:
				if (aux != NULL) printf("\nYou have to select an option between 1 and 10\n");
				getchar();
		}

	} 
	while(aux != NULL); 
    return 0;
}

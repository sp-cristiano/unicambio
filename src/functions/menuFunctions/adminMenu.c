/*
******************************************************************************
This file contains all the admin menu functions for the unicambio project.
[Este arquivo contém todas as funções do menu do administrador para o projeto unicambio.]
******************************************************************************
*/

/*
******************************************************************************
Including internal header files.
[Incluindo arquivos de cabeçalho internos.]
******************************************************************************
*/
#include "../include/config.h"
#include "../include/messages.h"
#include "../include/structures.h"
#include "../include/globals.h"
#include "../include/adminMenu.h"

/*
******************************************************************************
this will display the admin menu
[Esta função exibirá o menu do administrador]
******************************************************************************
*/

/*
******************************************************************************
This function will start the session.
[Esta função iniciará a sessão.]
******************************************************************************
*/
void startSessionMenu(SystemData *sysData)
{
	exitFlag = FALSE;
	int choice;
	do
	{
		displayBanner();
		printf("                 %s\n", UI_WELCOME);
		printf("                   %s\n", UI_START_SESSION_MENU_OPT_1);
		printf("\t1. Start Session [Iniciar Sessão]\n\n");
		printf("\t0. Exit [Sair]\n\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:
			exitProgram(sysData); // Exit the program [Encerrar o programa]
			break;
		case 1:
			loginPage(sysData); // Login page [Página de login]
			break;
		default:
			printf("          %s\n", UI_ERROR_INVALID_INPUT);
			sleep(MID_SLEEP);
			break;
		}
	} while ((choice < 0 || choice > 1) && exitFlag == FALSE && !is_authenticated);
}

void adminMenu(SystemData *sysData)
{
	if (sysData == NULL)
	{
		printf("%s\n", UI_ERROR_DATA_NOT_FOUND);
		sleep(MIN_SLEEP);
		return; // If the system data is not initialized, exit the function [Se os dados do sistema não estiverem inicializados, saia da função]
	}

	int choice;
	do
	{
		displayBanner();
		printf("                 %s\n", UI_ADMIN_MENU);
		printf("\t %s\n", UI_ADMIN_MENU_OPT_1);
		printf("\t %s\n", UI_ADMIN_MENU_OPT_2);
		printf("\t %s\n", UI_ADMIN_MENU_OPT_3);
		printf("\t %s\n", UI_ADMIN_MENU_OPT_4);
		printf("\t %s\n", UI_ADMIN_MENU_OPT_5);
		printf("\t %s\n", UI_LOGOUT);

		printf("%s: ", UI_PROMPT);
		scanf("%d", &choice);

		switch (choice)
		{
		case 0:
			displayBanner();
			terminateSession(sysData); // Function to terminate the session
			startSessionMenu(sysData);
			break;
		case 1:
			manageUsersMenu(sysData); // Function to manage users
			break;
		case 2:
			manageRolesMenu(sysData); // Function to manage roles
			break;
		case 3:
			manageCurrenciesMenu(sysData); // Function to manage currencies
			break;
		case 4:
			manageExchangeRatesMenu(sysData); // Function to manage exchange rates
			break;
		case 5:
			manageTransactionsMenu(sysData); // Function to manage transactions
			break;
		default:
			printf("          %s\n", UI_ERROR_INVALID_INPUT);
			sleep(MID_SLEEP);
			break;
		}
	} while (choice != 0 && exitFlag == FALSE && !is_authenticated);
}
/**
 * @file adminMenu.c
 * @author Chinedum Odili
 * @brief This file contains the admin menu and the start session menu
 * [Este arquivo contém o menu do administrador e o menu de inicio de sessão]
 * @param sysData Pointer to the system data structure containing user, role, currency, exchange rate, and transaction information.
 */
/*
==================================================================================================================
																			File inclusion directives for internal header files
																			[Diretivas de inclusão de arquivos de cabeçalho internos]
==================================================================================================================
*/

#include "../include/config.h"
#include "../include/messages.h"
#include "../include/structures.h"
#include "../include/globals.h"
#include "../include/adminMenu.h"
#include "../include/userMenu.h"				 // TODO: Will create the user menu
#include "../include/currencyMenu.h"		 // TODO: will create the currency menu
#include "../include/roleMenu.h"				 // TODO: will create the role menu
#include "../include/exchangeRateMenu.h" // TODO: will create the exchange rate menu
#include "../include/transactionMenu.h"	 // TODO: will create the transaction menu
#include "../include/utilities.h"
#include "../include/oauthFunctions.h"

/*
==================================================================================================================
																			This function will start the main menu session
																			[Esta função iniciara a sessão do menu principal]
==================================================================================================================
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

/*
==================================================================================================================
																			This function will be shown once the admin is authenticated.
																			[Esta função será mostrada uma vez que o admin estiver autenticado.]
==================================================================================================================
*/
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
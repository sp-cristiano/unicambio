#include "../include/oauth.h"
#include "../include/unicambio.h"
#include "../include/structures.h"
#include "../include/messages.h"
#include "../include/utilities.h"
#include "../include/homePageMenu.h"

/*
==================================================================================================================
																			This function will start the main menu session
																			[Esta função iniciara a sessão do menu principal]
==================================================================================================================
*/
void homePageMenu(SystemData *sysData)
{
	sysData->appContext->exitFlag = false;
	int choice;
	do
	{
		displayBanner();
		centerStringOnly(UI_LABEL_WELCOME);
		printf("\n");
		centerStringOnly(UI_HOME_PAGE);
		printf("\n");
		centerStringOnly(UI_START_SESSION_MENU_OPT_1);
		centerStringOnly(UI_START_SESSION_MENU_OPT_1_PT);
		printf("\n");
		printf("\n");

		// printf("                 %s\n\n", UI_LABEL_WELCOME);
		// printf("                 %s\n\n", UI_HOME_PAGE);
		// printf("                   %s\n", UI_START_SESSION_MENU_OPT_1);
		printf("\t1. Start Session [Iniciar Sessão]\n\n");
		printf("\t0. Exit [Sair]\n\n");

		printf("display user data\n");
		for(size_t i = 0; i < sysData->userCount; i++){
			printf("\t%s %s\n", sysData->users[i].name, sysData->users[i].email);
		}
		printf("Printing currency data\n");
		for(size_t i = 0; i < sysData->currencyCount; i++){
			printf("\t%s %lf\n", sysData->currencies[i].name, sysData->currencies[i].rateToOneKz);
		}
		printf("Printing exchange data\n");
		for(size_t i = 0; i < sysData->exchangeRateCount; i++){
			printf("\t%d %lf\n", sysData->exchangeRates[i].exchangeRateID, sysData->exchangeRates[i].toCurrencyAmountConvertedTo);
		}
		printf("Printing Transaction data\n");
		for(size_t i = 0; i < sysData->transactionCount; i++){
			printf("\t%d %lf\n", sysData->transactions[i].transactionID, sysData->transactions[i].toCurrencyAmount);
		}
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:
			exitProgram(sysData); // Exit the program [Encerrar o programa]
			break;
		case 1:
			loginPageMenu(sysData); // Login page [Página de login]
			break;
		default:
			printf("          %s\n", UI_ERROR_INVALID_INPUT);
			sleep(MID_SLEEP);
			break;
		}
	} while ((choice < 0 || choice > 1) && sysData->appContext->exitFlag == false && sysData->appContext->isAuthenticated == false);
}

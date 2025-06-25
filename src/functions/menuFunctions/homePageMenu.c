#include "../include/structures.h"
#include "../include/userFunction.h"
#include "../include/enum.h"
#include "../include/homePageMenu.h"
#include "../include/utilities.h"
#include "../include/logger.h"

void homePageMenu(SystemData *sysData)
{

	sysData->appContext->exitFlag = false;
	int choice;
	do
	{
		displayBanner();
		centerStrings("Welcome to UniCambio [Bem vindo ao UniCambio]");
		printf("\n");
		centerStrings("HOME PAGE [PÁGINA INICIAL]");
		printf("\n");
		centerStrings("Type 1 to start a session or 0 to exit this application.");
		centerStrings(" [Digite 1 para iniciar uma sessão ou 0 para sair desta aplicação.]");
		centerStrings("1 - Login [Entrar]");
		centerStrings("0 - Exit [Sair]");
		printf("\n");
		printf("Enter your choice [Digite sua opção]: ");
		scanf("%d", &choice);
		printf("\n");
		switch (choice)
		{
		case 0:
			exitProgram(sysData);
			break;
		case 1:
			// loginMenu(sysData);
			break;

		default:
			logPrintMessage(LOG_ERROR, "Invalid choice [Opção inválida]", yes);
			break;
		}

	} while ((choice < 0 || choice > 1) && sysData->appContext->exitFlag == false && sysData->appContext->isAuthenticated == false);
}

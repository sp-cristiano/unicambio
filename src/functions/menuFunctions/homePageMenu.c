#include "../include/structures.h"
#include "../include/userFunction.h"
#include "../include/enum.h"
#include "../include/homePageMenu.h"
#include "../include/utilities.h"
#include "../include/logger.h"
#include "../include/auth.h"
#include "../include/grantAdminAccessMenu.h"
#include "../include/grantLimitedAccessMenu.h"
#include "../include/grantUserAccessMenu.h"

void homePageMenu(SystemData *sysData)
{
	if (!sysData)
	{
		printf("\n\n");
		logPrintMessage(LOG_ERROR, "Failed to access system data [ Falha ao acessar os dados do sistema ]", yes);
		return;
	}
	if (!sysData->appContext)
	{
		printf("\n\n");
		logPrintMessage(LOG_ERROR, "Failed to access app context [ Falha ao acessar o contexto da aplicação ]", yes);
		return;
	}

	if (sysData->userCount == 0)
	{
		printf("\n\n");
		logPrintMessage(LOG_ERROR, "No user in the system. Please create a default admin user by filling the .env file", yes);
		logPrintMessage(LOG_ERROR, "[ Nenhuma pessoa cadastrada no sistema. Por favor, crie um usuário admin padrão preenchendo o arquivo .env ]", yes);
		return;
	}
	// Default Reset of appContext.
	if (sysData->appContext->isAuthenticated == true)
	{
		sysData->appContext->session = true;
		sysData->appContext->exitFlag = false;
	}
	else
	{
		sysData->appContext->session = false;
		sysData->appContext->isAuthenticated = false;
		sysData->appContext->currentUserRoleID = 0;
		sysData->appContext->currentUserID = 0;
		sysData->appContext->exitFlag = false;
		sysData->appContext->currentUserName = NULL;
	}

	if (sysData->appContext->isAuthenticated == false && sysData->appContext->session == false && sysData->appContext->exitFlag == false)
	{

		int choice;
		int result;
		do
		{
			displayBanner(sysData);
			centerStrings("Welcome to UniCambio [Bem vindo ao UniCambio]");
			printf("\n");
			centerStrings("HOME PAGE [PÁGINA INICIAL]");
			printf("\n");
			centerStrings("Type 1 to start a session or 0 to exit this application.");
			centerStrings(" [Digite 1 para iniciar uma sessão ou 0 para sair desta aplicação.]");
			printf("\n\t\t1. - Login [Entrar]\n\n");
			printf("\t\t0. - Exit [Sair]\n\n");
			printf("\n");

			printf("Enter your choice [Digite sua opção]: ");
			result = scanf("%d", &choice);

			clearInputBuffer(); // Remove the invalid input [Remove a entrada inválida]

			if (result != 1 || (choice != 0 && choice != 1))
			{
				printf("\n\n");
				logPrintMessage(LOG_ERROR, "Invalid input [Entrada inválida]", yes);
				continue; // Restart the loop
			}

			switch (choice)
			{
			case 0:
				exitProgram(sysData);
				break;
			case 1:
				loginPageMenu(sysData);
				break;

			default:
				printf("\n\n");
				logPrintMessage(LOG_ERROR, "Invalid choice [Opção inválida]", yes);
				break;
			}

		} while ((choice != 0 || choice != 1) && sysData->appContext->exitFlag == false && sysData->appContext->isAuthenticated == false);
	}

	if (sysData->appContext->isAuthenticated == true)
	{
		if (sysData->appContext->currentUserRoleID == ROLE_USER)
		{
			grantUserAccessMenu(sysData);
		}
		else if (sysData->appContext->currentUserRoleID == ROLE_ADMIN)
		{
			grantAdminAccessMenu(sysData);
		}
		else
		{
			grantLimitedAccessMenu(sysData);
		}
	}
}
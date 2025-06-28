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
		logPrintMessage(LOG_ERROR, "Failed to access system data [ Falha ao acessar os dados do sistema ]", yes);
		return;
	}
	if (!sysData->appContext)
	{
		logPrintMessage(LOG_ERROR, "Failed to access app context [ Falha ao acessar o contexto da aplicação ]", yes);
		return;
	}

	int exitFlag = sysData->appContext->exitFlag, isAuthenticated = sysData->appContext->isAuthenticated, session = sysData->appContext->session;

	if (sysData->userCount == 0)
	{
		logPrintMessage(LOG_ERROR, "No user in the system. Please create a default admin user by filling the .env file", yes);
		logPrintMessage(LOG_ERROR, "[ Nenhuma pessoa cadastrada no sistema. Por favor, crie um usuário admin padrão preenchendo o arquivo .env ]", yes);
		return;
	}
	if (isAuthenticated == false && session == false && exitFlag == false)
	{

		// sysData->appContext->exitFlag = false;
		int choice;
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
			scanf("%d", &choice);
			printf("\n");
			switch (choice)
			{
			case 0:
				exitProgram(sysData);
				break;
			case 1:
				loginPageMenu(sysData);
				break;

			default:
				logPrintMessage(LOG_ERROR, "Invalid choice [Opção inválida]", yes);
				clearInputBuffer();
				break;
			}

		} while ((choice < 0 || choice > 1) && sysData->appContext->exitFlag == false && sysData->appContext->isAuthenticated == false);
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
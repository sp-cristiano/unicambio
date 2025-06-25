#include "../include/unicambio.h"
#include "../include/structures.h"
#include "../include/enum.h"
#include "../include/grantAdminAccessMenu.h"
#include "../include/utilities.h"
#include "../include/logger.h"
#include "../include/auth.h"
#include "../include/saveSystemData.h"

StatusInfo grantAdminAccessMenu(SystemData *sysData)
{
	int choice;
	StatusInfo status;
	if (sysData->appContext->session == true && sysData->appContext->isAuthenticated == true && sysData->appContext->currentUserRoleID == ROLE_ADMIN)
	{
		do
		{
			displayBanner();
			centerStrings("ADMIN MENU [MENU DO ADMINISTRADOR]");
			printf("\n");
			centerStrings("Select option from  1 to 4 to navigate this menu. Select 0 to Logout.\n");
			centerStrings("Selecione a opção de 1 a 4 para navegar nesta menu. Selecione 0 para sair.\n");
			printf("\n");
			printf("\n\t\t1. - Perforn User Operations [Realizar operações de usuário]\n\n");
			printf("\t\t2. - Perform Currency Operations [Realizar operações de moeda]\n\n");
			printf("\t\t3. - Perform Exchange Rate Operations [Realizar operações de taxa de caâmbio]\n\n");
			printf("\t\t4. - Perform Transaction Operations [Realizar operações de transação]\n\n");
			printf("\t\t0. - Logout [Sair]\n\n");
			printf("\n");
			printf("Enter your choice [Digite sua opção]: ");
			scanf("%d", &choice);
			printf("\n");

			switch (choice)
			{
			case 0:
				logoutUser(sysData);
				break;
			case 1:
				status = performUserOperationsMenu(sysData);
				break;
			case 2:
				status = performCurrencyOperationsMenu(sysData);
				break;
			case 3:
				status = performExchangeRateOperationsMenu(sysData);
				break;
			case 4:
				status = performTransactionOperationsMenu(sysData);
				break;
			default:
				logPrintMessage(LOG_ERROR, "Invalid input [Entrada inválida]", yes);
				break;
			}
		} while ((choice < 0 || choice > 4) && sysData->appContext->session == true && sysData->appContext->isAuthenticated == true && sysData->appContext->exitFlag == false);
	}
	return status;
}

// TODO; Add user operations
StatusInfo performUserOperationsMenu(SystemData *sysData)
{
	int choice;
	StatusInfo status;
	do
	{

	} while ((choice < 0 || choice > 5) && sysData->appContext->session == true && sysData->appContext->isAuthenticated == true && sysData->appContext->exitFlag == false);
	return status;
}

// TODO: Add currency operations
StatusInfo performCurrencyOperationsMenu(SystemData *sysData)
{
	int choice;
	StatusInfo status;
	do
	{
		displayBanner();
		centerStrings("ADMIN MENU [MENU DO ADMINISTRADOR]");
		printf("\n");
		centerStrings("Select option from  1 to 4 to navigate this menu. Select 0 to go back.\n");
		centerStrings("Selecione a opção de 1 a 4 para navegar nesta menu. Selecione 0 para voltar.\n");
		printf("\n");
		printf("\n\t\t1. - Create User [Criar usuário]n\n");
		printf("\t\t2. - Update User Profile [] [] \n\n");
		printf("\t\t3. - View all users [] \n\n");
		printf("\t\t4. - Search for User  \n\n");
		printf("\t\t5. - Delete User Profile \n\n");
	} while ((choice < 0 || choice > 5) && sysData->appContext->session == true && sysData->appContext->isAuthenticated == true && sysData->appContext->exitFlag == false);
	return status;
}

// TODO: ADD EXCHANGE RATE OPERATIONS
StatusInfo performExchangeRateOperationsMenu(SystemData *sysData)
{
	StatusInfo status;
	return status;
}

// TODO: ADD TRANSACTION OPERATIONS
StatusInfo performTransactionOperationsMenu(SystemData *sysData)
{
	StatusInfo status;
	return status;
}
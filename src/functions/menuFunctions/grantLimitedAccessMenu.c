#include "../include/unicambio.h"
#include "../include/structures.h"
#include "../include/enum.h"
#include "../include/grantLimitedAccessMenu.h"
#include "../include/utilities.h"
#include "../include/logger.h"
#include "../include/auth.h"
#include "../include/saveSystemData.h"
#include "../include/grantUserAccessMenu.h"

StatusInfo grantLimitedAccessMenu(SystemData *sysData)
{
	int choice;
	StatusInfo status;
	if (sysData->appContext->session == true && sysData->appContext->isAuthenticated == true && sysData->appContext->currentUserRoleID != ROLE_USER && sysData->appContext->currentUserRoleID != ROLE_ADMIN)
	{
		do
		{
			displayBanner();
			centerStrings("RESTRICTED USER MENU [MENU DO USUARIO RESTRITO]");
			printf("\n");
			centerStrings("Select option from  1 to 2 to navigate this menu. Select 0 to Logout.\n");
			centerStrings("Selecione a opção de 1 a 2 para navegar nesta menu. Selecione 0 para sair.\n");
			printf("\n");
			printf("\n\t\t1. - View available currencies [Visualizar moedas disponíveis]\n\n");
			printf("\t\t2. - View your transaction History [Visualizar seu histórico de transações]\n\n");
			printf("\t\t0. - Exit [Sair]\n\n");
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
				status = viewAvailableCurrenciesMenu(sysData);
				break;
			case 2:
				status = viewTransactionHistoryMenu(sysData);
				break;
			default:
				logPrintMessage(LOG_ERROR, "Invalid option [Opção inválida]", yes);
				break;
			}
			return status;
		} while ((choice < 0 || choice > 3) && sysData->appContext->session == true && sysData->appContext->isAuthenticated == true && sysData->appContext->currentUserRoleID != ROLE_USER && sysData->appContext->currentUserRoleID != ROLE_ADMIN);
	}
	return status;
}
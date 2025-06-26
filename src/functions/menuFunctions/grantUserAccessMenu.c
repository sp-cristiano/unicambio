#include "../include/unicambio.h"
#include "../include/structures.h"
#include "../include/enum.h"
#include "../include/grantUserAccessMenu.h"
#include "../include/utilities.h"
#include "../include/logger.h"
#include "../include/auth.h"
#include "../include/saveSystemData.h"

StatusInfo grantUserAccessMenu(SystemData *sysData)
{
	int choice;
	StatusInfo status;
	if (sysData->appContext->session == true && sysData->appContext->isAuthenticated == true && sysData->appContext->currentUserRoleID == ROLE_USER)
	{
		do
		{
			displayBanner(sysData);
			centerStrings("USER MENU [MENU DO USUARIO]");
			printf("\n");
			centerStrings("Select option from  1 to 4 to navigate this menu. Select 0 to Logout.\n");
			centerStrings("Selecione a opção de 1 a 4 para navegar nesta menu. Selecione 0 para sair.\n");
			printf("\n");
			printf("\n\t\t1. - View available currencies [Visualizar moedas disponíveis]\n\n");
			printf("\t\t2. - Verify exchange rates [Verificar taxas de caâmbio]\n\n");
			printf("\t\t2. - Create a transaction [Criar uma transação]\n\n");
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
				status = verifyExchangeRatesMenu(sysData);
				break;
			case 3:
				status = createTransactionMenu(sysData);
				break;
			case 4:
				status = viewTransactionHistoryMenu(sysData);
				break;
			default:
				logPrintMessage(LOG_ERROR, "Invalid input [Entrada inválida]", yes);
				break;
			}
		} while ((choice < 0 || choice > 4) && sysData->appContext->session == true && sysData->appContext->isAuthenticated == true && sysData->appContext->exitFlag == false);
		return status;
	}
}
StatusInfo viewAvailableCurrenciesMenu(SystemData *sysData)
{
	StatusInfo status;
	return status;
}
StatusInfo verifyExchangeRatesMenu(SystemData *sysData)
{
	StatusInfo status;
	return status;
}
StatusInfo createTransactionMenu(SystemData *sysData)
{
	StatusInfo status;
	return status;
}
StatusInfo viewTransactionHistoryMenu(SystemData *sysData)
{
	StatusInfo status;
	return status;
}
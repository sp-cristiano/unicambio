#include "../include/unicambio.h"
#include "../include/structures.h"
#include "../include/enum.h"
#include "../include/grantAdminAccessMenu.h"
#include "../include/utilities.h"
#include "../include/logger.h"
#include "../include/auth.h"
#include "../include/saveSystemData.h"
#include "../include/homePageMenu.h"
#include "../include/userFunction.h"

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

StatusInfo performUserOperationsMenu(SystemData *sysData)
{
	int choice;
	StatusInfo status;
	do
	{
		displayBanner();
		centerStrings("ADMIN MENU [MENU DO ADMINISTRADOR]\n");
		centerStrings("USER OPERATIONS MENU [MENU DE OPERAÇÕES DE USUARIO]");
		printf("\n");
		centerStrings("Select option from  1 to 5 to navigate this menu. Select 0 to go back.\n");
		centerStrings("Selecione a opção de 1 a 5 para navegar nesta menu. Selecione 0 para voltar.\n");
		printf("\n");
		printf("\n\t\t1. - Create User [Criar usuário]\n\n");
		printf("\t\t2. - Update User Profile [Atualizar perfil]\n\n");
		printf("\t\t3. - View all users [Visualizar todos os usuários] \n\n");
		printf("\t\t4. - Search for User [Buscar usuário] \n\n");
		printf("\t\t5. - Delete User Profile [Deletar perfil] \n\n");
		printf("\t\t0. - Go Back [Voltar]\n\n");
		printf("\n");
		printf("Enter your choice [Digite sua opção]: ");
		scanf("%d", &choice);
		printf("\n");
		switch (choice)
		{
		case 0:
			homePageMenu(sysData);
			break;
		case 1:
			status = createUserMenu(sysData);
			break;
		case 2:
			status = updateUserProfileMenu(sysData);
			break;
		case 3:
			status = viewAllUsersMenu(sysData);
			break;
		case 4:
			status = searchForUserMenu(sysData);
			break;
		case 5:
			status = deleteUserProfileMenu(sysData);
			break;
		default:
			logPrintMessage(LOG_ERROR, "Invalid input [Entrada inválida]", yes);
			break;
		}

	} while ((choice < 0 || choice > 5) && sysData->appContext->session == true && sysData->appContext->isAuthenticated == true && sysData->appContext->exitFlag == false);
	return status;
}

StatusInfo createUserMenu(SystemData *sysData)
{
	StatusInfo status;
	StatusInfo created = failed;
	do
	{
		displayBanner();
		centerStrings("ADMIN MENU [MENU DO ADMINISTRADOR]\n");
		centerStrings("CREATE USER MENU [MENU DE CRIAR USUARIO]");
		printf("\n");
		centerStrings("Select option from  1 to 2 to navigate this menu. Select 0 to go back.\n");
		centerStrings("Selecione a opção de 1 a 2 para navegar nesta menu. Selecione 0 para voltar.\n");
		printf("\n");
		printf("\n\t\t1. - Create Admin [Criar admin]\n\n");
		printf("\t\t2. - Create User [Criar usuário] \n\n");
		printf("\t\t0. - Go Back [Voltar]\n\n");

		char *name = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
		char *username = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
		char *email = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
		char *password = (char *)malloc(MAX_PASSWORD_LENGTH * sizeof(char));
		char *phone = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
		char *dateCreated = (char *)malloc(MAX_DATE_LENGTH * sizeof(char));
		char *lastUpdated = (char *)malloc(MAX_DATE_LENGTH * sizeof(char));
		char *lastLogin = (char *)malloc(MAX_DATE_LENGTH * sizeof(char));
		char *dateDeleted = (char *)malloc(MAX_DATE_LENGTH * sizeof(char));

		if (name == NULL || username == NULL || email == NULL || password == NULL || phone == NULL || dateCreated == NULL || lastUpdated == NULL || lastLogin == NULL || dateDeleted == NULL)
		{
			logPrintMessage(LOG_ERROR, "Memory allocation for user default data failed [ Alocacao de memoria falhou para os dados padrão do usuário ]", yes);
			freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
			status = failed;
			return status;
		}

		char *now = getCurrentDateTime(TYPE_DATE);

		if (!now)
		{
			logPrintMessage(LOG_ERROR, "Failed to get current date and time [ Falha ao obter a data e hora atual ]", yes);
			freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
			free(now);
			status = failed;
			return status;
		}

		int roleID, userStatus = active, choice = -1;

		while (choice < 0 || choice > 2)
		{
			clearInputBuffer();
			displayBanner();
			centerStrings("ADMIN MENU [MENU DO ADMINISTRADOR]\n");
			centerStrings("CREATE USER MENU [MENU DE CRIAR USUARIO]");
			printf("\n");
			centerStrings("Select option from  1 to 2 to navigate this menu. Select 0 to go back.\n");
			centerStrings("Selecione a opção de 1 a 2 para navegar nesta menu. Selecione 0 para voltar.\n");
			printf("\n");
			printf("\n\t\t1. - Create Admin [Criar admin]\n\n");
			printf("\t\t2. - Create User [Criar usuário] \n\n");
			printf("\t\t0. - Go Back [Voltar]\n\n");
			printf("Enter your choice [Digite sua opção]: ");
			scanf("%d", &choice);
			switch (choice)
			{
			case 0:
				freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
				free(now);
				status = performUserOperationsMenu(sysData);
				return status;
			case 1:
				roleID = ROLE_ADMIN;
				break;
			case 2:
				roleID = ROLE_USER;
				break;
			default:
				logPrintMessage(LOG_ERROR, "Invalid input [Entrada inválida]", yes);
				break;
			}
		}
		clearInputBuffer();
		displayBanner();
		printf("Enter user name [Digite o nome do usuário]: ");
		scanf("%149[^\n]", name);
		while (strlen(name) <= 0 || (name[0] == '0' && strlen(name) == 1))
		{
			if (name[0] == '0' && strlen(name) == 1)
			{
				freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
				free(now);
				status = performUserOperationsMenu(sysData);
				return status;
			}
			else
			{
				if (strlen(name) <= 0)
				{
					logPrintMessage(LOG_ERROR, "Invalid input [Entrada inválida]", yes);
				}
				free(name);
				clearInputBuffer();
				displayBanner();
				name = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
				printf("Enter user name [Digite o nome do usuário]: ");
				scanf("%149[^\n]", name);
			}
		}

		clearInputBuffer();
		displayBanner();
		printf("Enter user username [Digite o username do usuário]: ");
		scanf("%s", username);
		while (strlen(username) <= 0 || (username[0] == '0' && strlen(username) == 1))
		{
			if (username[0] == '0' && strlen(username) == 1)
			{
				freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
				free(now);
				status = performUserOperationsMenu(sysData);
				return status;
			}
			else
			{
				if (strlen(username) <= 0)
				{
					logPrintMessage(LOG_ERROR, "Invalid input [Entrada inválida]", yes);
				}
				free(username);
				clearInputBuffer();
				displayBanner();
				username = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
				printf("Enter user username [Digite o username do usuário]: ");
				scanf("%s", username);
			}
		}

		clearInputBuffer();
		displayBanner();
		printf("Enter user email [Digite o email do usuário]: ");
		scanf("%s", email);
		while (strlen(email) <= 0 || (email[0] == '0' && strlen(email) == 1))
		{
			if (email[0] == '0' && strlen(email) == 1)
			{
				freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
				free(now);
				status = performUserOperationsMenu(sysData);
				return status;
			}
			else
			{
				if (strlen(email) <= 0)
				{
					logPrintMessage(LOG_ERROR, "Invalid input [Entrada inválida]", yes);
				}
				free(email);
				clearInputBuffer();
				displayBanner();
				email = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
				printf("Enter user email [Digite o email do usuário]: ");
				scanf("%s", email);
			}
		}

		clearInputBuffer();
		displayBanner();
		printf("Enter user password [Digite a senha do usuário]: ");
		scanf("%s", password);
		while (strlen(password) <= 0 || (password[0] == '0' && strlen(password) == 1))
		{
			if (password[0] == '0' && strlen(password) == 1)
			{
				freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
				free(now);
				status = performUserOperationsMenu(sysData);
				return status;
			}
			else
			{
				if (strlen(password) <= 0)
				{
					logPrintMessage(LOG_ERROR, "Invalid input [Entrada inválida]", yes);
				}
				free(password);
				clearInputBuffer();
				displayBanner();
				password = (char *)malloc(MAX_PASSWORD_LENGTH * sizeof(char));
				printf("Enter user password [Digite a senha do usuário]: ");
				scanf("%s", password);
			}
		}

		clearInputBuffer();
		displayBanner();
		printf("Enter user phone [Digite o telefone do usuário]: ");
		scanf("%s", phone);
		while (strlen(phone) <= 0 || (phone[0] == '0' && strlen(phone) == 1))
		{
			if (phone[0] == '0' && strlen(phone) == 1)
			{
				freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
				free(now);
				status = performUserOperationsMenu(sysData);
				return status;
			}
			else
			{
				if (strlen(phone) <= 0)
				{
					logPrintMessage(LOG_ERROR, "Invalid input [Entrada inválida]", yes);
				}
				free(phone);
				clearInputBuffer();
				displayBanner();
				phone = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
				printf("Enter user phone [Digite o telefone do usuário]: ");
				scanf("%s", phone);
			}
		}
		strncpy(dateCreated, now, MAX_DATE_LENGTH - 1);
		dateCreated[MAX_DATE_LENGTH - 1] = '\0';

		strncpy(lastUpdated, EMPTY_STRING, MAX_DATE_LENGTH - 1);
		lastUpdated[MAX_DATE_LENGTH - 1] = '\0';

		strncpy(lastLogin, EMPTY_STRING, MAX_DATE_LENGTH - 1);
		lastLogin[MAX_DATE_LENGTH - 1] = '\0';

		strncpy(dateDeleted, EMPTY_STRING, MAX_DATE_LENGTH - 1);
		dateDeleted[MAX_DATE_LENGTH - 1] = '\0';

		created = createUser(sysData, name, username, email, password, phone, roleID, userStatus, dateCreated, lastUpdated, lastLogin, dateDeleted);
		freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
		free(now);
		if (created == failed)
		{
			status = failed;
			return status;
		}
		else
		{
			status = successful;
			return status;
		}

	} while (sysData->appContext->exitFlag == false && created == failed && sysData->appContext->session == true && sysData->appContext->isAuthenticated == true);
	return status;
}

StatusInfo updateUserProfileMenu(SystemData *sysData)
{
	StatusInfo status;
	return status;
}
StatusInfo viewAllUsersMenu(SystemData *sysData)
{
	StatusInfo status;
	return status;
}
StatusInfo searchForUserMenu(SystemData *sysData)
{
	StatusInfo status;
	return status;
}
StatusInfo deleteUserProfileMenu(SystemData *sysData)
{
	StatusInfo status;
	return status;
}

// TODO: Add currency operations
StatusInfo performCurrencyOperationsMenu(SystemData *sysData)
{
	int choice;
	StatusInfo status;
	do
	{

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

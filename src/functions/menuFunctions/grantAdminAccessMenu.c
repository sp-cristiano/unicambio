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
			displayBanner(sysData);
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
				clearInputBuffer();
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
		displayBanner(sysData);
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
			clearInputBuffer();
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
		displayBanner(sysData);
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
			displayBanner(sysData);
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
				clearInputBuffer();
				break;
			}
		}
		clearInputBuffer();
		displayBanner(sysData);
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
				displayBanner(sysData);
				name = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
				printf("Enter user name [Digite o nome do usuário]: ");
				scanf("%149[^\n]", name);
			}
		}

		clearInputBuffer();
		displayBanner(sysData);
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
				displayBanner(sysData);
				username = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
				printf("Enter user username [Digite o username do usuário]: ");
				scanf("%s", username);
			}
		}

		clearInputBuffer();
		displayBanner(sysData);
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
				displayBanner(sysData);
				email = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
				printf("Enter user email [Digite o email do usuário]: ");
				scanf("%s", email);
			}
		}

		clearInputBuffer();
		displayBanner(sysData);
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
				displayBanner(sysData);
				password = (char *)malloc(MAX_PASSWORD_LENGTH * sizeof(char));
				printf("Enter user password [Digite a senha do usuário]: ");
				scanf("%s", password);
			}
		}

		clearInputBuffer();
		displayBanner(sysData);
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
				displayBanner(sysData);
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
	int currentUserRoleID = sysData->appContext->currentUserRoleID;
	char questionToUpdate;
	size_t userIndex;

	StatusInfo status, updated = failed;

	int choice;
	if (currentUserRoleID == ROLE_ADMIN)
	{
		do
		{
			displayBanner(sysData);
			centerStrings("ADMIN MENU [MENU DO ADMINISTRADOR]\n");
			centerStrings("UPDATE USER PROFILE [ATUALIZAR PERFIL DE USUARIO]");
			printf("\n");
			centerStrings("Enter the user ID of the user you want to update. Enter 0 to go back.\n");
			centerStrings("Digite o ID do usuário que deseja atualizar. Digite 0 para voltar.\n");
			printf("\n");
			printf("\n");
			printf("S/N   ID [ID]     NAME [NOME]\n");
			for (size_t i = 0; i < sysData->userCount; i++)
			{
				printf("%ld     %d        %s\n", (i + 1), sysData->users[i].userID, sysData->users[i].name);
			}
			printf("\n");
			printf("Enter user ID [Digite ID do usuário]: ");
			scanf("%d", &choice);

			if (choice == 0)
			{
				performUserOperationsMenu(sysData);
			}
			userIndex = (size_t)getUserIndexByID(sysData, choice); // getUserIndexByID()
			size_t zerro = 0;

			if (userIndex >= zerro && userIndex < sysData->userCount)
			{
				do
				{
					// clearInputBuffer();
					displayBanner(sysData);
					centerStrings("ADMIN MENU [MENU DO ADMINISTRADOR]\n");
					centerStrings("UPDATE USER PROFILE [ATUALIZAR PERFIL DE USUARIO]");
					printf("\n");
					viewSingleUser(sysData, userIndex);
					centerStrings("\n\n Do you still want to update this user data? (y/n)");
					centerStrings("\nVocê ainda deseja atualizar os dados deste usuário? (s/n)");
					// clearInputBuffer();
					scanf(" %c", &questionToUpdate);
					if (questionToUpdate != 'y' && questionToUpdate != 'Y' && questionToUpdate != 's' && questionToUpdate != 'S' && questionToUpdate != 'n' && questionToUpdate != 'N')
					{
						logPrintMessage(LOG_WARNING, "Invalid Input [Entrada Invalida]", yes);
					}

				} while (questionToUpdate != 'y' && questionToUpdate != 'Y' && questionToUpdate != 's' && questionToUpdate != 'S' && questionToUpdate != 'n' && questionToUpdate != 'N');

				if (questionToUpdate == 'y' || questionToUpdate == 'Y' || questionToUpdate == 's' || questionToUpdate == 'S')
				{
					int choice;
					do
					{
						displayBanner(sysData);

						char *now = getCurrentDateTime(TYPE_DATETIME);
						centerStrings("ADMIN MENU [MENU DO ADMINISTRADOR]\n");

						selectOptionToUpdateUserByAdmin(sysData, userIndex);

						printf("\n");
						printf("Enter your choice [Digite sua opção]: ");
						clearInputBuffer();
						scanf("%d", &choice);
						switch (choice)
						{
						case 0:
							status = performUserOperationsMenu(sysData);
							updated = failed;
							break;
						case 1:
							char *name = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));

							printf("User Name to update %s [Nome de usuário para atualizar %s]\n", sysData->users[userIndex].name, sysData->users[userIndex].name);
							printf("Enter New User Name [Digite o novo nome do usuário]: ");
							// clearInputBuffer();
							scanf("%149[^\n]", name);
							strcpy(sysData->users[userIndex].name, name);
							strcpy(sysData->users[userIndex].lastUpdated, now);
							updated = saveSystemData(sysData);
							// free(name);
							// free(now);
							viewSingleUser(sysData, userIndex);
							break;
						case 2:
							char *username = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
							printf("User Username to update %s [Username de usuário para atualizar %s]\n", sysData->users[userIndex].username, sysData->users[userIndex].username);
							printf("Enter New User Username [Digite o novo username do usuário]: ");
							// clearInputBuffer();
							scanf("%s", username);
							strcpy(sysData->users[userIndex].username, username);
							strcpy(sysData->users[userIndex].lastUpdated, now);
							updated = saveSystemData(sysData);
							// free(username);
							// free(now);
							viewSingleUser(sysData, userIndex);
							break;
						case 3:
							char *email = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
							printf("User Email to update %s [Email de usuário para atualizar %s]\n", sysData->users[userIndex].email, sysData->users[userIndex].email);
							printf("Enter New User Email [Digite o novo email do usuário]: ");
							// clearInputBuffer();
							scanf("%s", email);
							strcpy(sysData->users[userIndex].email, email);
							strcpy(sysData->users[userIndex].lastUpdated, now);
							updated = saveSystemData(sysData);
							// free(email);
							// free(now);
							viewSingleUser(sysData, userIndex);
							break;
						case 4:
							char *password = (char *)malloc(MAX_PASSWORD_LENGTH * sizeof(char));

							printf("User Password to update %s [Senha de usuário para atualizar %s]\n", sysData->users[userIndex].password, sysData->users[userIndex].password);
							if (!password)
							{
								logPrintMessage(LOG_ERROR, "Failed to allocate memory for password update [Falha ao alocar memória]", yes);
								free(password);
								return failed;
							}

							printf("Enter New User Password [Digite a nova senha do usuário]: ");
							clearInputBuffer();
							scanf("%s", password);
							char *hashedPWD = hashPassword(password);
							strcpy(sysData->users[userIndex].password, hashedPWD);
							strcpy(sysData->users[userIndex].lastUpdated, now);
							updated = saveSystemData(sysData);
							// free(hashedPWD);
							// free(password);
							// free(now);

							viewSingleUser(sysData, userIndex);

							break;
						case 5:
							printf("User Phone to update %s [Telefone de usuário para atualizar %s]\n", sysData->users[userIndex].phone, sysData->users[userIndex].phone);
							printf("Enter New User Phone [Digite o novo telefone do usuário]: ");
							// clearInputBuffer();
							char *phone = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
							scanf("%s", phone);
							strcpy(sysData->users[userIndex].phone, phone);
							strcpy(sysData->users[userIndex].lastUpdated, now);
							updated = saveSystemData(sysData);
							// free(phone);
							// free(now);
							viewSingleUser(sysData, userIndex);
							break;
						case 6:
							printf("User Role to update %d [Papel de usuário para atualizar %d]\n", sysData->users[userIndex].roleID, sysData->users[userIndex].roleID);
							clearInputBuffer();
							printf("Enter New User Role [Digite o novo papel do usuário]: ");
							scanf("%d", &sysData->users[userIndex].roleID);
							sysData->users[userIndex].lastUpdated = now;
							updated = saveSystemData(sysData);
							// free(now);
							viewSingleUser(sysData, userIndex);
							break;
						case 7:
							printf("User Status to update %d [Status de usuário para atualizar %d]\n", sysData->users[userIndex].userStatus, sysData->users[userIndex].userStatus);
							printf("Enter New User Status [Digite o novo status do usuário]: ");
							scanf("%d", &sysData->users[userIndex].userStatus);
							sysData->users[userIndex].lastUpdated = now;
							updated = saveSystemData(sysData);
							// free(now);
							viewSingleUser(sysData, userIndex);
							break;
						default:
							logPrintMessage(LOG_WARNING, "Invalid Input [Entrada Invalida]", yes);
							updated = failed;
							clearInputBuffer();
							// free(now);
							break;
						}
						// free(now);
					} while ((choice < 0 || choice > 7));
				}
				else if (questionToUpdate == 'n' || questionToUpdate == 'N')
				{
					status = performUserOperationsMenu(sysData);
					updated = failed;
				}
			}
			else
			{
				updated = failed;
			}

		} while (updated == failed && sysData->appContext->session == true && sysData->appContext->isAuthenticated == true && sysData->appContext->exitFlag == false);
	}
	else
	{
		// TODO UPDATE FUNCTIONS FOR NON ADMIN
	}
	// free(searchCriteria);
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

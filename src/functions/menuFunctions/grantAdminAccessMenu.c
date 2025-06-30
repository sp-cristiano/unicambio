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
	int choice, result;
	StatusInfo status;
	while (sysData->appContext->session == true && sysData->appContext->isAuthenticated == true && sysData->appContext->exitFlag == false)
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
		result = scanf("%d", &choice);
		clearInputBuffer();

		if (result != 1 || choice < 0 || choice > 4)
		{
			printf("\n\n");
			logPrintMessage(LOG_ERROR, "Invalid input. Please try again. [Entrada inválida. Por favor, tente novamente.]", yes);
			status = failed;
			continue;
		}
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
			printf("\n\n");
			logPrintMessage(LOG_ERROR, "Invalid input [Entrada inválida]", yes);
			break;
		}
	}
	return status;
}

StatusInfo performUserOperationsMenu(SystemData *sysData)
{
	int choice, result;
	StatusInfo status;

	while (sysData->appContext->session == true && sysData->appContext->isAuthenticated == true && sysData->appContext->exitFlag == false)
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
		result = scanf("%d", &choice);

		clearInputBuffer();

		if (result != 1 || (choice < 0 || choice > 5))
		{
			printf("\n\n");
			logPrintMessage(LOG_ERROR, "Invalid input. Please try again. [Entrada inválida. Por favor, tente novamente.]", yes);
			status = failed;
			continue;
		}

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
			printf("\n\n");
			logPrintMessage(LOG_ERROR, "Invalid input [Entrada inválida]", yes);
			break;
		}
	}
	return status;
}

StatusInfo createUserMenu(SystemData *sysData)
{
	StatusInfo status, created = failed;
	int result, roleID, userStatus = active;

	while (created == failed && sysData->appContext->session == true && sysData->appContext->isAuthenticated == true && sysData->appContext->exitFlag == false)
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
			logPrintMessage(LOG_ERROR, "Memory allocation for user data failed [ Alocacao de memoria falhou para os dados do usuário ]", yes);
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

		strncpy(dateCreated, now, MAX_DATE_LENGTH - 1);
		dateCreated[MAX_DATE_LENGTH - 1] = '\0';

		strncpy(lastUpdated, EMPTY_STRING, MAX_DATE_LENGTH - 1);
		lastUpdated[MAX_DATE_LENGTH - 1] = '\0';

		strncpy(lastLogin, EMPTY_STRING, MAX_DATE_LENGTH - 1);
		lastLogin[MAX_DATE_LENGTH - 1] = '\0';

		strncpy(dateDeleted, EMPTY_STRING, MAX_DATE_LENGTH - 1);
		dateDeleted[MAX_DATE_LENGTH - 1] = '\0';

		printf("Choose a user role [Escolha um papel de usuário]: ");
		result = scanf("%d", &roleID);

		clearInputBuffer();

		if (result != 1 || (roleID < 0 || roleID > 2))
		{
			printf("\n\n");
			logPrintMessage(LOG_ERROR, "Invalid input. Please try again. [Entrada inválida. Por favor, tente novamente.]", yes);
			freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
			free(now);
			status = failed;
			continue;
		}

		switch (roleID)
		{
		case 0:
			freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
			free(now);
			status = performUserOperationsMenu(sysData);
			break;
		case 1:
			roleID = ROLE_ADMIN;
			break;
		case 2:
			roleID = ROLE_USER;
			// status = createUser(sysData, name, username, email, password, phone, roleID, userStatus, dateCreated, lastUpdated, lastLogin, dateDeleted);
			// freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
			// free(now);
			// created = successful;
			break;
		default:
			printf("\n\n");
			freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
			free(now);
			logPrintMessage(LOG_ERROR, "Invalid input [Entrada inválida]", yes);
			created = failed;
			break;
		}

		// for name starts here
		displayBanner(sysData);
		printf("\n\nEnter user name [Digite o nome do usuário]: ");
		result = scanf("%149[^\n]", name);
		clearInputBuffer();
		while (result != 1 || strlen(name) == 0)
		{
			printf("\n\n");
			logPrintMessage(LOG_ERROR, "Name can not be empty. Please try again. [O nome nao pode estar vazio. Por favor, tente novamente.]", yes);
			free(name);

			displayBanner(sysData);

			name = malloc(MAX_NAME_LENGTH * sizeof(char));
			if (name == NULL)
			{
				logPrintMessage(LOG_ERROR, "Memory allocation for user name failed [ Alocacao de memoria falhou para o nome do usuário ]", yes);
				freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
				free(now);
				status = failed;
				return status;
			}
			printf("\n\nEnter user name [Digite o nome do usuário]: ");
			result = scanf("%149[^\n]", name);
			clearInputBuffer();
		}
		if (strcmp(name, "0") == 0)
		{
			sysData->appContext->goBack = true;
			freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
			free(now);
			status = createUserMenu(sysData);
			return status;
		}
		// for name ends here

		// for username starts here
		displayBanner(sysData);
		printf("\n\nEnter user username [Digite o nome de usuário]: ");
		result = scanf("%s", username);
		clearInputBuffer();
		while (result != 1 || strlen(username) == 0)
		{
			printf("\n\n");
			logPrintMessage(LOG_ERROR, "Username can not be empty. Please try again. [O nome de usuário nao pode estar vazio. Por favor, tente novamente.]", yes);
			free(username);

			displayBanner(sysData);

			username = malloc(MAX_NAME_LENGTH * sizeof(char));
			if (username == NULL)
			{
				logPrintMessage(LOG_ERROR, "Memory allocation for user username failed [ Alocacao de memoria falhou para o nome de usuário ]", yes);
				freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
				free(now);
				status = failed;
				return status;
			}
			printf("\n\nEnter user username [Digite o nome de usuário]: ");
			result = scanf("%s", username);
			clearInputBuffer();
		}
		if (strcmp(username, "0") == 0)
		{
			sysData->appContext->goBack = true;
			freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
			free(now);
			status = createUserMenu(sysData);
			return status;
		}
		// for username ends here

		// for email starts here
		displayBanner(sysData);
		printf("\n\nEnter user email [Digite o email do usuário]: ");
		result = scanf("%s", email);
		clearInputBuffer();
		while (result != 1 || strlen(email) == 0)
		{
			printf("\n\n");
			logPrintMessage(LOG_ERROR, "Email can not be empty. Please try again. [O email nao pode estar vazio. Por favor, tente novamente.]", yes);
			free(email);

			displayBanner(sysData);

			email = malloc(MAX_NAME_LENGTH * sizeof(char));
			if (email == NULL)
			{
				logPrintMessage(LOG_ERROR, "Memory allocation for user email failed [ Alocacao de memoria falhou para o email do usuário ]", yes);
				freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
				free(now);
				status = failed;
				return status;
			}
			printf("\n\nEnter user email [Digite o email do usuário]: ");
			result = scanf("%s", email);
			clearInputBuffer();
		}
		if (strcmp(email, "0") == 0)
		{
			sysData->appContext->goBack = true;
			freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
			free(now);
			status = createUserMenu(sysData);
			return status;
		}
		// for email ends here

		// for password starts here
		displayBanner(sysData);
		printf("\n\nEnter user password [Digite a senha do usuário]: ");
		result = scanf("%s", password);
		clearInputBuffer();
		while (result != 1 || strlen(password) == 0)
		{
			printf("\n\n");
			logPrintMessage(LOG_ERROR, "Password can not be empty. Please try again. [A senha nao pode estar vazia. Por favor, tente novamente.]", yes);
			free(password);

			displayBanner(sysData);

			password = malloc(MAX_PASSWORD_LENGTH * sizeof(char));
			if (password == NULL)
			{
				logPrintMessage(LOG_ERROR, "Memory allocation for user password failed [ Alocacao de memoria falhou para a senha do usuário ]", yes);
				freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
				free(now);
				status = failed;
				return status;
			}
			printf("\n\nEnter user password [Digite a senha do usuário]: ");
			result = scanf("%s", password);
			clearInputBuffer();
		}
		if (strcmp(password, "0") == 0)
		{
			sysData->appContext->goBack = true;
			freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
			free(now);
			status = createUserMenu(sysData);
			return status;
		}
		// for password ends here

		// for phone starts here
		displayBanner(sysData);
		printf("\n\nEnter user phone [Digite o telefone do usuário]: ");
		result = scanf("%s", phone);
		clearInputBuffer();
		while (result != 1 || strlen(phone) == 0)
		{
			printf("\n\n");
			logPrintMessage(LOG_ERROR, "Phone can not be empty. Please try again. [O telefone nao pode estar vazio. Por favor, tente novamente.]", yes);
			free(phone);

			displayBanner(sysData);

			phone = malloc(MAX_NAME_LENGTH * sizeof(char));
			if (phone == NULL)
			{
				logPrintMessage(LOG_ERROR, "Memory allocation for user phone failed [ Alocacao de memoria falhou para o telefone do usuário ]", yes);
				freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
				free(now);
				status = failed;
				return status;
			}
			printf("\n\nEnter user phone [Digite o telefone do usuário]: ");
			result = scanf("%s", phone);
			clearInputBuffer();
		}
		if (strcmp(phone, "0") == 0)
		{
			sysData->appContext->goBack = true;
			freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
			free(now);
			status = createUserMenu(sysData);
			return status;
		}
		// for phone ends here

		status = createUser(sysData, name, username, email, password, phone, roleID, userStatus, dateCreated, lastUpdated, lastLogin, dateDeleted);
		freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
		free(now);
		created = successful;

		return status;
	}
	return status;
}

// TODO: REFACTOR UPDATE USER MENU

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
			printf("\tS/N   ID [ID]   ROLE    STATUS    NAME [NOME]\n");
			printSymbols(SCREEN_WIDTH, '=');
			for (size_t i = 0; i < sysData->userCount; i++)
			{
				if (sysData->users[i].userStatus == active)
				{
					printf("\t%ld     %d      %d        %d         %s\n", (i + 1), sysData->users[i].userID, sysData->users[i].roleID, sysData->users[i].userStatus, sysData->users[i].name);
				}
				else
				{
					printf("\t%ld     %d      %d       %d         %s\n", (i + 1), sysData->users[i].userID, sysData->users[i].roleID, sysData->users[i].userStatus, sysData->users[i].name);
				}
				printSymbols(SCREEN_WIDTH, '-');
			}
			printf("\n");
			printf("Enter user ID [Digite ID do usuário]: ");
			scanf("%d", &choice);

			if (choice == 0)
			{
				performUserOperationsMenu(sysData);
				updated = failed;
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

						selectOptionToUpdateUserByAdmin();

						printf("\n");
						printf("Enter your choice [Digite sua opção]: ");
						clearInputBuffer();
						scanf("%d", &choice);

						updated = updateUser(sysData, userIndex, choice, now, updated, status);

						// free(now);
					} while ((choice < 0 || choice > 7));
					// status = performUserOperationsMenu(sysData)
				}
				else if (questionToUpdate == 'n' || questionToUpdate == 'N')
				{
					status = performUserOperationsMenu(sysData);
					clearInputBuffer();
					updated = failed;
				}
			}
			else
			{
				updated = failed;
				status = failed;
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
	int choice;
	StatusInfo status;
	do
	{
		int usersNotDeletedCount = 0, usersTempDeletedCount = 0;
		displayBanner(sysData);
		centerStrings("ADMIN MENU [MENU DO ADMINISTRADOR]\n");
		centerStrings("VIEW ALL USERS MENU [MENU DE VISUALIZAR TODOS OS USUÁRIOS]");
		printf("\n");

		printf("\tS/N   ID [ID]     NAME [NOME]\n");
		printSymbols(SCREEN_WIDTH, '=');

		for (size_t i = 0; i < sysData->userCount; i++)
		{
			if (sysData->users[i].userStatus == deleted)
			{
				usersTempDeletedCount++;
				continue;
			}
			else
			{
				usersNotDeletedCount++;
				printf("\t%d     %d        %s\n", usersNotDeletedCount, sysData->users[i].userID, sysData->users[i].name);
				printSymbols(SCREEN_WIDTH, '-');
			}
		}
		printf("\n\n");
		if (sysData->appContext->currentUserRoleID == ROLE_ADMIN)
		{
			printSymbols(SCREEN_WIDTH, '=');

			printf("TOTAL ACTIVE USERS[TOTAL DE USUARIOS ATIVOS]:                                  [%d]\n", usersNotDeletedCount);
			printSymbols(SCREEN_WIDTH, '-');
			printf("TOTAL USERS TEMPORARILY DELETED [TOTAL DE USUARIOS TEMPORARIAMENTE EXCLUIDOS]: [%d]\n", usersTempDeletedCount);
			printSymbols(SCREEN_WIDTH, '-');
			printf("TOTAL USERS[TOTAL DE USUARIOS]:                                                [%ld]\n", sysData->userCount);
		}
		else
		{
			printf("TOTAL USERS[TOTAL DE USUARIOS]:[ %d ]\n", usersNotDeletedCount);
		}
		printf("\n\n");
		printf("Press 0 to go back [Pressione 0 para voltar]: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:
			status = performUserOperationsMenu(sysData);
			break;
		default:
			centerStrings("Invalid Input [Entrada Invalida]");
			sleep(MIN_SLEEP);
			clearInputBuffer();
			break;
		}

	} while (choice != 0 && sysData->appContext->session == true && sysData->appContext->isAuthenticated == true && sysData->appContext->exitFlag == false);

	return status;
}
StatusInfo searchForUserMenu(SystemData *sysData)
{
	StatusInfo status, userFound = failed;

	char searchCriteria[MAX_NAME_LENGTH];
	do
	{
		displayBanner(sysData);
		centerStrings("ADMIN MENU [MENU DO ADMINISTRADOR]\n");
		centerStrings("SEARCH USER MENU [MENU DE BUSCA DE USUARIO]");
		printf("\n");
		clearInputBuffer();
		centerStrings("Enter search criteria or press 0 to go back [Digite o criterio de busca ou pressione 0 para voltar]: ");
		printf("\n");
		printf("Enter search criteria [Digite o criterio de busca]: ");
		scanf("%149[^\n]", searchCriteria);
		if (searchCriteria[0] == '0' && strlen(searchCriteria) == 1)
		{
			status = performUserOperationsMenu(sysData);
			userFound = failed;
			status = failed;
		}
		else
		{
			int userID = searchForUser(sysData, searchCriteria);
			if (userID < 0)
			{
				logPrintMessage(LOG_ERROR, "User not found  while searching. [Usuario nao encontrado na busca]", yes);
				userFound = failed;
				status = failed;
			}
			else
			{
				size_t userIndex = getUserIndexByID(sysData, userID);
				if (userIndex != (size_t)failed)
				{
					userFound = successful;
					int choice;
					do
					{
						displayBanner(sysData);
						centerStrings("ADMIN MENU [MENU DO ADMINISTRADOR]\n");
						centerStrings("SEARCH USER MENU [MENU DE BUSCA DE USUARIO]");
						printf("\n");
						status = viewSingleUser(sysData, userIndex);
						printf("\n\nEnter 0 to go back to search menu [Pressione 0 para voltar ao menu de busca]: ");
						scanf("%d", &choice);
						switch (choice)
						{
						case 0:
							status = searchForUserMenu(sysData);
							break;
						default:
							logPrintMessage(LOG_ERROR, "Invalid Input [Entrada Invalida]", yes);
							clearInputBuffer();
						}

					} while (choice != 0);
				}
			}
		}

	} while (userFound == failed && sysData->appContext->session == true && sysData->appContext->isAuthenticated == true && sysData->appContext->exitFlag == false);
	return status;
}
StatusInfo deleteUserProfileMenu(SystemData *sysData)
{
	StatusInfo status;
	char questionToDelete;
	size_t userIndex, zerro = 0;
	int userID, userFound = false;
	do
	{
		displayBanner(sysData);
		centerStrings("ADMIN MENU [MENU DO ADMINISTRADOR]\n");
		centerStrings("DELETE USER MENU [MENU DE EXCLUSÃO DE USUARIO]");
		printf("\n");
		int usersNotDeletedCount = 0, usersTempDeletedCount = 0;

		printf("\tS/N   ID [ID]     NAME [NOME]\n");
		printSymbols(SCREEN_WIDTH, '=');

		for (size_t i = 0; i < sysData->userCount; i++)
		{
			if (sysData->users[i].userStatus == deleted)
			{
				usersTempDeletedCount++;
				continue;
			}
			else
			{
				usersNotDeletedCount++;
				printf("\t%d     %d        %s\n", usersNotDeletedCount, sysData->users[i].userID, sysData->users[i].name);
				printSymbols(SCREEN_WIDTH, '-');
			}
		}
		printf("\n\n");
		if (sysData->appContext->currentUserRoleID == ROLE_ADMIN)
		{
			printSymbols(SCREEN_WIDTH, '=');

			printf("TOTAL ACTIVE USERS[TOTAL DE USUARIOS ATIVOS]:                                  [%d]\n", usersNotDeletedCount);
			printSymbols(SCREEN_WIDTH, '-');
			printf("TOTAL USERS TEMPORARILY DELETED [TOTAL DE USUARIOS TEMPORARIAMENTE EXCLUIDOS]: [%d]\n", usersTempDeletedCount);
			printSymbols(SCREEN_WIDTH, '-');
			printf("TOTAL USERS[TOTAL DE USUARIOS]:                                                [%ld]\n", sysData->userCount);
		}
		else
		{
			printf("TOTAL USERS[TOTAL DE USUARIOS]:[ %d ]\n", usersNotDeletedCount);
		}
		printf("\n\n");
		centerStrings("Enter user ID to delete or 0 to go back to user menu [Pressione 0 para voltar ao menu de usuario]\n\n");

		printf("Enter user ID [Digite o ID do usuário]: ");

		scanf("%d", &userID);
		if (userID == 0)
		{
			status = performUserOperationsMenu(sysData);
			userFound = false;
		}
		userIndex = (size_t)getUserIndexByID(sysData, userID);

		if (userIndex >= zerro && userIndex < sysData->userCount)
		{
			do
			{
				displayBanner(sysData);
				centerStrings("ADMIN MENU [MENU DO ADMINISTRADOR]\n");
				centerStrings("DELETE USER MENU [MENU DE EXCLUSÃO DE USUARIO]");
				printf("\n");
				viewSingleUser(sysData, userIndex);
				printf("\n\n");
				centerStrings("Are you sure you want to delete this user?(y/n)");
				centerStrings("[Tem certeza que deseja excluir esse usuario? (s/n)]\n\n");
				scanf(" %c", &questionToDelete);
				if (questionToDelete != 'y' && questionToDelete != 'Y' && questionToDelete != 's' && questionToDelete != 'S' && questionToDelete != 'n' && questionToDelete != 'N')
				{
					logPrintMessage(LOG_ERROR, "Invalid Input [Entrada Invalida]", yes);

					clearInputBuffer();
				}
			} while (questionToDelete != 'y' && questionToDelete != 'Y' && questionToDelete != 's' && questionToDelete != 'S' && questionToDelete != 'n' && questionToDelete != 'N');
			if (questionToDelete == 'y' || questionToDelete == 'Y' || questionToDelete == 's' || questionToDelete == 'S')
			{
				char *now = getCurrentDateTime(TYPE_DATETIME);
				sysData->users[userIndex].userStatus = deleted;

				strcpy(sysData->users[userIndex].lastUpdated, now);

				strcpy(sysData->users[userIndex].dateDeleted, now);
				// saveSystemData(sysData);
				status = successful;
				userFound = true;
			}
		}
		else
		{
			status = failed;
			userFound = false;
			clearInputBuffer();
		}

	} while (userFound == false && sysData->appContext->session == true && sysData->appContext->isAuthenticated == true && sysData->appContext->exitFlag == false);
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
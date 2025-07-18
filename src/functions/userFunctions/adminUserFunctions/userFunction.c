#include "../include/userFunction.h"
#include "../include/unicambio.h"
#include "../include/structures.h"
#include "../include/enum.h"
#include "../include/logger.h"
#include "../include/utilities.h"
#include "../include/saveSystemData.h"
#include "../include/grantAdminAccessMenu.h"
#include "../include/auth.h"

StatusInfo createUser(SystemData *sysData, char *name, char *username, char *email, char *password, char *phone, int roleID, int userStatus, char *dateCreated, char *lastUpdated, char *lastLogin, char *dateDeleted)
{
	StatusInfo status;
	if (!sysData)
	{
		logPrintMessage(LOG_ERROR, "System data is Null. Failed to create user [ Dados do sistema nulo. Falha ao criar o usuário ]", yes);
		status = failed;
		return status;
	}

	if (!sysData->appContext->adminUserEmail || !sysData->appContext->adminUserPassword || !sysData->appContext->adminUserPhone)
	{
		logPrintMessage(LOG_ERROR, "Admin default user data in app context is empty", yes);
		logPrintMessage(LOG_ERROR, "[ Dados padrão do usuário admin no contexto da aplicação estao vazios ]", yes);
		status = failed;
		return status;
	}

	if (!name || !username || !email || !password || !phone)
	{
		logPrintMessage(LOG_ERROR, "One or more user data is empty [ Um ou mais dados do usuário estao vazios ]", yes);
		status = failed;
		return status;
	}
	if (userStatus == active)
	{
		if (sysData->userCount >= sysData->userCapacity)
		{
			size_t newCapacity = (sysData->userCapacity * 2) + 2;
			UserInfo *tempUserSize = realloc(sysData->users, newCapacity * sizeof(UserInfo));
			if (!tempUserSize)
			{
				logPrintMessage(LOG_ERROR, "Failed to resize user array [ Falha ao redimensionar o array de usuário ]", yes);
				status = failed;
				return status;
			}
			sysData->users = tempUserSize;
			sysData->userCapacity = newCapacity;
		}
		int userID = randomNumber(1000, 9999);

		if (sysData->users && sysData->userCount > 0)
		{
			for (size_t i = 0; i < sysData->userCount; i++)
			{
				if (sysData->users[i].userID == userID)
				{
					userID = randomNumber(1000, 9999);
					i = 0;
				}
				if ((sysData->users[i].email && strcmp(sysData->users[i].email, email) == 0) || (sysData->users[i].username && strcmp(sysData->users[i].username, username) == 0) || (sysData->users[i].phone && strcmp(sysData->users[i].phone, phone) == 0))
				{
					logPrintMessage(LOG_ERROR, "User already exists [ O usuário ja existe ]", yes);
					status = failed;
					return status;
				}
			}
		}

		char *hashedPassword = hashPassword(password);
		if (!hashedPassword)
		{
			logPrintMessage(LOG_ERROR, "Failed to hash password [ Falha ao hashar a senha ]", yes);
			// free(hashedPassword);
			status = failed;
			return status;
		}

		sysData->users[sysData->userCount].userID = userID;

		sysData->users[sysData->userCount].name = strdup(name);
		if (sysData->users[sysData->userCount].name == NULL)
		{
			logPrintMessage(LOG_ERROR, "Failed to save user name [ Falha ao salvar o nome do usuário ]", yes);
			free(hashedPassword);
			status = failed;
			return status;
		}

		sysData->users[sysData->userCount].username = strdup(username);
		if (sysData->users[sysData->userCount].username == NULL)
		{
			logPrintMessage(LOG_ERROR, "Failed to save user username [ Falha ao salvar o username do usuário ]", yes);
			status = failed;
			free(sysData->users[sysData->userCount].name);
			free(hashedPassword);
			return status;
		}

		sysData->users[sysData->userCount].email = strdup(email);
		if (sysData->users[sysData->userCount].email == NULL)
		{
			logPrintMessage(LOG_ERROR, "Failed to save user email [ Falha ao salvar o email do usuário ]", yes);
			status = failed;
			free(sysData->users[sysData->userCount].username);
			free(sysData->users[sysData->userCount].name);
			free(hashedPassword);
			return status;
		}
		sysData->users[sysData->userCount].password = strdup(hashedPassword);
		if (sysData->users[sysData->userCount].password == NULL)
		{
			logPrintMessage(LOG_ERROR, "Failed to save user password [ Falha ao salvar a senha do usuário ]", yes);
			status = failed;
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].username);
			free(sysData->users[sysData->userCount].name);
			free(hashedPassword);
			return status;
		}
		sysData->users[sysData->userCount].phone = strdup(phone);
		if (sysData->users[sysData->userCount].phone == NULL)
		{
			logPrintMessage(LOG_ERROR, "Failed to save user phone [ Falha ao salvar o telefone do usuário ]", yes);
			status = failed;
			free(sysData->users[sysData->userCount].password);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].username);
			free(sysData->users[sysData->userCount].name);
			free(hashedPassword);

			return status;
		}
		sysData->users[sysData->userCount].roleID = roleID;

		sysData->users[sysData->userCount].userStatus = userStatus;

		sysData->users[sysData->userCount].dateCreated = strdup(dateCreated);
		if (sysData->users[sysData->userCount].dateCreated == NULL)
		{
			logPrintMessage(LOG_ERROR, "Failed to save user creation date [ Falha ao salvar a data de criação do usuário ]", yes);
			status = failed;
			free(sysData->users[sysData->userCount].phone);
			free(sysData->users[sysData->userCount].password);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].username);
			free(sysData->users[sysData->userCount].name);
			free(hashedPassword);

			return status;
		}
		sysData->users[sysData->userCount].lastUpdated = strdup(lastUpdated);
		if (sysData->users[sysData->userCount].lastUpdated == NULL)
		{
			logPrintMessage(LOG_ERROR, "Failed to save user last updated date [ Falha ao salvar a data de atualização do usuário ]", yes);
			status = failed;
			free(sysData->users[sysData->userCount].dateCreated);
			free(sysData->users[sysData->userCount].phone);
			free(sysData->users[sysData->userCount].password);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].username);
			free(sysData->users[sysData->userCount].name);
			free(hashedPassword);

			return status;
		}
		sysData->users[sysData->userCount].lastLogin = strdup(lastLogin);
		if (sysData->users[sysData->userCount].lastLogin == NULL)
		{
			logPrintMessage(LOG_ERROR, "Failed to save user last login date [ Falha ao salvar a data de login do usuário ]", yes);
			status = failed;
			free(sysData->users[sysData->userCount].lastUpdated);
			free(sysData->users[sysData->userCount].dateCreated);
			free(sysData->users[sysData->userCount].phone);
			free(sysData->users[sysData->userCount].password);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].username);
			free(sysData->users[sysData->userCount].name);
			free(hashedPassword);

			return status;
		}
		sysData->users[sysData->userCount].dateDeleted = strdup(dateDeleted);
		if (sysData->users[sysData->userCount].dateDeleted == NULL)
		{
			logPrintMessage(LOG_ERROR, "Failed to save user deleted date [ Falha ao salvar a data de exclusão do usuário ]", yes);
			status = failed;
			free(sysData->users[sysData->userCount].lastLogin);
			free(sysData->users[sysData->userCount].lastUpdated);
			free(sysData->users[sysData->userCount].dateCreated);
			free(sysData->users[sysData->userCount].phone);
			free(sysData->users[sysData->userCount].password);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].username);
			free(sysData->users[sysData->userCount].name);
			free(hashedPassword);

			return status;
		}

		sysData->userCount++;

		status = successful;

		saveUserData(sysData);

		free(hashedPassword);
		return status;
	}
	status = failed;
	return status;
}

StatusInfo saveUserData(SystemData *sysData)
{
	StatusInfo status;

	if (!sysData)
	{
		logPrintMessage(LOG_ERROR, "System data is Null. Failed to save user data [ Dados do sistema nulo. Falha ao salvar dados do usuário ]", yes);
		status = failed;
		return status;
	}
	FILE *userFile = fopen(USER_DATA_FILE_PATH, "w");
	if (!userFile)
	{
		logPrintMessage(LOG_ERROR, "Failed to open user data file [ Falha ao abrir o arquivo de dados do usuário ]", yes);
		status = failed;
		return status;
	}
	if (sysData->userCount == 0)
	{
		logPrintMessage(LOG_INFO, "There is no new user to save [ Nao houve nenhum novo usuário para salvar ]", yes);
		fclose(userFile);
		status = successful;
		return status;
	}

	for (size_t i = 0; i < sysData->userCount; i++)
	{
		fprintf(userFile, "%d|%s|%s|%s|%s|%s|%d|%d|%s|%s|%s|%s|\n", sysData->users[i].userID, sysData->users[i].name, sysData->users[i].username, sysData->users[i].email, sysData->users[i].password, sysData->users[i].phone, sysData->users[i].roleID, sysData->users[i].userStatus, sysData->users[i].dateCreated, sysData->users[i].lastUpdated, sysData->users[i].lastLogin, sysData->users[i].dateDeleted);
	}
	if (fclose(userFile) != 0)
	{
		logPrintMessage(LOG_ERROR, "Failed to close user data file [ Falha ao fechar o arquivo de dados do usuário ]", yes);
		status = failed;
		return status;
	}
	status = successful;
	logPrintMessage(LOG_SUCCESS, "User data saved successfully [ Dados do usuário salvos com sucesso ]", yes);
	return status;
}

StatusInfo loadUserData(SystemData *sysData)
{
	StatusInfo status;

	if (!sysData)
	{

		logPrintMessage(LOG_ERROR, "System data is Null. Failed to load user data [ Dados do sistema nulo. Falha ao carregar dados do usuário ]", yes);
		status = failed;
		return status;
	}

	FILE *userFile = fopen(USER_DATA_FILE_PATH, "r");
	if (!userFile)
	{
		logPrintMessage(LOG_ERROR, "Failed to open user data file [ Falha ao abrir o arquivo de dados do usuário ]", yes);
		status = failed;
		return status;
	}

	int _userID, _roleID, _userStatus;
	char _name[MAX_NAME_LENGTH], _userName[MAX_NAME_LENGTH], _email[MAX_NAME_LENGTH], _password[MAX_PASSWORD_LENGTH], _phone[MAX_NAME_LENGTH], _dateCreated[MAX_DATE_LENGTH], _lastUpdated[MAX_DATE_LENGTH], _lastLogin[MAX_DATE_LENGTH], _dateDeleted[MAX_DATE_LENGTH];

	if (sysData->userCount >= sysData->userCapacity)
	{
		size_t newCapacity = (sysData->userCapacity + 2) * 2;
		UserInfo *tempUserSize = realloc(sysData->users, sizeof(UserInfo) * newCapacity);
		if (!tempUserSize)
		{
			logPrintMessage(LOG_ERROR, "Failed to allocate memory for user data [ Falha ao alocar memória para os dados do usuário ]", yes);
			fclose(userFile);
			status = failed;
			return status;
		}
		sysData->users = tempUserSize;
		sysData->userCapacity = newCapacity;
	}

	sysData->userCount = 0;
	while (fscanf(userFile, "%d|%149[^|]|%149[^|]|%149[^|]|%299[^|]|%149[^|]|%d|%d|%99[^|]|%99[^|]|%99[^|]|%99[^|]|", &_userID, _name, _userName, _email, _password, _phone, &_roleID, &_userStatus, _dateCreated, _lastUpdated, _lastLogin, _dateDeleted) != EOF && sysData->userCount < sysData->userCapacity)
	{
		if (sysData->userCount >= sysData->userCapacity)
		{
			// resize the user capacity if necessary
			size_t newCapacity = (sysData->userCapacity + 2) * 2;
			UserInfo *tempUserSize = realloc(sysData->users, sizeof(UserInfo) * newCapacity);
			if (!tempUserSize)
			{
				logPrintMessage(LOG_ERROR, "Failed to allocate memory for user data [ Falha ao alocar memória para os dados do usuário ]", yes);
				fclose(userFile);
				status = failed;
				return status;
			}
			sysData->users = tempUserSize;
			sysData->userCapacity = newCapacity;
		}

		sysData->users[sysData->userCount].userID = _userID;
		sysData->users[sysData->userCount].name = strdup(_name);
		sysData->users[sysData->userCount].username = strdup(_userName);
		sysData->users[sysData->userCount].email = strdup(_email);
		sysData->users[sysData->userCount].password = strdup(_password);
		sysData->users[sysData->userCount].phone = strdup(_phone);
		sysData->users[sysData->userCount].roleID = _roleID;
		sysData->users[sysData->userCount].userStatus = _userStatus;
		sysData->users[sysData->userCount].dateCreated = strdup(_dateCreated);
		sysData->users[sysData->userCount].lastUpdated = strdup(_lastUpdated);
		sysData->users[sysData->userCount].lastLogin = strdup(_lastLogin);
		sysData->users[sysData->userCount].dateDeleted = strdup(_dateDeleted);

		sysData->userCount++;
	}
	if (sysData->userCount == 0)
	{
		logPrintMessage(LOG_ERROR, "Unable to load user data because user data is empty [ Nao foi possivel carregar os dados do usuário pois os dados estao vazios ]", yes);
		status = failed;
		return status;
	}
	fclose(userFile);
	logPrintMessage(LOG_SUCCESS, "User data loaded successfully [ Dados do usuário carregados com sucesso ]", yes);
	status = successful;
	return status;
}

StatusInfo freeUserDataVariable(char *name, char *username, char *email, char *password, char *phone, char *dateCreated, char *lastUpdated, char *lastLogin, char *dateDeleted)
{
	free(name);
	free(username);
	free(email);
	free(password);
	free(phone);
	free(dateCreated);
	free(lastUpdated);
	free(lastLogin);
	free(dateDeleted);
	return successful;
}
StatusInfo freeUserData(SystemData *sysData)
{
	free(sysData->users[sysData->userCount].name);
	free(sysData->users[sysData->userCount].username);
	free(sysData->users[sysData->userCount].email);
	free(sysData->users[sysData->userCount].password);
	free(sysData->users[sysData->userCount].phone);
	free(sysData->users[sysData->userCount].dateCreated);
	free(sysData->users[sysData->userCount].lastUpdated);
	free(sysData->users[sysData->userCount].lastLogin);
	free(sysData->users[sysData->userCount].dateDeleted);
	return successful;
}
StatusInfo freeMemoryAllocatedToUserStructure(SystemData *sysData)
{
	StatusInfo status;

	if (!sysData)
	{
		logPrintMessage(LOG_ERROR, "System data is Null. Failed to free memory allocated to user structure [ Dados do sistema nulo. Falha ao liberar memória alocada para a estrutura do usuário ]", yes);
		status = failed;
		return status;
	}
	if (!sysData->users)
	{
		logPrintMessage(LOG_ERROR, "User data is Null. Failed to free memory allocated to user structure [ Dados do usuário nulo. Falha ao liberar memória alocada para a estrutura do usuário ]", yes);
		status = failed;
		return status;
	}
	for (size_t i = 0; i < sysData->userCount; i++)
	{
		free(sysData->users[i].name);
		free(sysData->users[i].username);
		free(sysData->users[i].email);
		free(sysData->users[i].password);
		free(sysData->users[i].phone);
		free(sysData->users[i].dateCreated);
		free(sysData->users[i].lastUpdated);
		free(sysData->users[i].lastLogin);
		free(sysData->users[i].dateDeleted);
	}
	free(sysData->users);
	status = successful;
	return status;
}

StatusInfo updateUser(SystemData *sysData, size_t userIndex, int choice, char *now, StatusInfo updated, StatusInfo status)
{
	int goBack = sysData->appContext->goBack;
	status = status;
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
		scanf("%149[^\n]", name);
		clearInputBuffer();
		strcpy(sysData->users[userIndex].name, name);
		strcpy(sysData->users[userIndex].lastUpdated, now);
		updated = saveSystemData(sysData);
		status = successful;
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
		status = successful;
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
		status = successful;
		// free(email);
		// free(now);
		viewSingleUser(sysData, userIndex);
		break;
	case 4:
		char *password = (char *)malloc(MAX_PASSWORD_LENGTH * sizeof(char));

		printf("User Password to update %.10s... [Senha de usuário para atualizar %.10s...]\n", sysData->users[userIndex].password, sysData->users[userIndex].password);
		if (!password)
		{
			logPrintMessage(LOG_ERROR, "Failed to allocate memory for password update [Falha ao alocar memória]", yes);
			free(password);
			return failed;
		}

		printf("Enter New User Password [Digite a nova senha do usuário]: ");
		clearInputBuffer();
		// scanf("%299[^\n]", password);
		scanf("%s", password);
		char *hashedPWD = hashPassword(password);
		strcpy(sysData->users[userIndex].password, hashedPWD);
		strcpy(sysData->users[userIndex].lastUpdated, now);
		updated = saveSystemData(sysData);
		status = successful;
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
		status = successful;
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
		status = successful;
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
		status = successful;
		break;
	default:
		logPrintMessage(LOG_WARNING, "Invalid Input [Entrada Invalida]", yes);
		updated = failed;
		status = failed;
		clearInputBuffer();
		// free(now);
		break;
	}
	return updated;
}
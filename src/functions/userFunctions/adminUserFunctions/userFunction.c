#include "../include/userFunction.h"
#include "../include/unicambio.h"
#include "../include/structures.h"
#include "../include/enum.h"
#include "../include/logger.h"
#include "../include/utilities.h"
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
			free(hashedPassword);
			status = failed;
			return status;
		}

		sysData->users[sysData->userCount].userID = userID;

		sysData->users[sysData->userCount].name = strdup(name);
		if (sysData->users[sysData->userCount].name == NULL)
		{
			logPrintMessage(LOG_ERROR, "Failed to save user name [ Falha ao salvar o nome do usuário ]", yes);
			status = failed;
			return status;
		}

		sysData->users[sysData->userCount].username = strdup(username);
		if (sysData->users[sysData->userCount].username == NULL)
		{
			logPrintMessage(LOG_ERROR, "Failed to save user username [ Falha ao salvar o username do usuário ]", yes);
			status = failed;
			free(sysData->users[sysData->userCount].name);
			return status;
		}

		sysData->users[sysData->userCount].email = strdup(email);
		if (sysData->users[sysData->userCount].email == NULL)
		{
			logPrintMessage(LOG_ERROR, "Failed to save user email [ Falha ao salvar o email do usuário ]", yes);
			status = failed;
			free(sysData->users[sysData->userCount].username);
			free(sysData->users[sysData->userCount].name);
			return status;
		}
		sysData->users[sysData->userCount].password = hashedPassword;
		if (sysData->users[sysData->userCount].password == NULL)
		{
			logPrintMessage(LOG_ERROR, "Failed to save user password [ Falha ao salvar a senha do usuário ]", yes);
			status = failed;
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].username);
			free(sysData->users[sysData->userCount].name);
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
	if (!sysData)
	{
		logPrintMessage(LOG_ERROR, "System data is Null. Failed to save user data [ Dados do sistema nulo. Falha ao salvar dados do usuário ]", yes);
		return failed;
	}
	FILE *userFile = fopen(USER_DATA_FILE_PATH, "w");
	if (!userFile)
	{
		logPrintMessage(LOG_ERROR, "Failed to open user data file [ Falha ao abrir o arquivo de dados do usuário ]", yes);
		return failed;
	}
	if (sysData->userCount == 0)
	{
		logPrintMessage(LOG_INFO, "There is no new user to save [ Nao houve nenhum novo usuário para salvar ]", yes);
		fclose(userFile);
		return successful;
	}

	for (size_t i = 0; i < sysData->userCount; i++)
	{
		fprintf(userFile, "%d|%s|%s|%s|%s|%s|%d|%d|%s|%s|%s|%s|\n", sysData->users[i].userID, sysData->users[i].name, sysData->users[i].username, sysData->users[i].email, sysData->users[i].password, sysData->users[i].phone, sysData->users[i].roleID, sysData->users[i].userStatus, sysData->users[i].dateCreated, sysData->users[i].lastUpdated, sysData->users[i].lastLogin, sysData->users[i].dateDeleted);
	}
	if (fclose(userFile) != 0)
	{
		logPrintMessage(LOG_ERROR, "Failed to close user data file [ Falha ao fechar o arquivo de dados do usuário ]", yes);
		return failed;
	}
	logPrintMessage(LOG_SUCCESS, "User data saved successfully [ Dados do usuário salvos com sucesso ]", yes);
	return successful;
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

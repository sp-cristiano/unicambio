#include "../include/unicambio.h"
#include "../include/userFunctions.h"
#include "../include/structures.h"
#include "../include/messages.h"
#include "../include/logger.h"
#include "../include/utilities.h"
#include "../include/oauth.h"

void createUser(SystemData *sysData, char *name, char *userName, char *email, char *password, char *phone, int roleID, int userStatus, char *createAt, char *lastSeen, char *deleteAt)
{
	// check if sysData pointer is valid [Verifique se o ponteiro sysData é válido]
	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		sleep(MID_SLEEP);
		return;
	}
	if (sysData->appContext == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_APP_CONTEXT_IS_NULL);
		sleep(MID_SLEEP);
		return;
	}
	if (userStatus == active)
	{

		// check if user capacity need adjustment [Verifique se a capacidade de usuário precisa de ajuste]

		if (sysData->userCount >= sysData->userCapacity)
		{
			size_t newCapacity = (sysData->userCapacity + 2) * 2;
			UserInfo *tempUserSize = realloc(sysData->users, sizeof(UserInfo) * newCapacity);
			if (!tempUserSize)
			{
				logMessages(LOG_ERROR, "Error allocating memory to create user [Erro ao alocar memória para criar usuário]\n");
				centerStringOnly("Error allocating memory to create user [Erro ao alocar memória para criar usuário]\n");
				sleep(MID_SLEEP);
				return;
			}
			sysData->users = tempUserSize;
			sysData->userCapacity = newCapacity;
		}

		int userID = randomNumber(1000, 9999); // Generate random userID [Gere um ID de usuário aleatório]

		if (sysData->users != NULL && sysData->userCount > 0)
		{

			// check if user already exists [Verifique se o usuário já existe]
			for (size_t i = 0; i < sysData->userCount; i++)
			{
				if (sysData->users[i].userID == userID)
				{
					userID = randomNumber(1000, 9999); // Generate random userID [Gere um ID de usuário aleatório]
					i = 0;														 // restart the loop [reinicie o loop]
				}
				if ((sysData->users[i].email && strcmp(sysData->users[i].email, email) == 0) || (sysData->users[i].userName && strcmp(sysData->users[i].userName, userName) == 0) || (sysData->users[i].phone && strcmp(sysData->users[i].phone, phone) == 0))
				{
					logMessages(LOG_ERROR, UI_ERROR_USER_EXISTS);
					centerStringOnly(UI_ERROR_USER_EXISTS);
					sleep(MID_SLEEP);
					return;
				}
			}
		}

		// Allocate memory for user data and copy strings for new user data. [Aloque memória para dados de usuário e copie strings para os dados de usuário novo.]

		sysData->users[sysData->userCount].userID = userID;

		sysData->users[sysData->userCount].name = strdup(name);
		if (!sysData->users[sysData->userCount].name)
		{
			logMessages(LOG_ERROR, "Error allocating memory for user name [Erro ao alocar memória para o nome do usuário].\n");
			return;
		}
		sysData->users[sysData->userCount].userName = strdup(userName);
		if (!sysData->users[sysData->userCount].userName)
		{
			logMessages(LOG_ERROR, "Error allocating memory for user username [Erro ao alocar memória para o nome do usuário].\n");
			free(sysData->users[sysData->userCount].name);
			return;
		}
		sysData->users[sysData->userCount].email = strdup(email);
		if (!sysData->users[sysData->userCount].email)
		{
			logMessages(LOG_ERROR, "Error allocating memory for user email [Erro ao alocar memória para o email do usuário].\n");
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			return;
		}

		sysData->users[sysData->userCount].password = strdup(hashPassword(password)); // Hash password [Hashe a senha]
		if (!sysData->users[sysData->userCount].password)
		{
			logMessages(LOG_ERROR, "Error hashing password and allocating it to user [Erro ao hashear a senha e alocar para o usuário].\n");
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			free(password);
			return;
		}

		sysData->users[sysData->userCount].phone = strdup(phone);
		if (!sysData->users[sysData->userCount].phone)
		{
			logMessages(LOG_ERROR, "Error allocating memory for user phone [Erro ao alocar memória para o telefone do usuário].\n");
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].password);
			free(password);
			// logAndFreeUser(sysData, sysData->userCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}
		sysData->users[sysData->userCount].roleID = roleID;
		sysData->users[sysData->userCount].userStatus = userStatus;
		sysData->users[sysData->userCount].createAt = strdup(createAt);
		if (!sysData->users[sysData->userCount].createAt)
		{
			logMessages(LOG_ERROR, "Error allocating memory for user createAt [Erro ao alocar memória para o createAt do usuário].\n");
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].password);
			free(sysData->users[sysData->userCount].phone);
			free(password);
			return;
		}
		sysData->users[sysData->userCount].lastSeen = strdup(lastSeen);
		if (!sysData->users[sysData->userCount].lastSeen)
		{
			logMessages(LOG_ERROR, "Error allocating memory for user lastSeen [Erro ao alocar memória para o lastSeen do usuário].\n");
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].password);
			free(sysData->users[sysData->userCount].phone);
			free(sysData->users[sysData->userCount].createAt);
			free(password);
			return;
		}
		if (deleteAt != NULL)
		{
			sysData->users[sysData->userCount].deleteAt = strdup(deleteAt);
		}
		else
		{
			sysData->users[sysData->userCount].deleteAt = strdup(" ");
		}
		if (!sysData->users[sysData->userCount].deleteAt)
		{
			logMessages(LOG_ERROR, "Error allocating memory for user deleteAt [Erro ao alocar memória para o deleteAt do usuário].\n");
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].password);
			free(sysData->users[sysData->userCount].phone);
			free(sysData->users[sysData->userCount].createAt);
			free(sysData->users[sysData->userCount].lastSeen);
			free(password);
			// logAndFreeUser(sysData, sysData->userCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}
		// free(hashedPwd);
		sysData->userCount++; // Increase user count [Aumente o contador de usuários
		saveUserData(sysData);
	}
	else
	{
		logMessages(LOG_ERROR, UI_ERROR_USER_DATA_STATUS_NOT_ACTIVE);
		centerStringOnly(UI_ERROR_USER_DATA_STATUS_NOT_ACTIVE);
		sleep(MID_SLEEP);
	}
	return;
}

// Save User Data to file
void saveUserData(SystemData *sysData)
{
	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		centerStringOnly(UI_ERROR_SYSTEM_DATA_IS_NULL);
		sleep(MID_SLEEP);
		return;
	}

	FILE *usersFile = fopen(USER_DATA_FILE_PATH, "w");
	if (usersFile == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_USER_DATA_FILE_NOT_FOUND);
		centerStringOnly(UI_ERROR_USER_DATA_FILE_NOT_FOUND);
		sleep(MID_SLEEP);
		return;
	}
	if (sysData->userCount == 0)
	{
		logMessages(LOG_INFO, "There are no users to save [Não há usuários para salvar].");
		sleep(MID_SLEEP);
		fclose(usersFile);
		return;
	}

	for (size_t i = 0; i < sysData->userCount; i++)
	{
		fprintf(usersFile, "%d|%s|%s|%s|%s|%s|%d|%d|%s|%s|%s\n", sysData->users[i].userID, sysData->users[i].name, sysData->users[i].userName, sysData->users[i].email, sysData->users[i].password, sysData->users[i].phone, sysData->users[i].roleID, sysData->users[i].userStatus, sysData->users[i].createAt, sysData->users[i].lastSeen, sysData->users[i].deleteAt);
	}
	if (fclose(usersFile))
	{
		logMessages(LOG_ERROR, "Error closing user data file [Erro ao fechar o arquivo de dados de usuário].\n");
		sleep(MID_SLEEP);
		return;
	}
	else
	{
		logMessages(LOG_INFO, "User data saved successfully [Dados de usuário salvos com sucesso].\n");
		sleep(MID_SLEEP);
	}
}

// Load User Data to The structured User Database from the database file. [Carregue os dados de usuários estruturados no banco de dados do arquivo de banco de dados.]
void loadUserData(SystemData *sysData)
{
	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		centerStringOnly(UI_ERROR_SYSTEM_DATA_IS_NULL);
		sleep(MID_SLEEP);
		return;
	}

	FILE *usersFile = fopen(USER_DATA_FILE_PATH, "r");
	if (usersFile == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_USER_DATA_FILE_NOT_FOUND);
		centerStringOnly(UI_ERROR_USER_DATA_FILE_NOT_FOUND);
		sleep(MID_SLEEP);
		return;
	}
	// initialize variables for reading data
	int _userID, _roleID, _userStatus;
	char _name[MAX_NAME_LENGTH], _userName[MAX_NAME_LENGTH], _email[MAX_NAME_LENGTH], _password[MAX_PASSWORD_LENGTH], _phone[MAX_NAME_LENGTH], _createAt[MAX_DATE_LENGTH], _lastSeen[MAX_DATE_LENGTH], _deleteAt[MAX_DATE_LENGTH];

	// adjust user capacity if needed.
	if (sysData->userCount >= sysData->userCapacity)
	{
		size_t newCapacity = (sysData->userCapacity + 2) * 2;
		UserInfo *tempUserSize = realloc(sysData->users, sizeof(UserInfo) * newCapacity);
		if (!tempUserSize)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			sleep(MID_SLEEP);
			return;
		}
		sysData->users = tempUserSize;
		sysData->userCapacity = newCapacity;
	}

	// initializing sysData->userCount to 0
	sysData->userCount = 0;

	// Read data from file [Leia dados do arquivo]

	while (fscanf(usersFile, "%d|%149[^|]|%149[^|]|%149[^|]|%299[^|]|%149[^|]|%d|%d|%99[^|]|%99[^|]|%99[^|]\n", &_userID, _name, _userName, _email, _password, _phone, &_roleID, &_userStatus, _createAt, _lastSeen, _deleteAt) != EOF && sysData->userCount < sysData->userCapacity)
	{
		// Check if userCount exceeds userCapacity
		if (sysData->userCount >= sysData->userCapacity)
		{
			// resize the user capacity if necessary
			size_t newCapacity = (sysData->userCapacity + 2) * 2;
			UserInfo *tempUserSize = realloc(sysData->users, sizeof(UserInfo) * newCapacity);
			if (!tempUserSize)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
				sleep(MID_SLEEP);
				return;
			}
			sysData->users = tempUserSize;
			sysData->userCapacity = newCapacity;
		}

		// Add user to database
		sysData->users[sysData->userCount].userID = _userID;

		sysData->users[sysData->userCount].name = strdup(_name);
		if (!sysData->users[sysData->userCount].name)
		{
			logMessages(LOG_ERROR, "Error allocating Memory for user name in loadUserData [Erro ao alocar memória para o nome do usuário na função loadUserData]");
			return;
		}
		sysData->users[sysData->userCount].userName = strdup(_userName);
		if (!sysData->users[sysData->userCount].userName)
		{
			logMessages(LOG_ERROR, "Error allocating Memory for user username in loadUserData [Erro ao alocar memória para o nome do usuário na função loadUserData]");
			free(sysData->users[sysData->userCount].name);
			return;
		}

		sysData->users[sysData->userCount].email = strdup(_email);
		if (!sysData->users[sysData->userCount].email)
		{
			logMessages(LOG_ERROR, "Error allocating Memory for user email in loadUserData [Erro ao alocar memória para o email do usuário na função loadUserData]");
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			return;
		}

		sysData->users[sysData->userCount].password = strdup(_password);
		if (!sysData->users[sysData->userCount].password)
		{
			logMessages(LOG_ERROR, "Error allocating Memory for user password in loadUserData [Erro ao alocar memória para a senha do usuário na função loadUserData]");
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			return;
		}

		sysData->users[sysData->userCount].phone = strdup(_phone);
		if (!sysData->users[sysData->userCount].phone)
		{
			logMessages(LOG_ERROR, "Error allocating Memory for user phone in loadUserData [Erro ao alocar memória para o telefone do usuário na função loadUserData]");
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].password);
			return;
		}

		sysData->users[sysData->userCount].roleID = _roleID;

		sysData->users[sysData->userCount].userStatus = _userStatus;

		sysData->users[sysData->userCount].createAt = strdup(_createAt);
		if (!sysData->users[sysData->userCount].createAt)
		{
			logMessages(LOG_ERROR, "Error allocating Memory for user createAt in loadUserData [Erro ao alocar memória para o createAt do usuário na função loadUserData]");
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].password);
			free(sysData->users[sysData->userCount].phone);
			// logAndFreeUser(sysData, sysData->userCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}

		sysData->users[sysData->userCount].lastSeen = strdup(_lastSeen);
		if (!sysData->users[sysData->userCount].lastSeen)
		{
			logMessages(LOG_ERROR, "Error allocating Memory for user lastSeen in loadUserData [Erro ao alocar memória para o lastSeen do usuário na função loadUserData]");
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].password);
			free(sysData->users[sysData->userCount].phone);
			free(sysData->users[sysData->userCount].createAt);
			// logAndFreeUser(sysData, sysData->userCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}

		sysData->users[sysData->userCount].deleteAt = strdup(_deleteAt);
		if (!sysData->users[sysData->userCount].deleteAt)
		{
			logMessages(LOG_ERROR, "Error allocating Memory for user deleteAt in loadUserData [Erro ao alocar memória para o deleteAt do usuário na função loadUserData]");
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].password);
			free(sysData->users[sysData->userCount].phone);
			free(sysData->users[sysData->userCount].createAt);
			free(sysData->users[sysData->userCount].lastSeen);
			// logAndFreeUser(sysData, sysData->userCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}
		sysData->userCount++;
	}

	// check for emptyfile scenerio
	if (sysData->userCount == 0)
	{
		logMessages(LOG_ERROR, UI_ERROR_USER_DATA_IS_EMPTY);
		centerStringOnly(UI_ERROR_USER_DATA_IS_EMPTY);
		sleep(MID_SLEEP);
		return;
	}
	if (ferror(usersFile))
	{
		logMessages(LOG_ERROR, UI_ERROR_USER_DATA_FILE_READ_ERROR);
		centerStringOnly(UI_ERROR_USER_DATA_FILE_READ_ERROR);
		sleep(MID_SLEEP);
		return;
	}
	fclose(usersFile);
}

// Free User Data
void freeUserData(char *name, char *userName, char *email, char *password, char *phone, char *createAt, char *lastSeen, char *deleteAt)
{
	free(name);
	free(userName);
	free(email);
	free(password);
	free(phone);
	free(createAt);
	free(lastSeen);
	free(deleteAt);
}
void freeMemoryAllocatedToUserStructure(SystemData *sysData)
{

	if (sysData == NULL || sysData->users == NULL)
	{
		return;
	}
	for (size_t i = 0; i < sysData->userCount; i++)
	{
		free(sysData->users[i].name);
		free(sysData->users[i].userName);
		free(sysData->users[i].email);
		free(sysData->users[i].password);
		free(sysData->users[i].phone);
		free(sysData->users[i].createAt);
		free(sysData->users[i].lastSeen);
		free(sysData->users[i].deleteAt);
	}
	free(sysData->users);
	sysData->users = NULL;
	sysData->userCount = 0;
	sysData->userCapacity = 0;
}

// TODO: DELETE THIS logAndFreeUser LATER
void logAndFreeUser(SystemData *sysData, size_t index, const char *message)
{
	logMessages(LOG_ERROR, message);
	safefree(sysData->users[index].name);
	safefree(sysData->users[index].userName);
	safefree(sysData->users[index].email);
	safefree(sysData->users[index].password);
	safefree(sysData->users[index].phone);
	safefree(sysData->users[index].createAt);
	safefree(sysData->users[index].lastSeen);
	safefree(sysData->users[index].deleteAt);
	sleep(MID_SLEEP);
}
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
		centerStringOnly(UI_ERROR_SYSTEM_DATA_IS_NULL);
		sleep(MID_SLEEP);
		return;
	}

	// check if sysData->appContext pointer is valid [Verifique se o ponteiro sysData->appContext é válido]
	if (sysData->appContext == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_APP_CONTEXT_IS_NULL);
		centerStringOnly(UI_ERROR_APP_CONTEXT_IS_NULL);
		sleep(MID_SLEEP);
		return;
	}
	if (userStatus == active)
	{

		// check if user capacity need adjustment [Verifique se a capacidade de usuário precisa de ajuste]
		if (sysData->userCapacity == 0)
		{
			sysData->userCapacity = 2;
		}
		else if (sysData->userCount >= sysData->userCapacity)
		{
			sysData->userCapacity = (sysData->userCapacity + 2) * 2;
		}
		// reallocate memory to the user structure.
		UserInfo *tempUserSize = realloc(sysData->users, sizeof(UserInfo) * sysData->userCapacity);
		if (tempUserSize == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			sleep(MID_SLEEP);
			return;
		}
		sysData->users = tempUserSize;

		int userID = randomNumber(1000, 9999); // Generate random userID [Gere um ID de usuário aleatório]

		// check if user already exists [Verifique se o usuário já existe]
		for (size_t i = 0; i < sysData->userCount; i++)
		{
			if (sysData->users[i].userID == userID)
			{
				userID = randomNumber(1000, 9999); // Generate random userID [Gere um ID de usuário aleatório]
				i = -1;														 // restart the loop [reinicie o loop]
			}
			if (sysData->users[i].email == email || sysData->users[i].userName == userName || sysData->users[i].phone == phone)
			{
				logMessages(LOG_ERROR, UI_ERROR_USER_EXISTS);
				centerStringOnly(UI_ERROR_USER_EXISTS);
				sleep(MID_SLEEP);
				return;
			}
		}

		// Allocate memory for user data and copy strings for new user data. [Aloque memória para dados de usuário e copie strings para os dados de usuário novo.]

		sysData->users[sysData->userCount].userID = userID;

		sysData->users[sysData->userCount].name = strdup(name);
		if (sysData->users[sysData->userCount].name == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			sleep(MID_SLEEP);
			return;
		}
		sysData->users[sysData->userCount].userName = strdup(userName);
		if (sysData->users[sysData->userCount].userName == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			free(sysData->users[sysData->userCount].name);
			sleep(MID_SLEEP);
			return;
		}
		sysData->users[sysData->userCount].email = strdup(email);
		if (sysData->users[sysData->userCount].email == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			sleep(MID_SLEEP);
			return;
		}
		char *hashedPwd = hashPassword(password); // Hash password [Hashe a senha]

		sysData->users[sysData->userCount].password = strdup(hashedPwd);
		if (sysData->users[sysData->userCount].password == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			sleep(MID_SLEEP);
			return;
		}
		sysData->users[sysData->userCount].phone = strdup(phone);
		if (sysData->users[sysData->userCount].phone == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].password);
			sleep(MID_SLEEP);
			return;
		}
		sysData->users[sysData->userCount].roleID = roleID;
		sysData->users[sysData->userCount].userStatus = userStatus;
		sysData->users[sysData->userCount].createAt = strdup(createAt);
		if (sysData->users[sysData->userCount].createAt == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].password);
			free(sysData->users[sysData->userCount].phone);
			sleep(MID_SLEEP);
			return;
		}
		sysData->users[sysData->userCount].lastSeen = strdup(lastSeen);
		if (sysData->users[sysData->userCount].lastSeen == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].password);
			free(sysData->users[sysData->userCount].phone);
			free(sysData->users[sysData->userCount].createAt);
			sleep(MID_SLEEP);
			return;
		}
		if (deleteAt == NULL)
		{
			deleteAt = " ";
			sysData->users[sysData->userCount].deleteAt = strdup(deleteAt);
			if (sysData->users[sysData->userCount].deleteAt == NULL)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
				free(sysData->users[sysData->userCount].name);
				free(sysData->users[sysData->userCount].userName);
				free(sysData->users[sysData->userCount].email);
				free(sysData->users[sysData->userCount].password);
				free(sysData->users[sysData->userCount].phone);
				free(sysData->users[sysData->userCount].createAt);
				free(sysData->users[sysData->userCount].lastSeen);
				sleep(MID_SLEEP);
				return;
			}
		}
		else
		{
			sysData->users[sysData->userCount].deleteAt = strdup(deleteAt);
			if (sysData->users[sysData->userCount].deleteAt == NULL)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
				free(sysData->users[sysData->userCount].name);
				free(sysData->users[sysData->userCount].userName);
				free(sysData->users[sysData->userCount].email);
				free(sysData->users[sysData->userCount].password);
				free(sysData->users[sysData->userCount].phone);
				free(sysData->users[sysData->userCount].createAt);
				free(sysData->users[sysData->userCount].lastSeen);
				sleep(MID_SLEEP);
			}
		}
		sysData->userCount++; // Increase user count [Aumente o contador de usuários
		saveUserData(sysData);
	}
	else
	{
		logMessages(LOG_ERROR, UI_ERROR_USER_DATA_STATUS_NOT_ACTIVE);
		centerStringOnly(UI_ERROR_USER_DATA_STATUS_NOT_ACTIVE);
		sleep(MID_SLEEP);
		return;
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
	for (size_t i = 0; i < sysData->userCount; i++)
	{
		fprintf(usersFile, "%d|%s|%s|%s|%s|%s|%d|%d|%s|%s|%s\n", sysData->users[i].userID, sysData->users[i].name, sysData->users[i].userName, sysData->users[i].email, sysData->users[i].password, sysData->users[i].phone, sysData->users[i].roleID, sysData->users[i].userStatus, sysData->users[i].createAt, sysData->users[i].lastSeen, sysData->users[i].deleteAt);
	}
	fclose(usersFile);
	return;
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
	char _name[MAX_NAME_LENGTH], _userName[MAX_NAME_LENGTH], _email[MAX_NAME_LENGTH], _password[MAX_PASSWORD_LENGTH], _phone[MAX_NAME_LENGTH], _createAt[MAX_DATE_LENGTH], _lastSeen[MAX_DATE_LENGTH], _deletedAt[MAX_DATE_LENGTH];

	// adjust user capacity if needed.
	if (sysData->userCapacity == 0)
	{
		sysData->userCapacity = 2;
	}
	else
	{
		sysData->userCapacity = (sysData->userCapacity + 2) * 2;
	}

	// Reallocate memory to userinfo structure
	UserInfo *tempUserSize = realloc(sysData->users, sizeof(UserInfo) * sysData->userCapacity);
	if (tempUserSize == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
		centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
		sleep(MID_SLEEP);
		return;
	}
	// assigning tempUserSize to sysData->users
	sysData->users = tempUserSize;

	// initializing sysData->userCount to 0
	sysData->userCount = 0;

	// Read data from file [Leia dados do arquivo]

	while (fscanf(usersFile, "%d|%149[^|]|%149[^|]|%149[^|]|%299[^|]|%149[^|]|%d|%d|%99[^|]|%99[^|]|%99[^|]\n", &_userID, _name, _userName, _email, _password, _phone, &_roleID, &_userStatus, _createAt, _lastSeen, _deletedAt) != EOF && sysData->userCount < sysData->userCapacity)
	{
		// Check if userCount exceeds userCapacity
		if (sysData->userCount >= sysData->userCapacity)
		{
			// resize the user capacity if necessary
			sysData->userCapacity = (sysData->userCapacity + 2) * 2;
			tempUserSize = realloc(sysData->users, sizeof(UserInfo) * sysData->userCapacity);
			if (tempUserSize == NULL)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
				sleep(MID_SLEEP);
				return;
			}
			sysData->users = tempUserSize;
		}

		// Add user to database
		sysData->users[sysData->userCount].userID = _userID;

		sysData->users[sysData->userCount].name = strdup(_name);
		if (sysData->users[sysData->userCount].name == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			sleep(MID_SLEEP);
			return;
		}

		sysData->users[sysData->userCount].userName = strdup(_userName);
		if (sysData->users[sysData->userCount].userName == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			free(sysData->users[sysData->userCount].name);
			sleep(MID_SLEEP);
			return;
		}
		sysData->users[sysData->userCount].email = strdup(_email);
		if (sysData->users[sysData->userCount].email == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			sleep(MID_SLEEP);
			return;
		}
		sysData->users[sysData->userCount].password = strdup(_password);
		if (sysData->users[sysData->userCount].password == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			sleep(MID_SLEEP);
			return;
		}
		sysData->users[sysData->userCount].phone = strdup(_phone);
		if (sysData->users[sysData->userCount].phone == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].password);
			sleep(MID_SLEEP);
			return;
		}
		sysData->users[sysData->userCount].roleID = _roleID;
		sysData->users[sysData->userCount].userStatus = _userStatus;
		sysData->users[sysData->userCount].createAt = strdup(_createAt);
		if (sysData->users[sysData->userCount].createAt == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].password);
			free(sysData->users[sysData->userCount].phone);
			sleep(MID_SLEEP);
			return;
		}
		sysData->users[sysData->userCount].lastSeen = strdup(_lastSeen);
		if (sysData->users[sysData->userCount].lastSeen == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			free(sysData->users[sysData->userCount].name);
			free(sysData->users[sysData->userCount].userName);
			free(sysData->users[sysData->userCount].email);
			free(sysData->users[sysData->userCount].password);
			free(sysData->users[sysData->userCount].phone);
			free(sysData->users[sysData->userCount].createAt);
			sleep(MID_SLEEP);
			return;
		}

		sysData->users[sysData->userCount].deleteAt = strdup(_deletedAt);

		if (sysData->users[sysData->userCount].deleteAt == NULL)
		{
			strcpy(_deletedAt, " ");

			sysData->users[sysData->userCount].deleteAt = strdup(_deletedAt);

			if (sysData->users[sysData->userCount].deleteAt == NULL)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
				free(sysData->users[sysData->userCount].name);
				free(sysData->users[sysData->userCount].userName);
				free(sysData->users[sysData->userCount].email);
				free(sysData->users[sysData->userCount].password);
				free(sysData->users[sysData->userCount].phone);
				free(sysData->users[sysData->userCount].createAt);
				free(sysData->users[sysData->userCount].lastSeen);
				sleep(MID_SLEEP);
			}
		}
		else
		{
			sysData->users[sysData->userCount].deleteAt = strdup(_deletedAt);
			if (sysData->users[sysData->userCount].deleteAt == NULL)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
				free(sysData->users[sysData->userCount].name);
				free(sysData->users[sysData->userCount].userName);
				free(sysData->users[sysData->userCount].email);
				free(sysData->users[sysData->userCount].password);
				free(sysData->users[sysData->userCount].phone);
				free(sysData->users[sysData->userCount].createAt);
				free(sysData->users[sysData->userCount].lastSeen);
				sleep(MID_SLEEP);
				return;
			}
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
	// check for potential format errors

	if (feof(usersFile))
	{
		logMessages(LOG_ERROR, UI_ERROR_USER_DATA_FILE_FORMAT_ERROR);
		centerStringOnly(UI_ERROR_USER_DATA_FILE_FORMAT_ERROR);
		sleep(MID_SLEEP);
		return;
	}
	else if (ferror(usersFile))
	{
		logMessages(LOG_ERROR, UI_ERROR_USER_DATA_FILE_READ_ERROR);
		centerStringOnly(UI_ERROR_USER_DATA_FILE_READ_ERROR);
		sleep(MID_SLEEP);
		return;
	}
	fclose(usersFile);
}

// Free User Data
void freeUserData(SystemData *sysData)
{
	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		centerStringOnly(UI_ERROR_SYSTEM_DATA_IS_NULL);
		sleep(MID_SLEEP);
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
}
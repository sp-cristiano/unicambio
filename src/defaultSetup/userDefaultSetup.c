#include "../include/unicambio.h"
#include "../include/userDefaultSetup.h"
#include "../include/messages.h"
#include "../include/logger.h"
#include "../include/structures.h"
#include "../include/utilities.h"
#include "../include/userFunctions.h"
#include "../include/createDB.h"

void createUserDefaultSetup(SystemData *sysData)
{
	FILE *checkUserFile = fopen(USER_DATA_FILE_PATH, "r");
	if (checkUserFile == NULL)
	{
		logMessages(LOG_WARNING, UI_ERROR_USER_DATA_FILE_NOT_FOUND);
		centerStringOnly(UI_ERROR_USER_DATA_FILE_NOT_FOUND);

		// create db file
		createUserDBFile();

		if (!sysData->appContext->ADMIN_USER_EMAIL || !sysData->appContext->ADMIN_USER_PASSWORD || !sysData->appContext->ADMIN_USER_PHONE)
		{
			logMessages(LOG_ERROR, "Admin default user data in app context is null [Dados do usuário administrador no contexto da aplicação é nulo]");
			centerStringOnly("Admin default user data in app context is null [Dados do usuário administrador no contexto da aplicação é nulo]");
			sleep(MID_SLEEP);
			return;
		}

		// allocate memory for default user data
		char *name = (char *)malloc(strlen(MAX_NAME_LENGTH) * sizeof(char));
		char *userName = (char *)malloc(strlen(MAX_NAME_LENGTH) * sizeof(char));
		char *email = (char *)malloc(strlen(MAX_NAME_LENGTH) * sizeof(char));
		char *password = (char *)malloc(strlen(MAX_PASSWORD_LENGTH) * sizeof(char));
		char *phone = (char *)malloc(strlen(MAX_NAME_LENGTH) * sizeof(char));
		char *createAt = (char *)malloc(strlen(MAX_DATE_LENGTH) * sizeof(char));
		char *lastSeen = (char *)malloc(strlen(MAX_DATE_LENGTH) * sizeof(char));
		char *deleteAt = (char *)malloc(strlen(MAX_DATE_LENGTH) * sizeof(char));

		if (name == NULL || userName == NULL || email == NULL || password == NULL || phone == NULL || createAt == NULL || lastSeen == NULL || deleteAt == NULL)
		{
			logMessages(LOG_ERROR, "Memory allocation  for default user data failed [Erro alocando memória para os dados do usuário padrão]");
			centerStringOnly("Memory allocation  for default user data failed [Erro alocando memória para os dados do usuário padrão]");
			freeUserData(name, userName, email, password, phone, createAt, lastSeen, deleteAt);
			sleep(MID_SLEEP);
			return;
		}

		// Initialize user data
		strncpy(name, DEFAULT_ADMIN_NAME, MAX_NAME_LENGTH - 1);
		name[MAX_NAME_LENGTH - 1] = '\0';

		strncpy(userName, DEFAULT_ADMIN_USERNAME, MAX_NAME_LENGTH - 1);
		userName[MAX_NAME_LENGTH - 1] = '\0';

		strncpy(email, sysData->appContext->ADMIN_USER_EMAIL, MAX_NAME_LENGTH - 1);
		email[MAX_NAME_LENGTH - 1] = '\0';

		strncpy(password, sysData->appContext->ADMIN_USER_PASSWORD, MAX_PASSWORD_LENGTH - 1);
		password[MAX_PASSWORD_LENGTH - 1] = '\0';

		strncpy(phone, sysData->appContext->ADMIN_USER_PHONE, MAX_NAME_LENGTH - 1);
		phone[MAX_NAME_LENGTH - 1] = '\0';

		int roleID = ROLE_ADMIN;

		int userStatus = active;

		strncpy(createAt, getCurrentDateTime(TYPE_DATE_TIME), MAX_DATE_LENGTH - 1);
		createAt[MAX_DATE_LENGTH - 1] = '\0';

		strncpy(lastSeen, getCurrentDateTime(TYPE_DATE_TIME), MAX_DATE_LENGTH - 1);
		lastSeen[MAX_DATE_LENGTH - 1] = '\0';

		strncpy(deleteAt, NULL, MAX_DATE_LENGTH - 1);
		deleteAt[MAX_DATE_LENGTH - 1] = '\0';

		createUser(sysData, name, userName, email, password, phone, roleID, userStatus, createAt, lastSeen, deleteAt);

		freeUserData(name, userName, email, password, phone, createAt, lastSeen, deleteAt);
	}
	else
	{

		fclose(checkUserFile);
	}
}
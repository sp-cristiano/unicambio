#include "../include/unicambio.h"
#include "../include/structures.h"
#include "../include/enum.h"
#include "../include/logger.h"
#include "../include/utilities.h"
#include "../include/userDefaultSetup.h"
#include "../include/userFunction.h"
#include "../include/createDB.h"

StatusInfo createUserDefaultSetup(SystemData *sysData)
{
	StatusInfo status;

	FILE *checkUserFile = fopen(USER_DATA_FILE_PATH, "r");
	if (!checkUserFile)
	{
		printf("\n\n");
		logPrintMessage(LOG_WARNING, "User database file not found [ Arquivo de dados do usuário nao encontrado ]", yes);
		logPrintMessage(LOG_INFO, "Creating user database file [ Criando arquivo de dados do usuário ]", yes);

		processing();

		status = createUserDBFile();
		if (status == failed)
		{
			printf("\n\n");
			logPrintMessage(LOG_ERROR, "Failed to create user database file [ Falha ao criar o arquivo de dados do usuário ]", yes);
			return status;
		}

		if (!sysData->appContext->adminUserEmail || !sysData->appContext->adminUserPassword || !sysData->appContext->adminUserPhone)
		{
			printf("\n\n");
			logPrintMessage(LOG_ERROR, "Admin default user data in app context is empty [ Dados padrão do usuário admin no contexto da aplicação estao vazios ]", yes);
			status = failed;
			return status;
		}

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
			printf("\n\n");
			logPrintMessage(LOG_ERROR, "Memory allocation for user default data failed [ Alocacao de memoria falhou para os dados padrão do usuário ]", yes);
			freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
			status = failed;
			return status;
		}

		char *now = getCurrentDateTime(TYPE_DATE);

		if (!now)
		{
			printf("\n\n");
			logPrintMessage(LOG_ERROR, "Failed to get current date and time [ Falha ao obter a data e hora atual ]", yes);
			freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
			free(now);
			status = failed;
			return status;
		}

		strncpy(name, DEFAULT_ADMIN_NAME, MAX_NAME_LENGTH - 1);
		name[MAX_NAME_LENGTH - 1] = '\0';

		strncpy(username, DEFAULT_ADMIN_USERNAME, MAX_NAME_LENGTH - 1);
		username[MAX_NAME_LENGTH - 1] = '\0';

		strncpy(email, sysData->appContext->adminUserEmail, MAX_NAME_LENGTH - 1);
		email[MAX_NAME_LENGTH - 1] = '\0';

		strncpy(password, sysData->appContext->adminUserPassword, MAX_PASSWORD_LENGTH - 1);
		password[MAX_PASSWORD_LENGTH - 1] = '\0';

		strncpy(phone, sysData->appContext->adminUserPhone, MAX_NAME_LENGTH - 1);
		phone[MAX_NAME_LENGTH - 1] = '\0';

		strncpy(dateCreated, now, MAX_DATE_LENGTH - 1);
		dateCreated[MAX_DATE_LENGTH - 1] = '\0';

		strncpy(lastUpdated, EMPTY_STRING, MAX_DATE_LENGTH - 1);
		lastUpdated[MAX_DATE_LENGTH - 1] = '\0';

		strncpy(lastLogin, EMPTY_STRING, MAX_DATE_LENGTH - 1);
		lastLogin[MAX_DATE_LENGTH - 1] = '\0';

		strncpy(dateDeleted, EMPTY_STRING, MAX_DATE_LENGTH - 1);
		dateDeleted[MAX_DATE_LENGTH - 1] = '\0';

		int roleID = ROLE_ADMIN;
		int userStatus = active;

		status = createUser(sysData, name, username, email, password, phone, roleID, userStatus, dateCreated, lastUpdated, lastLogin, dateDeleted);

		freeUserDataVariable(name, username, email, password, phone, dateCreated, lastUpdated, lastLogin, dateDeleted);
		free(now);

		if (status != successful)
		{
			printf("\n\n");
			logPrintMessage(LOG_ERROR, "Failed to create user [ Falha ao criar o usuário ]", yes);
			status = failed;
			return status;
		}
		printf("\n\n");
		logPrintMessage(LOG_SUCCESS, "Default User created successfully [ Usuário criado com sucesso ]", yes);
		status = successful;
		return status;
	}
	else
	{
		printf("\n\n");
		logPrintMessage(LOG_INFO, "User database file found [ Arquivo de dados do usuário encontrado ]", yes);
		status = successful;
		fclose(checkUserFile);
		return status;
	}
	return status;
}
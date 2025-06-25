#include "../include/unicambio.h"
#include "../include/env.h"
#include "../include/utilities.h"
#include "../include/logger.h"
#include "../include/structures.h"
#include "../include/enum.h"

static void trim(char *str)
{
	char *end;

	// Trim leading spaces [Remove espaco em branco no inicio]
	while (isspace((unsigned char)*str))
	{
		str++;
	}
	if (*str == 0)
	{
		return;
	}
	// Trim trailing spaces [Remove espaco em branco no fim]
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
	{
		end--;
	}
	*(end + 1) = '\0';
}

static void removeComment(char *str)
{
	char *comment = strchr(str, '#');
	if (comment != NULL)
	{
		*comment = '\0';
	}
}
StatusInfo loadEnvFile(SystemData *sysData, const char *envFilePath)
{
	StatusInfo status;

	if (!sysData || !sysData->appContext)
	{
		logPrintMessage(LOG_ERROR, "System Data or Application Context is NULL", yes);
		return failed;
	}
	FILE *userFile = fopen(USER_DATA_FILE_PATH, "r");
	if (!userFile)
	{
		logPrintMessage(LOG_ERROR, "Default user file doesn't exist, Loading default admin data to app context.", yes);
		logPrintMessage(LOG_INFO, "[ Arquivo de dados do usuário padrão nao existe, carregando dados do admin padrão para o contexto da aplicação ]", yes);

		FILE *envFile = fopen(envFilePath, "r");
		if (envFile == NULL)
		{
			logPrintMessage(LOG_ERROR, "Failed to open environment file [ Falha ao abrir o arquivo de ambiente ]", yes);
			return failed;
		}
		char line[MAX_LINE_LENGTH];
		while (fgets(line, sizeof(line), envFile))
		{
			removeComment(line);
			trim(line);
			if (line[0] == '#' || strchr(line, '=') == NULL)
			{
				continue;
			}
			char *key = strtok(line, "=");
			char *value = strtok(NULL, "=");
			if (!key || !value)
			{
				continue;
			}
			trim(key);
			trim(value);

			if (strcmp(key, "ADMIN_USER_EMAIL") == 0)
			{
				free(sysData->appContext->adminUserEmail);
				sysData->appContext->adminUserEmail = strdup(value);
				if (!sysData->appContext->adminUserEmail)
				{
					logPrintMessage(LOG_ERROR, "Failed to load ADMIN_USER_EMAIL [ Falha ao carregar ADMIN_USER_EMAIL ]", yes);
					status = failed;
					return status;
				}
			}
			else if (strcmp(key, "ADMIN_USER_PASSWORD") == 0)
			{
				free(sysData->appContext->adminUserPassword);
				sysData->appContext->adminUserPassword = strdup(value);
				if (!sysData->appContext->adminUserPassword)
				{
					logPrintMessage(LOG_ERROR, "Failed to load ADMIN_USER_PASSWORD [ Falha ao carregar ADMIN_USER_PASSWORD ]", yes);
					free(sysData->appContext->adminUserEmail);
					status = failed;
					return status;
				}
			}
			else if (strcmp(key, "ADMIN_USER_PHONE") == 0)
			{
				free(sysData->appContext->adminUserPhone);
				sysData->appContext->adminUserPhone = strdup(value);
				if (!sysData->appContext->adminUserPhone)
				{
					logPrintMessage(LOG_ERROR, "Failed to load ADMIN_USER_PHONE [ Falha ao carregar ADMIN_USER_PHONE ]", yes);
					free(sysData->appContext->adminUserEmail);
					free(sysData->appContext->adminUserPassword);
					status = failed;
					return status;
				}
			}
		}
		fclose(envFile);
		status = successful;
		sysData->appContextCount++;
		sysData->appContextCapacity++;
		logPrintMessage(LOG_SUCCESS, "Environment file loaded successfully [ Arquivo de ambiente carregado com sucesso ]", yes);
		return status;
	}
	fclose(userFile);
	logPrintMessage(LOG_SUCCESS, "Environment file doesn't need to load as user file exists ", yes);
	logPrintMessage(LOG_INFO, "[ Arquivo de ambiente nao precisa ser carregado pois o arquivo de dados do usuário existe ]", yes);
	status = successful;
	return status;
}

StatusInfo freeAppContext(char *currentUserName, char *adminUserPassword, char *adminUserEmail, char *adminUserPhone)
{
	free(currentUserName);
	free(adminUserPassword);
	free(adminUserEmail);
	free(adminUserPhone);
	return successful;
}
StatusInfo freeMemoryAllocatedToAppContextStructure(SystemData *sysData)
{
	StatusInfo status;
	if (!sysData || !sysData->appContext)
	{
		logPrintMessage(LOG_ERROR, "System Data or Application Context is NULL to free memory allocated to app context structure [ Sistema ou contexto de aplicação nulo para liberar memória alocada para a estrutura de contexto da aplicação ]", yes);
		status = failed;
		return status;
	}
	for (size_t i = 0; i < sysData->appContextCount; i++)
	{
		freeAppContext(sysData->appContext[i].currentUserName, sysData->appContext[i].adminUserPassword, sysData->appContext[i].adminUserEmail, sysData->appContext[i].adminUserPhone);
	}
	free(sysData->appContext);
	status = successful;
	return status;
}
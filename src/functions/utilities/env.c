/**
 * @file env.c
 * @author Chinedum Odili (https://github.com/sp-cristiano)
 * @brief Implementation of loading environment config file into SystemData's appContext. [Implementação de carregamento de arquivo de configuração de ambiente para o appContext do SystemData]
 * @version 0.1
 * @date 2025-06-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../include/unicambio.h"
#include "../include/env.h"
#include "../include/logger.h"
#include "../include/messages.h"
#include "../include/structures.h"

/**
 * @brief Removes leading and trailing whitespace from a string in place. [Remove espaco em branco no inicio e no fim de uma string]
 *
 */
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
/**
 * @brief Loads environment config file and stores the values in SystemData's appContext. [Carrega arquivo de configuração de ambiente e armazena os valores no appContext do SystemData]
 *
 * supports keys like:
 * ADMIN_USER_EMAIL
 * ADMIN_USER_PASSWORD
 * ADMIN_USER_PHONE
 *
 * [Suporta chaves como:
 * ADMIN_USER_EMAIL
 * ADMIN_USER_PASSWORD
 * ADMIN_USER_PHONE]
 *
 * @param sysData Pointer to the SystemData struct [Ponteiro para a estrutura SystemData]
 * @param filePath Path to the environment file [Caminho para o arquivo de ambiente]
 * @return StatusInfo Status of the operation [Status da operação]
 */

static void removeComment(char *str)
{
	char *comment = strchr(str, '#');
	if (comment != NULL)
	{
		*comment = '\0';
	}
}

StatusInfo loadEnvFile(SystemData *sysData, const char *filePath)
{
	// Check if sysData or sysData->appContext is NULL[Verifique se sysData ou sysData->appContext é NULL]
	if (!sysData || !sysData->appContext)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_OR_APP_CONTEXT_IS_NULL);
		return failed;
	}
	FILE *envFile = fopen(filePath, "r");
	if (envFile == NULL)
	{
		// fprintf(stderr, "%s\n", UI_ERROR_ENV_FILE_NOT_FOUND);
		logMessages(LOG_ERROR, UI_ERROR_ENV_FILE_NOT_FOUND);
		return failed;
	}
	char line[MAX_LINE_LENGTH];

	while (fgets(line, sizeof(line), envFile))
	{
		removeComment(line); // remove comments
		trim(line);					 // remove leading and trailing whitespace

		if (line[0] == '#' || strchr(line, '=') == NULL)
		{
			continue;
		}
		char *key = strtok(line, "=");
		char *value = strtok(NULL, " ");

		if (!key || !value)
		{
			continue;
		}
		trim(key);
		trim(value);

		if (strcmp(key, "ADMIN_USER_EMAIL") == 0)
		{
			free(sysData->appContext->ADMIN_USER_EMAIL);
			sysData->appContext->ADMIN_USER_EMAIL = strdup(value);
			if (sysData->appContext->ADMIN_USER_EMAIL == NULL)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				return failed;
			}
		}
		else if (strcmp(key, "ADMIN_USER_PASSWORD") == 0)
		{
			free(sysData->appContext->ADMIN_USER_PASSWORD);
			sysData->appContext->ADMIN_USER_PASSWORD = strdup(value);
			if (sysData->appContext->ADMIN_USER_PASSWORD == NULL)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				return failed;
			}
		}
		else if (strcmp(key, "ADMIN_USER_PHONE") == 0)
		{
			free(sysData->appContext->ADMIN_USER_PHONE);
			sysData->appContext->ADMIN_USER_PHONE = strdup(value);
			if (sysData->appContext->ADMIN_USER_PHONE == NULL)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				return failed;
			}
		}
	}
	fclose(envFile);
	sysData->appContextCount++;
	sysData->appContextCapacity++;
	return successful;
}

void freeAppContext(char *currentDate, char *currentTime, char *currentUserName, char *ADMIN_USER_PASSWORD, char *ADMIN_USER_EMAIL, char *ADMIN_USER_PHONE)
{
	free(currentDate);
	free(currentTime);
	free(currentUserName);
	free(ADMIN_USER_PASSWORD);
	free(ADMIN_USER_EMAIL);
	free(ADMIN_USER_PHONE);
}

freeMemoryAllocatedToAppContextStructure(SystemData *sysData)
{
	if (sysData == NULL)
	{
		return;
	}
	for (size_t i = 0; i < sysData->appContextCount; i++)
	{
		free(sysData->appContext[i].currentDate);
		free(sysData->appContext[i].currentTime);
		free(sysData->appContext[i].currentUserName);
		free(sysData->appContext[i].ADMIN_USER_PASSWORD);
		free(sysData->appContext[i].ADMIN_USER_EMAIL);
		free(sysData->appContext[i].ADMIN_USER_PHONE);
	}
	// free(sysData->appContext);
	sysData->appContext = NULL;
	sysData->appContextCount = 0;
	sysData->appContextCapacity = 0;
}
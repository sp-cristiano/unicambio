#include "../include/unicambio.h"
#include "../include/createDB.h"
#include "../include/logger.h"
StatusInfo createUserDBFile()
{
	StatusInfo status;

	FILE *userFile = fopen(USER_DATA_FILE_PATH, "w");
	if (!userFile)
	{
		printf("\n\n");
		logPrintMessage(LOG_ERROR, "Failed to create user database file [ Falha ao criar o arquivo de dados do usuário ]", yes);
		status = failed;
		return status;
	}
	else
	{
		status = successful;
		printf("\n\n");
		logPrintMessage(LOG_SUCCESS, "User database file created successfully [ Arquivo de dados do usuário criado com sucesso ]", yes);
		return status;
	}
	if (fclose(userFile) != 0)
	{
		logPrintMessage(LOG_ERROR, "Failed to close user database file [ Falha ao fechar o arquivo de dados do usuário ]", yes);
		printf("\n\n");
		status = failed;
		return status;
	}
	return status;
}

StatusInfo createCurrencyDBFile()
{
	StatusInfo status;

	FILE *currencyFile = fopen(CURRENCY_DATA_FILE_PATH, "w");
	if (!currencyFile)
	{
		printf("\n\n");
		logPrintMessage(LOG_ERROR, "Failed to create currency database file [ Falha ao criar o arquivo de dados da moeda ]", yes);
		status = failed;
		return status;
	}
	else
	{
		status = successful;
		printf("\n\n");
		logPrintMessage(LOG_SUCCESS, "Currency database file created successfully [ Arquivo de dados da moeda criado com sucesso ]", yes);
		return status;
	}
	if (fclose(currencyFile) != 0)
	{
		printf("\n\n");
		logPrintMessage(LOG_ERROR, "Failed to close currency database file [ Falha ao fechar o arquivo de dados da moeda ]", yes);
		status = failed;
		return status;
	}
	return status;
}
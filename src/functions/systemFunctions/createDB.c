#include "../include/unicambio.h"
#include "../include/createDB.h"
#include "../include/logger.h"
#include "../include/endian.h"

StatusInfo createUserDBFile()
{
	StatusInfo status;

	FILE *userFile = fopen(USER_DATA_FILE_PATH, "w");
	if (!userFile)
	{
		logPrintMessage(LOG_ERROR, "Failed to create user database file [ Falha ao criar o arquivo de dados do usuário ]", yes);
		status = failed;
		return status;
	}
	else
	{
		status = successful;
		logPrintMessage(LOG_SUCCESS, "User database file created successfully [ Arquivo de dados do usuário criado com sucesso ]", yes);
		return status;
	}
	if (fclose(userFile) != 0)
	{
		logPrintMessage(LOG_ERROR, "Failed to close user database file [ Falha ao fechar o arquivo de dados do usuário ]", yes);
		status = failed;
		return status;
	}
	return status;
}
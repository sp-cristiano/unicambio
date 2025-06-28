#include "../include/unicambio.h"
#include "../include/structures.h"
#include "../include/enum.h"
#include "../include/currencyDefaultSetup.h"
#include "../include/currencyFunction.h"
#include "../include/utilities.h"
#include "../include/logger.h"
#include "../include/createDB.h"

StatusInfo createCurrencyDefaultSetup(SystemData *sysData)
{
	StatusInfo status;
	FILE *checkCurrencyFile = fopen(CURRENCY_DATA_FILE_PATH, "r");
	if (!checkCurrencyFile)
	{
		logPrintMessage(LOG_WARNING, "Currency database file not found [ Arquivo de dados da moeda nao encontrado ]", yes);
		logPrintMessage(LOG_INFO, "Creating currency database file [ Criando arquivo de dados da moeda ]", yes);

		processing();

		status = createCurrencyDBFile();
		if (status == failed)
		{
			logPrintMessage(LOG_ERROR, "Failed to create currency database file [ Falha ao criar o arquivo de dados da moeda ]", yes);
			return failed;
		}
		if (!sysData)
		{
			logPrintMessage(LOG_ERROR, "System data not found [ Dados do sistema nao encontrados ]", yes);
			status = failed;
			return status;
		}
		char *name = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
		char *code = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
		char *symbol = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
		char *country = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
		char *dateCreated = (char *)malloc(MAX_DATE_LENGTH * sizeof(char));
		char *lastUpdated = (char *)malloc(MAX_DATE_LENGTH * sizeof(char));
		char *dateDeleted = (char *)malloc(MAX_DATE_LENGTH * sizeof(char));
		if (!name || !code || !symbol || !country || !dateCreated || !lastUpdated || !dateDeleted)
		{
			logPrintMessage(LOG_ERROR, "Memory allocation for currency default data failed [ Falha ao alocar memória para os dados padrão da moeda ]", yes);
			freeCurrencyVariable(name, code, symbol, country, dateCreated, lastUpdated, dateDeleted);
			status = failed;
			return status;
		}

		char *now = getCurrentDateTime(TYPE_DATETIME);
		if (!now)
		{
			logPrintMessage(LOG_ERROR, "Failed to get current date and time [ Falha ao obter data e hora atual ]", yes);
			freeCurrencyVariable(name, code, symbol, country, dateCreated, lastUpdated, dateDeleted);
			status = failed;
			return status;
		}
		strncpy(name, "United State Dollar [Dolar dos Estados Unidos]", MAX_NAME_LENGTH - 1);
		name[MAX_NAME_LENGTH - 1] = '\0';

		strncpy(code, "USD", MAX_NAME_LENGTH - 1);
		code[MAX_NAME_LENGTH - 1] = '\0';

		strncpy(symbol, "$", MAX_NAME_LENGTH - 1);
		symbol[MAX_NAME_LENGTH - 1] = '\0';

		strncpy(country, "United States", MAX_NAME_LENGTH - 1);
		country[MAX_NAME_LENGTH - 1] = '\0';

		strncpy(dateCreated, now, MAX_DATE_LENGTH - 1);
		dateCreated[MAX_DATE_LENGTH - 1] = '\0';

		strncpy(lastUpdated, EMPTY_STRING, MAX_DATE_LENGTH - 1);
		lastUpdated[MAX_DATE_LENGTH - 1] = '\0';

		strncpy(dateDeleted, EMPTY_STRING, MAX_DATE_LENGTH - 1);
		dateDeleted[MAX_DATE_LENGTH - 1] = '\0';

		int currencyStatus = active;
		double rateToOneKz = convertRateToOneKz(DEFAULT_USD_RATE);

		status = createCurrency(sysData, name, code, symbol, country, currencyStatus, rateToOneKz, dateCreated, lastUpdated, dateDeleted);

		freeCurrencyVariable(name, code, symbol, country, dateCreated, lastUpdated, dateDeleted);
		free(now);
		if (status != successful)
		{
			logPrintMessage(LOG_ERROR, "Failed to create currency [ Falha ao criar a moeda ]", yes);
			status = failed;
			return status;
		}
		logPrintMessage(LOG_SUCCESS, "Default currency created successfully [ Moeda padrão criada com sucesso ]", yes);
		status = successful;
		return status;
	}
	else
	{
		logPrintMessage(LOG_INFO, "Currency database file found [ Arquivo de dados da moeda encontrado ]", yes);
		status = successful;
		fclose(checkCurrencyFile);
		return status;
	}
	return status;
}

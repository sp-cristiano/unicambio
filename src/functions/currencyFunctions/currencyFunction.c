#include "../include/currencyFunction.h"

StatusInfo creatCurrency(SystemData *sysData, char *name, char *code, char *symbol, char *country, int currencyStatus, double rateToOneKz, char *dateCreated, char *lastUpdated, char *dateDeleted)
{
	StatusInfo status;
	if (!sysData)
	{
		logPrintMessage(LOG_ERROR, "System data is Null. Failed to create currency [ Dados do sistema nulo. Falha ao criar moeda ]", yes);
		status = failed;
		return status;
	}

	if (!name || !code || !symbol || !country || !dateCreated || !lastUpdated || !dateDeleted)
	{
		logPrintMessage(LOG_ERROR, "Currency data is Null. Failed to create currency [ Dados da moeda nulo. Falha ao criar moeda ]", yes);
		status = failed;
		return status;
	}
	if (currencyStatus == active)
	{
		if (sysData->currencyCount >= sysData->currencyCapacity)
		{
			size_t newCapacity = (sysData->currencyCapacity + 2) * 2;
			CurrencyInfo *tempCurrencySize = realloc(sysData->currencies, sizeof(CurrencyInfo) * newCapacity);
			if (!tempCurrencySize)
			{
				logPrintMessage(LOG_ERROR, "Failed to allocate memory for currency data [ Falha ao alocar memória para os dados da moeda ]", yes);
				status = failed;
				return status;
			}
			sysData->currencyCapacity = newCapacity;
			sysData->currencies = tempCurrencySize;
		}

		int currencyID = randomNumber(10000, 50000);

		if (sysData->currencies && sysData->currencyCount > 0)
		{
			for (size_t i = 0; i < sysData->currencyCount; i++)
			{
				if (sysData->currencies[i].currencyID == currencyID)
				{
					currencyID = randomNumber(10000, 50000);
					i = 0;
				}
				if ((sysData->currencies[i].code && strcmp(sysData->currencies[i].code, code) == 0))
				{
					logPrintMessage(LOG_ERROR, "Currency code already exists. Failed to create currency [ Codigo da moeda ja cadastrado. Falha ao criar moeda ]", yes);
					status = failed;
					return status;
				}
			}
		}
		if (sysData->currencyCount < sysData->currencyCapacity)
		{
			sysData->currencies[sysData->currencyCount].currencyID = currencyID;

			sysData->currencies[sysData->currencyCount].name = strdup(name);
			if (sysData->currencies[sysData->currencyCount].name == NULL)
			{
				logPrintMessage(LOG_ERROR, "Failed to allocate memory for currency name [ Falha ao alocar memória para o nome da moeda ]", yes);
				status = failed;
				return status;
			}

			sysData->currencies[sysData->currencyCount].code = strdup(code);
			if (sysData->currencies[sysData->currencyCount].code == NULL)
			{
				logPrintMessage(LOG_ERROR, "Failed to allocate memory for currency code [ Falha ao alocar memória para o codigo da moeda ]", yes);
				free(sysData->currencies[sysData->currencyCount].name);
				status = failed;
				return status;
			}

			sysData->currencies[sysData->currencyCount].symbol = strdup(symbol);
			if (sysData->currencies[sysData->currencyCount].symbol == NULL)
			{
				logPrintMessage(LOG_ERROR, "Failed to allocate memory for currency symbol [ Falha ao alocar memória para o simbolo da moeda ]", yes);
				free(sysData->currencies[sysData->currencyCount].code);
				free(sysData->currencies[sysData->currencyCount].name);
				status = failed;
				return status;
			}
			sysData->currencies[sysData->currencyCount].country = strdup(country);
			if (sysData->currencies[sysData->currencyCount].country == NULL)
			{
				logPrintMessage(LOG_ERROR, "Failed to allocate memory for currency country [ Falha ao alocar memória para o pais da moeda ]", yes);
				free(sysData->currencies[sysData->currencyCount].symbol);
				free(sysData->currencies[sysData->currencyCount].code);
				free(sysData->currencies[sysData->currencyCount].name);
				status = failed;
				return status;
			}

			sysData->currencies[sysData->currencyCount].currencyStatus = currencyStatus;

			sysData->currencies[sysData->currencyCount].rate = rateToOneKz;

			sysData->currencies[sysData->currencyCount].dateCreated = strdup(dateCreated);
			if (sysData->currencies[sysData->currencyCount].dateCreated == NULL)
			{
				logPrintMessage(LOG_ERROR, "Failed to allocate memory for currency creation date [ Falha ao alocar memória para a data de criação da moeda ]", yes);
				free(sysData->currencies[sysData->currencyCount].country);
				free(sysData->currencies[sysData->currencyCount].symbol);
				free(sysData->currencies[sysData->currencyCount].code);
				free(sysData->currencies[sysData->currencyCount].name);
				status = failed;
				return status;
			}
			sysData->currencies[sysData->currencyCount].lastUpdated = strdup(lastUpdated);
			if (sysData->currencies[sysData->currencyCount].lastUpdated == NULL)
			{
				logPrintMessage(LOG_ERROR, "Failed to allocate memory for currency update date [ Falha ao alocar memória para a data de atualização da moeda ]", yes);
				free(sysData->currencies[sysData->currencyCount].dateCreated);
				free(sysData->currencies[sysData->currencyCount].country);
				free(sysData->currencies[sysData->currencyCount].symbol);
				free(sysData->currencies[sysData->currencyCount].code);
				free(sysData->currencies[sysData->currencyCount].name);
				status = failed;
				return status;
			}
			sysData->currencies[sysData->currencyCount].dateDeleted = strdup(dateDeleted);
			if (sysData->currencies[sysData->currencyCount].dateDeleted == NULL)
			{
				logPrintMessage(LOG_ERROR, "Failed to allocate memory for currency deletion date [ Falha ao alocar memória para a data de exclusão da moeda ]", yes);
				free(sysData->currencies[sysData->currencyCount].lastUpdated);
				free(sysData->currencies[sysData->currencyCount].dateCreated);
				free(sysData->currencies[sysData->currencyCount].country);
				free(sysData->currencies[sysData->currencyCount].symbol);
				free(sysData->currencies[sysData->currencyCount].code);
				free(sysData->currencies[sysData->currencyCount].name);
				status = failed;
				return status;
			}
			sysData->currencyCount++;
			status = successful;
			saveCurrencyData(sysData);
		}
		return status;
	}
}
StatusInfo freeCurrencyVariable(char *name, char *code, char *symbol, char *country, char *dateCreated, char *lastUpdated, char *dateDeleted)
{
	free(name);
	free(code);
	free(symbol);
	free(country);
	free(dateCreated);
	free(lastUpdated);
	free(dateDeleted);
	return successful;
}

StatusInfo freeCurrencyData(SystemData *sysData)
{
	free(sysData->currencies[sysData->currencyCount].name);
	free(sysData->currencies[sysData->currencyCount].code);
	free(sysData->currencies[sysData->currencyCount].symbol);
	free(sysData->currencies[sysData->currencyCount].country);
	free(sysData->currencies[sysData->currencyCount].dateCreated);
	free(sysData->currencies[sysData->currencyCount].lastUpdated);
	free(sysData->currencies[sysData->currencyCount].dateDeleted);
	return successful;
}

StatusInfo saveCurrencyData(SystemData *sysData)
{
	StatusInfo status;
	if (!sysData)
	{
		logPrintMessage(LOG_ERROR, "System data is Null. Failed to save currency data [ Dados do sistema nulo. Falha ao salvar dados da moeda ]", yes);
		status = failed;
		return status;
	}

	FILE *currencyFile = fopen(CURRENCY_DATA_FILE_PATH, "w");
	if (!currencyFile)
	{
		logPrintMessage(LOG_ERROR, "Failed to open currency data file [ Falha ao abrir o arquivo de dados da moeda ]", yes);
		status = failed;
		return status;
	}
	if (sysData->currencyCount == 0)
	{
		logPrintMessage(LOG_INFO, "Currency data file is empty [ Arquivo de dados da moeda esta vazio ]", yes);
		fclose(currencyFile);
		status = successful;
		return status;
	}
	for (size_t i = 0; i < sysData->currencyCount; i++)
	{
		fprintf(currencyFile, "%d|%s|%s|%s|%s|%d|%ld|%s|%s|%s\n", sysData->currencies[i].currencyID, sysData->currencies[i].name, sysData->currencies[i].code, sysData->currencies[i].symbol, sysData->currencies[i].country, sysData->currencies[i].currencyStatus, sysData->currencies[i].rate, sysData->currencies[i].dateCreated, sysData->currencies[i].lastUpdated, sysData->currencies[i].dateDeleted);
	}
	if (fclose(currencyFile) != 0)
	{
		logPrintMessage(LOG_ERROR, "Failed to close currency data file [ Falha ao fechar o arquivo de dados da moeda ]", yes);
		status = failed;
		return status;
	}
	status = successful;
	logPrintMessage(LOG_INFO, "Currency data saved successfully [ Dados da moeda salvos com sucesso ]", yes);
	return status;
}

StatusInfo loadCurrencyData(SystemData *sysData)
{
	StatusInfo status;
	if (!sysData)
	{
		logPrintMessage(LOG_ERROR, "System data is Null. Failed to load currency data [ Dados do sistema nulo. Falha ao carregar dados da moeda ]", yes);
		status = failed;
		return status;
	}
	FILE *currencyFile = fopen(CURRENCY_DATA_FILE_PATH, "r");
	if (!currencyFile)
	{
		logPrintMessage(LOG_ERROR, "Failed to open currency data file [ Falha ao abrir o arquivo de dados da moeda ]", yes);
		status = failed;
		return status;
	}

	int _currencyID, _currencyStatus;
	char name[MAX_NAME_LENGTH], code[MAX_NAME_LENGTH], symbol[MAX_NAME_LENGTH], country[MAX_NAME_LENGTH], dateCreated[MAX_DATE_LENGTH], lastUpdated[MAX_DATE_LENGTH], dateDeleted[MAX_DATE_LENGTH];
	double rate;

	if (sysData->currencyCount >= sysData->currencyCapacity)
	{
		size_t newCapacity = (sysData->userCapacity + 2) * 2;
		CurrencyInfo *tempCurrencySize = realloc(sysData->currencies, sizeof(CurrencyInfo) * newCapacity);
		if (!tempCurrencySize)
		{
			logPrintMessage(LOG_ERROR, "Failed to allocate memory for currency data [ Falha ao alocar memória para dados da moeda ]", yes);
			fclose(currencyFile);
			status = failed;
			return status;
		}
		sysData->currencies = tempCurrencySize;
		sysData->currencyCapacity = newCapacity;
	}
	sysData->currencyCount = 0;

	while (fscanf(currencyFile, "%d|%[149^|]|%9[^|]|%5[^|]|%149[^|]|%d|%lf|%99[^|]|%99[^|]|%99[^\n]\n", &_currencyID, name, code, symbol, country, &_currencyStatus, &rate, dateCreated, lastUpdated, dateDeleted) != EOF && sysData->currencyCount < sysData->currencyCapacity)
	{
		if (sysData->currencyCount >= sysData->currencyCapacity)
		{
			size_t newCapacity = (sysData->currencyCapacity + 2) * 2;
			CurrencyInfo *tempCurrencySize = realloc(sysData->currencies, sizeof(CurrencyInfo) * newCapacity);
			if (!tempCurrencySize)
			{
				logPrintMessage(LOG_ERROR, "Failed to allocate memory for currency data [ Falha ao alocar memória para dados da moeda ]", yes);
				fclose(currencyFile);
				status = failed;
				return status;
			}
			sysData->currencies = tempCurrencySize;
			sysData->currencyCapacity = newCapacity;
		}
		sysData->currencies[sysData->currencyCount].currencyID = _currencyID;
		sysData->currencies[sysData->currencyCount].name = strdup(name);
		sysData->currencies[sysData->currencyCount].code = strdup(code);
		sysData->currencies[sysData->currencyCount].symbol = strdup(symbol);
		sysData->currencies[sysData->currencyCount].country = strdup(country);
		sysData->currencies[sysData->currencyCount].currencyStatus = _currencyStatus;
		sysData->currencies[sysData->currencyCount].rate = rate;
		sysData->currencies[sysData->currencyCount].dateCreated = strdup(dateCreated);
		sysData->currencies[sysData->currencyCount].lastUpdated = strdup(lastUpdated);
		sysData->currencies[sysData->currencyCount].dateDeleted = strdup(dateDeleted);

		sysData->currencyCount++;
	}
	if (sysData->userCount == 0)
	{
		logPrintMessage(LOG_ERROR, "Unable to load currency data because currency data is empty [ Impossível carregar dados da moeda porque os dados da moeda estao vazios ]", yes);
		status = failed;
		return status;
	}
	fclose(currencyFile);

	status = successful;
	logPrintMessage(LOG_INFO, "Currency data loaded successfully [ Dados da moeda carregados com sucesso ]", yes);

	return status;
}

StatusInfo freeMemoryAllocatedToCurrencyStructure(SystemData *sysData)
{
	StatusInfo status;
	if (!sysData)
	{
		logPrintMessage(LOG_ERROR, "System data is Null. Failed to free memory allocated to currency structure [ Dados do sistema nulo. Falha ao liberar memória alocada para a estrutura de moeda ]", yes);
		status = failed;
		return status;
	}
	if (!sysData->currencies)
	{
		logPrintMessage(LOG_ERROR, "Currencies is Null. Failed to free memory allocated to currency structure [ Moedas nulas. Falha ao liberar memória alocada para a estrutura de moeda ]", yes);
		status = failed;
		return status;
	}
	for (size_t i = 0; i < sysData->currencyCount; i++)
	{
		free(sysData->currencies[i].name);
		free(sysData->currencies[i].code);
		free(sysData->currencies[i].symbol);
		free(sysData->currencies[i].country);
		free(sysData->currencies[i].dateCreated);
		free(sysData->currencies[i].lastUpdated);
		free(sysData->currencies[i].dateDeleted);
	}

	freeCurrencyData(sysData);
	status = successful;
	return status;
}
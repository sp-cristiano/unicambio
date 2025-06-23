#include "../include/unicambio.h"
#include "../include/utilities.h"
#include "../include/exchangeRateFunctions.h"
#include "../include/structures.h"
#include "../include/messages.h"
#include "../include/logger.h"
#include "../include/transactionFunctions.h"

void createExchangeRate(SystemData *sysData, int fromCurrencyID, double fromCurrencyAmountToConvert, int exchangeRateStatus, int toCurrencyID, char *createdAt, char *updatedAt, char *deletedAt)
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
	if (exchangeRateStatus == active)
	{

		// check if exchangeRate capacity need adjustment [Verifique se a capacidade de taxa de câmbio precisa de ajuste]
		if (sysData->exchangeRateCapacity == 0)
		{
			sysData->exchangeRateCapacity = 2;
		}
		else if (sysData->exchangeRateCount >= sysData->exchangeRateCapacity)
		{
			sysData->exchangeRateCapacity = (sysData->exchangeRateCapacity + 2) * 2;
		}

		// Reallocate Memory to the exchangeRate structure.
		ExchangeRateInfo *tempExchangeRateSize = realloc(sysData->exchangeRates, sizeof(ExchangeRateInfo) * sysData->exchangeRateCapacity);
		if (tempExchangeRateSize == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			sleep(MID_SLEEP);
			return;
		}

		sysData->exchangeRates = tempExchangeRateSize;

		int exchangeRateID = randomNumber(60000, 80000);

		// check if exchangeRateID already exists [Verifique se o ID da taxa de câmbio já existe]
		for (size_t i = 0; i < sysData->exchangeRateCount; i++)
		{
			if (sysData->exchangeRates[i].exchangeRateID == exchangeRateID)
			{
				exchangeRateID = randomNumber(60000, 80000);
				i = -1;
			}
		}
		// set current user id from appContext
		int userID = sysData->appContext->currentUserID;

		// Get from currency Rate by from currency id
		double fromCurrencyRate = getCurrencyRateToOneKzByID(sysData, fromCurrencyID);

		// Convert from currency to Kz
		double fromCurrencyRateToKz = ((fromCurrencyAmountToConvert) / (fromCurrencyRate));

		// Get from currency Code
		char *fromCurrencyCode = getCurrencyCodeByID(sysData, fromCurrencyID);

		// Get to currency Rate by to currency id
		double toCurrencyRate = getCurrencyRateToOneKzByID(sysData, toCurrencyID);

		// Convert from currency amount that has been converted to kwanza to to currency amount in to currency currency
		double toCurrencyAmountConvertedTo = fromCurrencyRateToKz * toCurrencyRate;

		// Get to currency Code
		char *toCurrencyCode = getCurrencyCodeByID(sysData, toCurrencyID);

		// Convert to currency to Kz
		double toCurrencyRateToKz = ((fromCurrencyAmountToConvert) / (toCurrencyRate));

		// Allocate memory for exchange Rate data and copy strings for new exchange Rate data
		sysData->exchangeRates[sysData->exchangeRateCount].exchangeRateID = exchangeRateID;
		sysData->exchangeRates[sysData->exchangeRateCount].fromCurrencyID = fromCurrencyID;
		sysData->exchangeRates[sysData->exchangeRateCount].fromCurrencyAmountToConvert = fromCurrencyAmountToConvert;
		sysData->exchangeRates[sysData->exchangeRateCount].fromCurrencyRateToKz = fromCurrencyRateToKz;
		sysData->exchangeRates[sysData->exchangeRateCount].toCurrencyID = toCurrencyID;
		sysData->exchangeRates[sysData->exchangeRateCount].exchangeRateStatus = exchangeRateStatus;
		sysData->exchangeRates[sysData->exchangeRateCount].toCurrencyAmountConvertedTo = toCurrencyAmountConvertedTo;
		sysData->exchangeRates[sysData->exchangeRateCount].toCurrencyRateToKz = toCurrencyRateToKz;
		sysData->exchangeRates[sysData->exchangeRateCount].createdAt = strdup(createdAt);
		if (sysData->exchangeRates[sysData->exchangeRateCount].createdAt == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			sleep(MID_SLEEP);
			return;
		}

		sysData->exchangeRates[sysData->exchangeRateCount].updatedAt = strdup(updatedAt);
		if (sysData->exchangeRates[sysData->exchangeRateCount].updatedAt == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			free(sysData->exchangeRates[sysData->exchangeRateCount].createdAt);
			sleep(MID_SLEEP);
			return;
		}
		if (deletedAt == NULL)
		{
			sysData->exchangeRates[sysData->exchangeRateCount].deletedAt = strdup(" ");
			if (sysData->exchangeRates[sysData->exchangeRateCount].deletedAt == NULL)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
				free(sysData->exchangeRates[sysData->exchangeRateCount].createdAt);
				free(sysData->exchangeRates[sysData->exchangeRateCount].updatedAt);
				sleep(MID_SLEEP);
				return;
			}
		}
		else
		{
			sysData->exchangeRates[sysData->exchangeRateCount].deletedAt = strdup(deletedAt);
			if (sysData->exchangeRates[sysData->exchangeRateCount].deletedAt == NULL)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
				free(sysData->exchangeRates[sysData->exchangeRateCount].createdAt);
				free(sysData->exchangeRates[sysData->exchangeRateCount].updatedAt);
				sleep(MID_SLEEP);
				return;
			}
		}
		// revert exchange rate from one kz
		double exchangeRate = revertRateFromOneKz(toCurrencyRateToKz);
		int transactionStatus = successful;

		if (sysData->appContext->currentUserID == 0)
		{
			userID = getUserIDByMultipleSearch(sysData, sysData->appContext->ADMIN_USER_PHONE);

			createTransaction(sysData, exchangeRateID, userID, fromCurrencyID, fromCurrencyAmountToConvert, toCurrencyID, toCurrencyAmountConvertedTo, exchangeRate, exchangeRateStatus, fromCurrencyCode, fromCurrencyRateToKz, toCurrencyCode, transactionStatus, createdAt, updatedAt, deletedAt);
			sysData->exchangeRateCount++;
			saveExchangeRateData(sysData);
		}
		else
		{

			sysData->exchangeRateCount++;
			saveExchangeRateData(sysData);
		}
	}
	else
	{
		logMessages(LOG_ERROR, UI_ERROR_EXCHANGE_RATE_DATA_IS_NULL);
		centerStringOnly(UI_ERROR_EXCHANGE_RATE_DATA_IS_NULL);
		sleep(MID_SLEEP);
		return;
	}
	return;
}

// Save Exchange Rate Data to file
void saveExchangeRateData(SystemData *sysData)
{
	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		centerStringOnly(UI_ERROR_SYSTEM_DATA_IS_NULL);
		sleep(MID_SLEEP);
		return;
	}

	FILE *exchangeRateFile = fopen(EXCHANGE_RATE_DATA_FILE_PATH, "w");
	if (exchangeRateFile == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_EXCHANGE_RATE_DATA_FILE_NOT_FOUND);
		centerStringOnly(UI_ERROR_EXCHANGE_RATE_DATA_FILE_NOT_FOUND);
		sleep(MID_SLEEP);
		return;
	}

	for (size_t i = 0; i < sysData->exchangeRateCount; i++)
	{
		fprintf(exchangeRateFile, "%d|%d|%lf|%lf|%d|%d|%lf|%lf|%s|%s|%s\n", sysData->exchangeRates[i].exchangeRateID, sysData->exchangeRates[i].fromCurrencyID, sysData->exchangeRates[i].fromCurrencyAmountToConvert, sysData->exchangeRates[i].fromCurrencyRateToKz, sysData->exchangeRates[i].toCurrencyID, sysData->exchangeRates[i].exchangeRateStatus, sysData->exchangeRates[i].toCurrencyAmountConvertedTo, sysData->exchangeRates[i].toCurrencyRateToKz, sysData->exchangeRates[i].createdAt, sysData->exchangeRates[i].updatedAt, sysData->exchangeRates[i].deletedAt);
	}
	fclose(exchangeRateFile);
	return;
}

void loadExchangeRateData(SystemData *sysData)
{
	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		centerStringOnly(UI_ERROR_SYSTEM_DATA_IS_NULL);
		sleep(MID_SLEEP);
		return;
	}

	FILE *exchangeRateFile = fopen(EXCHANGE_RATE_DATA_FILE_PATH, "r");
	if (exchangeRateFile == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_EXCHANGE_RATE_DATA_FILE_NOT_FOUND);
		centerStringOnly(UI_ERROR_EXCHANGE_RATE_DATA_FILE_NOT_FOUND);
		sleep(MID_SLEEP);
		return;
	}

	// Initialize variables for reading data
	int _exchangeRateID, _fromCurrencyID, toCurrencyID, _exchangeRateStatus;
	double _fromCurrencyAmountToConvert, _fromCurrencyRateToKz, _toCurrencyAmountConvertedTo, _toCurrencyRateToKz;
	char _createdAt[MAX_DATE_LENGTH], _updatedAt[MAX_DATE_LENGTH], _deletedAt[MAX_DATE_LENGTH];

	// Adjusting exchange capacity if needed.
	if (sysData->exchangeRateCapacity == 0)
	{
		sysData->exchangeRateCapacity = 2;
	}
	else if (sysData->exchangeRateCount >= sysData->exchangeRateCapacity)
	{
		sysData->exchangeRateCapacity = (sysData->exchangeRateCapacity + 2) * 2;
	}

	// Reallocate memory to exchange rate structure
	ExchangeRateInfo *tempExchangeRateSize = realloc(sysData->exchangeRates, sizeof(ExchangeRateInfo) * sysData->exchangeRateCapacity);
	if (tempExchangeRateSize == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
		centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
		sleep(MID_SLEEP);
		return;
	}
	sysData->exchangeRates = tempExchangeRateSize;

	// initializing sysData->exchangeRateCount to 0
	sysData->exchangeRateCount = 0;

	while (fscanf(exchangeRateFile, "%d|%d|%lf|%lf|%d|%d|%lf|%lf|%99[^|]|%99[^|]|%99[^|]\n)", &_exchangeRateID, &_fromCurrencyID, &_fromCurrencyAmountToConvert, &_fromCurrencyRateToKz, &toCurrencyID, &_exchangeRateStatus, &_toCurrencyAmountConvertedTo, &_toCurrencyRateToKz, _createdAt, _updatedAt, _deletedAt) != EOF && sysData->exchangeRateCount < sysData->exchangeRateCapacity)
	{
		// Check if exchangeCount exceeds exchangecapacity [Verifique se exchangeCount excede exchangecapacity]
		if (sysData->exchangeRateCount >= sysData->exchangeRateCapacity)
		{
			sysData->exchangeRateCapacity = (sysData->exchangeRateCapacity + 2) * 2;
			tempExchangeRateSize = realloc(sysData->exchangeRates, sizeof(ExchangeRateInfo) * sysData->exchangeRateCapacity);
			if (tempExchangeRateSize == NULL)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
				sleep(MID_SLEEP);
				return;
			}
			sysData->exchangeRates = tempExchangeRateSize;
		}

		// Add exchange rate data to database
		sysData->exchangeRates[sysData->exchangeRateCount].exchangeRateID = _exchangeRateID;
		sysData->exchangeRates[sysData->exchangeRateCount].fromCurrencyID = _fromCurrencyID;
		sysData->exchangeRates[sysData->exchangeRateCount].fromCurrencyAmountToConvert = _fromCurrencyAmountToConvert;
		sysData->exchangeRates[sysData->exchangeRateCount].fromCurrencyRateToKz = _fromCurrencyRateToKz;
		sysData->exchangeRates[sysData->exchangeRateCount].toCurrencyID = toCurrencyID;
		sysData->exchangeRates[sysData->exchangeRateCount].exchangeRateStatus = _exchangeRateStatus;
		sysData->exchangeRates[sysData->exchangeRateCount].toCurrencyAmountConvertedTo = _toCurrencyAmountConvertedTo;
		sysData->exchangeRates[sysData->exchangeRateCount].toCurrencyRateToKz = _toCurrencyRateToKz;
		sysData->exchangeRates[sysData->exchangeRateCount].createdAt = strdup(_createdAt);
		if (sysData->exchangeRates[sysData->exchangeRateCount].createdAt == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			sleep(MID_SLEEP);
			return;
		}
		sysData->exchangeRates[sysData->exchangeRateCount].updatedAt = strdup(_updatedAt);
		if (sysData->exchangeRates[sysData->exchangeRateCount].updatedAt == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			free(sysData->exchangeRates[sysData->exchangeRateCount].createdAt);
			sleep(MID_SLEEP);
			return;
		}

		sysData->exchangeRates[sysData->exchangeRateCount].deletedAt = strdup(_deletedAt);

		if (sysData->exchangeRates[sysData->exchangeRateCount].deletedAt == NULL)
		{
			strcpy(_deletedAt, " ");
			sysData->exchangeRates[sysData->exchangeRateCount].deletedAt = strdup(_deletedAt);
			if (sysData->exchangeRates[sysData->exchangeRateCount].deletedAt == NULL)
			{

				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
				free(sysData->exchangeRates[sysData->exchangeRateCount].createdAt);
				free(sysData->exchangeRates[sysData->exchangeRateCount].updatedAt);
				sleep(MID_SLEEP);
				return;
			}
		}
		else
		{
			sysData->exchangeRates[sysData->exchangeRateCount].deletedAt = strdup(_deletedAt);
			if (sysData->exchangeRates[sysData->exchangeRateCount].deletedAt == NULL)
			{

				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
				free(sysData->exchangeRates[sysData->exchangeRateCount].createdAt);
				free(sysData->exchangeRates[sysData->exchangeRateCount].updatedAt);
				sleep(MID_SLEEP);
				return;
			}
		}

		sysData->exchangeRateCount++;
	}
	fclose(exchangeRateFile);
}

// Free exchangeRate Data
void freeExchangeRateData(SystemData *sysData)
{
	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		centerStringOnly(UI_ERROR_SYSTEM_DATA_IS_NULL);
		sleep(MID_SLEEP);
		return;
	}
	for (size_t i = 0; i < sysData->exchangeRateCount; i++)
	{
		free(sysData->exchangeRates[i].createdAt);
		free(sysData->exchangeRates[i].updatedAt);
		free(sysData->exchangeRates[i].deletedAt);
	}
	free(sysData->exchangeRates);
}

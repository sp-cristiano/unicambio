/**
 * @file transactionFunctions.c
 *
 * @version 0.1
 * @copyright Copyright (c) 2025
 */

#include "../include/unicambio.h"
#include "../include/structures.h"
#include "../include/transactionFunctions.h"
#include "../include/messages.h"
#include "../include/logger.h"
#include "../include/utilities.h"

void createTransaction(SystemData *sysData, int exchangeRateID, int userID, int fromCurrencyID, double fromCurrencyAmountToConvert, int toCurrencyID, double toCurrencyAmountConvertedTo, double exchangeRate, int exchangeRateStatus, char *fromCurrencyCode, double fromCurrencyRateToKz, char *toCurrencyCode, int transactionStatus, char *createdAt, char *updatedAt, char *deletedAt)
{
	// check if sysData pointer is valid
	if (sysData == NULL || sysData->appContext == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		sleep(MID_SLEEP);
		return;
	}
	int transactionID = randomNumber(80010, 99090);

	// Check if transaction capacity need adjustment [Verifique se a capacidade de transação precisa de ajuste]
	if (sysData->transactionCount >= sysData->transactionCapacity)
	{
		size_t newCapacity = (sysData->transactionCapacity + 2) * 2;
		TransactionInfo *tempTransactionSize = realloc(sysData->transactions, sizeof(TransactionInfo) * newCapacity);
		if (!tempTransactionSize)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			sleep(MID_SLEEP);
			return;
		}
		sysData->transactions = tempTransactionSize;
		sysData->transactionCapacity = newCapacity;
	}

	// Check if transactionID already exists [Verifique se o ID da transação já existe]
	if (sysData->transactions != NULL && sysData->transactionCount > 0)
	{
		for (size_t i = 0; i < sysData->transactionCount; i++)
		{
			if (sysData->transactions[i].transactionID == transactionID)
			{
				transactionID = randomNumber(80010, 99090);
				i = 0;
			}
		}
	}
	// Allocate memory for transaction history and copy strings for new transaction history
	sysData->transactions[sysData->transactionCount].transactionID = transactionID;
	sysData->transactions[sysData->transactionCount].exchangeRateID = exchangeRateID;
	sysData->transactions[sysData->transactionCount].userID = userID;
	sysData->transactions[sysData->transactionCount].fromCurrencyID = fromCurrencyID;
	sysData->transactions[sysData->transactionCount].fromCurrencyAmount = fromCurrencyAmountToConvert;
	sysData->transactions[sysData->transactionCount].toCurrencyID = toCurrencyID;
	sysData->transactions[sysData->transactionCount].toCurrencyAmount = toCurrencyAmountConvertedTo;
	sysData->transactions[sysData->transactionCount].exchangeRate = exchangeRate;
	sysData->transactions[sysData->transactionCount].exchangeRateStatus = exchangeRateStatus;
	sysData->transactions[sysData->transactionCount].fromCurrencyCode = strdup(fromCurrencyCode);
	if (!sysData->transactions[sysData->transactionCount].fromCurrencyCode)
	{
		logAndFreeTransaction(sysData, sysData->transactionCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
		return;
	}

	sysData->transactions[sysData->transactionCount].fromCurrencyRateToKz = fromCurrencyRateToKz;

	sysData->transactions[sysData->transactionCount].toCurrencyCode = strdup(toCurrencyCode);
	if (!sysData->transactions[sysData->transactionCount].toCurrencyCode)
	{
		logAndFreeTransaction(sysData, sysData->transactionCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
		return;
	}
	sysData->transactions[sysData->transactionCount].transactionStatus = transactionStatus;

	sysData->transactions[sysData->transactionCount].createdAt = strdup(createdAt);
	if (!sysData->transactions[sysData->transactionCount].createdAt)
	{
		logAndFreeTransaction(sysData, sysData->transactionCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
		return;
	}

	sysData->transactions[sysData->transactionCount].updatedAt = strdup(updatedAt);
	if (!sysData->transactions[sysData->transactionCount].updatedAt)
	{
		logAndFreeTransaction(sysData, sysData->transactionCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
		return;
	}

	if (deletedAt != NULL)
	{

		sysData->transactions[sysData->transactionCount].deletedAt = strdup(deletedAt);
	}
	else
	{

		sysData->transactions[sysData->transactionCount].deletedAt = strdup(" ");
	}

	if (!sysData->transactions[sysData->transactionCount].deletedAt)
	{
		logAndFreeTransaction(sysData, sysData->transactionCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
		return;
	}

	sysData->transactionCount++;
	saveTransactionData(sysData);
	return;
}

void saveTransactionData(SystemData *sysData)
{
	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		centerStringOnly(UI_ERROR_SYSTEM_DATA_IS_NULL);
		sleep(MID_SLEEP);
		return;
	}

	FILE *transactionFile = fopen(TRANSACTION_DATA_FILE_PATH, "w");
	if (transactionFile == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_TRANSACTION_DATA_FILE_NOT_FOUND);
		centerStringOnly(UI_ERROR_TRANSACTION_DATA_FILE_NOT_FOUND);
		sleep(MID_SLEEP);
		return;
	}
	for (size_t i = 0; i < sysData->transactionCount; i++)
	{
		fprintf(transactionFile, "%d|%d|%d|%d|%lf|%d|%lf|%lf|%d|%s|%lf|%s|%d|%s|%s|%s\n", sysData->transactions[i].transactionID, sysData->transactions[i].exchangeRateID, sysData->transactions[i].userID, sysData->transactions[i].fromCurrencyID, sysData->transactions[i].fromCurrencyAmount, sysData->transactions[i].toCurrencyID, sysData->transactions[i].toCurrencyAmount, sysData->transactions[i].exchangeRate, sysData->transactions[i].exchangeRateStatus, sysData->transactions[i].fromCurrencyCode, sysData->transactions[i].fromCurrencyRateToKz, sysData->transactions[i].toCurrencyCode, sysData->transactions[i].transactionStatus, sysData->transactions[i].createdAt, sysData->transactions[i].updatedAt, sysData->transactions[i].deletedAt);
	}
	fclose(transactionFile);
	return;
}

// Load transaction Data to the structured transaction database file.
void loadTransactionData(SystemData *sysData)
{
	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		centerStringOnly(UI_ERROR_SYSTEM_DATA_IS_NULL);
		sleep(MID_SLEEP);
		return;
	}

	FILE *transactionFile = fopen(TRANSACTION_DATA_FILE_PATH, "r");
	if (transactionFile == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_TRANSACTION_DATA_FILE_NOT_FOUND);
		centerStringOnly(UI_ERROR_TRANSACTION_DATA_FILE_NOT_FOUND);
		sleep(MID_SLEEP);
		return;
	}

	// Initialize variables for reading data
	int _transactionID, _exchangeRateID, _userID, _fromCurrencyID, _toCurrencyID, _exchangeRateStatus, _transactionStatus;
	double _fromCurrencyAmount, _toCurrencyAmount, _exchangeRate, _fromCurrencyRateToKz;
	char _fromCurrencyCode[MAX_CURRENCY_CODE_LENGTH], _toCurrencyCode[MAX_CURRENCY_CODE_LENGTH], _createdAt[MAX_DATE_LENGTH], _updatedAt[MAX_DATE_LENGTH], _deletedAt[MAX_DATE_LENGTH];

	// Check if transaction capacity need adjustment [Verifique se a capacidade de transação precisa de ajuste]
	if (sysData->transactionCount >= sysData->transactionCapacity)
	{
		size_t newCapacity = (sysData->transactionCapacity + 2) * 2;
		TransactionInfo *tempTransactionSize = realloc(sysData->transactions, sizeof(TransactionInfo) * sysData->transactionCapacity);
		if (!tempTransactionSize)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			sleep(MID_SLEEP);
			return;
		}
		sysData->transactions = tempTransactionSize;
		sysData->transactionCapacity = newCapacity;
	}

	// Initializing syData->transactionCount to 0
	sysData->transactionCount = 0;
	// Read data from transaction file and store it in the transaction structure
	while (fscanf(transactionFile, "%d|%d|%d|%d|%lf|%d|%lf|%lf|%d|%9[^|]|%lf|%9[^|]|%d|%99[^|]|%99[^|]|%99[^|]\n", &_transactionID, &_exchangeRateID, &_userID, &_fromCurrencyID, &_fromCurrencyAmount, &_toCurrencyID, &_toCurrencyAmount, &_exchangeRate, &_exchangeRateStatus, _fromCurrencyCode, &_fromCurrencyRateToKz, _toCurrencyCode, &_transactionStatus, _createdAt, _updatedAt, _deletedAt) != EOF && sysData->transactionCount < sysData->transactionCapacity)
	{
		// check if transaction capacity need adjustment [Verifique se a capacidade de transação precisa de ajuste]
		if (sysData->transactionCount >= sysData->transactionCapacity)
		{
			size_t newCapacity = (sysData->transactionCapacity + 2) * 2;
			TransactionInfo *tempTransactionSize = realloc(sysData->transactions, sizeof(TransactionInfo) * sysData->transactionCapacity);
			if (!tempTransactionSize)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
				sleep(MID_SLEEP);
				return;
			}
			sysData->transactions = tempTransactionSize;
			sysData->transactionCapacity = newCapacity;
		}
		// Add transaction data from file to transaction structure
		sysData->transactions[sysData->transactionCount].transactionID = _transactionID;
		sysData->transactions[sysData->transactionCount].exchangeRateID = _exchangeRateID;
		sysData->transactions[sysData->transactionCount].userID = _userID;
		sysData->transactions[sysData->transactionCount].fromCurrencyID = _fromCurrencyID;
		sysData->transactions[sysData->transactionCount].fromCurrencyAmount = _fromCurrencyAmount;
		sysData->transactions[sysData->transactionCount].toCurrencyID = _toCurrencyID;
		sysData->transactions[sysData->transactionCount].toCurrencyAmount = _toCurrencyAmount;
		sysData->transactions[sysData->transactionCount].exchangeRate = _exchangeRate;
		sysData->transactions[sysData->transactionCount].exchangeRateStatus = _exchangeRateStatus;
		sysData->transactions[sysData->transactionCount].fromCurrencyCode = strdup(_fromCurrencyCode);
		if (!sysData->transactions[sysData->transactionCount].fromCurrencyCode)
		{
			logAndFreeTransaction(sysData, sysData->transactionCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}

		sysData->transactions[sysData->transactionCount].fromCurrencyRateToKz = _fromCurrencyRateToKz;

		sysData->transactions[sysData->transactionCount].toCurrencyCode = strdup(_toCurrencyCode);
		if (!sysData->transactions[sysData->transactionCount].toCurrencyCode)
		{
			logAndFreeTransaction(sysData, sysData->transactionCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}
		sysData->transactions[sysData->transactionCount].transactionStatus = _transactionStatus;

		sysData->transactions[sysData->transactionCount].createdAt = strdup(_createdAt);
		if (!sysData->transactions[sysData->transactionCount].createdAt)
		{
			logAndFreeTransaction(sysData, sysData->transactionCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}

		sysData->transactions[sysData->transactionCount].updatedAt = strdup(_updatedAt);
		if (!sysData->transactions[sysData->transactionCount].updatedAt)
		{
			logAndFreeTransaction(sysData, sysData->transactionCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}
		sysData->transactions[sysData->transactionCount].deletedAt = strdup(_deletedAt);

		if (!sysData->transactions[sysData->transactionCount].deletedAt)
		{
			logAndFreeTransaction(sysData, sysData->transactionCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}
		sysData->transactionCount++;
	}
	fclose(transactionFile);
	return;
}

void freeTransactionData(SystemData *sysData)
{
	if (sysData == NULL || sysData->transactions == NULL)
	{
		return;
	}
	for (size_t i = 0; i < sysData->transactionCount; i++)
	{
		safefree(sysData->transactions[i].fromCurrencyCode);
		safefree(sysData->transactions[i].toCurrencyCode);
		safefree(sysData->transactions[i].createdAt);
		safefree(sysData->transactions[i].updatedAt);
		safefree(sysData->transactions[i].deletedAt);
	}
	free(sysData->transactions);
	sysData->transactions = NULL;
	sysData->transactionCount = 0;
	sysData->transactionCapacity = 0;
	return;
}

// Helper function for logging and freeing fields
void logAndFreeTransaction(SystemData *sysData, size_t index, const char *message)
{
	logMessages(LOG_ERROR, message);
	free(sysData->transactions[index].fromCurrencyCode);
	free(sysData->transactions[index].toCurrencyCode);
	free(sysData->transactions[index].createdAt);
	free(sysData->transactions[index].updatedAt);
	free(sysData->transactions[index].deletedAt);
	sleep(MID_SLEEP);
}
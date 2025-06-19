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

void createTransaction(SystemData *sysData, int exchangeRateID, int userID, int fromCurrencyID, double fromCurrencyAmountToConvert, int toCurrencyID, double toCurrencyAmountConvertedTo, double exchangeRate, int transactionStatus, char *createdAt, char *updatedAt, char *deletedAt)
{
	// check if sysData pointer is valid
	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		centerStringOnly(UI_ERROR_SYSTEM_DATA_IS_NULL);
		sleep(MID_SLEEP);
		return;
	}
	int transactionID = randomNumber(80010, 99090);

	// Check if transaction capacity need adjustment [Verifique se a capacidade de transação precisa de ajuste]
	if (sysData->transactionCapacity == 0)
	{
		sysData->transactionCapacity = 2;
	}
	else if (sysData->transactionCount >= sysData->transactionCapacity)
	{
		sysData->transactionCapacity = (sysData->transactionCapacity + 2) * 2;
	}

	// Reallocate Memory to the transaction structure.
	TransactionInfo *tempTransactionSize = realloc(sysData->transactions, sizeof(TransactionInfo) * sysData->transactionCapacity);
	if (tempTransactionSize == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
		centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
		sleep(MID_SLEEP);
		return;
	}
	sysData->transactions = tempTransactionSize;

	// Check if transactionID already exists [Verifique se o ID da transação já existe]
	for (size_t i = 0; i < sysData->transactionCount; i++)
	{
		if (sysData->transactions[i].transactionID == transactionID)
		{
			transactionID = randomNumber(80010, 99090);
			i = -1;
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
	sysData->transactions[sysData->transactionCount].transactionStatus = transactionStatus;

	sysData->transactions[sysData->transactionCount].createdAt = strdup(createdAt);
	if (sysData->transactions[sysData->transactionCount].createdAt == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
		centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
		sleep(MID_SLEEP);
		return;
	}
	sysData->transactions[sysData->transactionCount].updatedAt = strdup(updatedAt);
	if (sysData->transactions[sysData->transactionCount].updatedAt == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
		centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
		free(sysData->transactions[sysData->transactionCount].createdAt);
		sleep(MID_SLEEP);
		return;
	}

	sysData->transactions[sysData->transactionCount].deletedAt = strdup(deletedAt);

	if (sysData->transactions[sysData->transactionCount].deletedAt == NULL)
	{
		strcpy(deletedAt, " ");
		sysData->transactions[sysData->transactionCount].deletedAt = strdup(deletedAt);
		if (sysData->transactions[sysData->transactionCount].deletedAt == NULL)
		{

			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			free(sysData->transactions[sysData->transactionCount].createdAt);
			free(sysData->transactions[sysData->transactionCount].updatedAt);
			sleep(MID_SLEEP);
			return;
		}
	}
	else
	{
		sysData->transactions[sysData->transactionCount].deletedAt = strdup(deletedAt);
		if (sysData->transactions[sysData->transactionCount].deletedAt == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_TRANSACTION_DATA_IS_NULL);
			centerStringOnly(UI_ERROR_TRANSACTION_DATA_IS_NULL);
			free(sysData->transactions[sysData->transactionCount].createdAt);
			free(sysData->transactions[sysData->transactionCount].updatedAt);
			sleep(MID_SLEEP);
			return;
		}

		sysData->transactionCount++;
		saveTransactionData(sysData);
	}
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
		fprintf(transactionFile, "%d|%d|%d|%d|%lf|%d|%lf|%lf|%d|%s|%s\n", sysData->transactions[i].transactionID, sysData->transactions[i].exchangeRateID, sysData->transactions[i].userID, sysData->transactions[i].fromCurrencyID, sysData->transactions[i].fromCurrencyAmount, sysData->transactions[i].toCurrencyID, sysData->transactions[i].toCurrencyAmount, sysData->transactions[i].exchangeRate, sysData->transactions[i].transactionStatus, sysData->transactions[i].createdAt, sysData->transactions[i].updatedAt, sysData->transactions[i].deletedAt);
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
	int _transactionID, _exchangeRateID, _userID, _fromCurrencyID, _toCurrencyID, _transactionStatus;
	double _fromCurrencyAmount, _toCurrencyAmount, _exchangeRate;
	char *_createdAt[MAX_DATE_LENGTH], *_updatedAt[MAX_DATE_LENGTH], *_deletedAt[MAX_DATE_LENGTH];

	// Adjusting transaction capacity if needed.
	if (sysData->transactionCapacity == 0)
	{
		sysData->transactionCapacity = 2;
	}
	else
	{
		sysData->transactionCapacity = sysData->transactionCapacity;
	}
	// Reallocate memory to transactions structure
	TransactionInfo *tempTransactionSize = realloc(sysData->transactions, sizeof(TransactionInfo) * sysData->transactionCapacity);
	if (tempTransactionSize == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
		centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
		sleep(MID_SLEEP);
		return;
	}

	// Assigning tempuTransactions to sysData->transactions
	sysData->transactions = tempTransactionSize;

	// Initializing syData->transactionCount to 0
	sysData->transactionCount = 0;

	// Read data from transaction file and store it in the transaction structure
	while (fscanf(transactionFile, "%d|%d|%d|%d|%lf|%d|%lf|%lf|%d|%99[^|]|%99[^|]\n", &_transactionID, &_exchangeRateID, &_userID, &_fromCurrencyID, &_fromCurrencyAmount, &_toCurrencyID, &_toCurrencyAmount, &_exchangeRate, &_transactionStatus, _createdAt, _updatedAt, _deletedAt) != EOF && sysData->transactionCount < sysData->transactionCapacity)
	{
		// check if transaction capacity need adjustment [Verifique se a capacidade de transação precisa de ajuste]
		if (sysData->transactionCount >= sysData->transactionCapacity)
		{
			sysData->transactionCapacity = (sysData->transactionCapacity + 2) * 2;
			tempTransactionSize = realloc(sysData->transactions, sizeof(TransactionInfo) * sysData->transactionCapacity);
			if (tempTransactionSize == NULL)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
				sleep(MID_SLEEP);
				return;
			}
			sysData->transactions = tempTransactionSize;
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
		sysData->transactions[sysData->transactionCount].transactionStatus = _transactionStatus;
		sysData->transactions[sysData->transactionCount].createdAt = strdup(_createdAt);
		if (sysData->transactions[sysData->transactionCount].createdAt == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			sleep(MID_SLEEP);
			return;
		}
		sysData->transactions[sysData->transactionCount].updatedAt = strdup(_updatedAt);
		if (sysData->transactions[sysData->transactionCount].updatedAt == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			sleep(MID_SLEEP);
			return;
		}
		sysData->transactions[sysData->transactionCount].deletedAt = strdup(_deletedAt);
		if (sysData->transactions[sysData->transactionCount].deletedAt == NULL)
		{
			strcpy(_deletedAt, " ");
			sysData->transactions[sysData->transactionCount].deletedAt = strdup(_deletedAt);
			if (sysData->transactions[sysData->transactionCount].deletedAt == NULL)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
				sleep(MID_SLEEP);
				return;
			}
		}
		else
		{
			sysData->transactions[sysData->transactionCount].deletedAt = strdup(_deletedAt);
			if (sysData->transactions[sysData->transactionCount].deletedAt == NULL)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
				sleep(MID_SLEEP);
				return;
			}
		}
		sysData->transactionCount++;
	}
	fclose(transactionFile);
	return;
}

void freeTransactionData(SystemData *sysData)
{
	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		centerStringOnly(UI_ERROR_SYSTEM_DATA_IS_NULL);
		sleep(MID_SLEEP);
		return;
	}
	for (size_t i = 0; i < sysData->transactionCount; i++)
	{
		free(sysData->transactions[i].createdAt);
		free(sysData->transactions[i].updatedAt);
		free(sysData->transactions[i].deletedAt);
	}
	free(sysData->transactions);
	return;
}
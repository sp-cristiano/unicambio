#include "unicambio.h"
#include "exchangeRateFunctions.h"
#include "structures.h"
#include "messages.h"
#include "logger.h"
#include "utilities.h"

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

		int exchangeRateID = randomNumber(60000, 80000), transactionID = randomNumber(80010, 99090);

		// check if exchangeRateID already exists [Verifique se o ID da taxa de câmbio já existe]
		for (size_t i = 0; i < sysData->exchangeRateCount; i++)
		{
			if (sysData->exchangeRates[i].exchangeRateID == exchangeRateID)
			{
				exchangeRateID = randomNumber(60000, 80000);
				i = -1;
			}
		}

		// Get from currency Rate by from currency id
		double fromCurrencyRate = getCurrencyRateByID(sysData, fromCurrencyID);

		// Convert from currency to Kz
		double fromCurrencyRateToKz = ((fromCurrencyAmountToConvert) / (fromCurrencyRate));

		// Get from currency Code
		char *fromCurrencyCode = getCurrencyCodeByID(sysData, fromCurrencyID);

		// Get to currency Rate by to currency id
		double toCurrencyRate = getCurrencyRateByID(sysData, toCurrencyID);

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

		// ADD TRANSACTION TO TRANSACTION INFO HISTORY
		int transactionStatus = active;

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
		sysData->transactions[sysData->transactionCount].userID = sysData->appContext->currentUserID;
		sysData->transactions[sysData->transactionCount].fromCurrencyID = fromCurrencyID;
		sysData->transactions[sysData->transactionCount].fromCurrencyAmount = fromCurrencyAmountToConvert;
		sysData->transactions[sysData->transactionCount].toCurrencyID = toCurrencyID;
		sysData->transactions[sysData->transactionCount].toCurrencyAmount = toCurrencyAmountConvertedTo;
		sysData->transactions[sysData->transactionCount].exchangeRate = toCurrencyRate;
		sysData->transactions[sysData->transactionCount].transactionStatus = transactionStatus;

		sysData->transactions[sysData->transactionCount].createdAt = sysData->exchangeRates[sysData->exchangeRateCount].createdAt;
		sysData->transactions[sysData->transactionCount].updatedAt = sysData->exchangeRates[sysData->exchangeRateCount].updatedAt;
		sysData->transactions[sysData->transactionCount].deletedAt = sysData->exchangeRates[sysData->exchangeRateCount].deletedAt;

		sysData->transactionCount++;
		sysData->exchangeRateCount++;
		saveExchangeRateData(sysData);
		saveTransactionData(sysData);
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
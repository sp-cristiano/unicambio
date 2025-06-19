#include "../include/unicambio.h"
#include "../include/createDB.h"
#include "../include/messages.h"
#include "../include/logger.h"
#include "../include/utilities.h"

void createDB()
{
	createUserDBFile();
	createCurrencyDBFile();
	createExchangeRateDBFile();
	createTransactionDBFile();
	return;
}

void createUserDBFile()
{
	FILE *checkUserFile = fopen(USER_DATA_FILE_PATH, "r");
	if (checkUserFile == NULL)
	{
		logMessages(LOG_WARNING, UI_ERROR_USER_DATA_FILE_NOT_FOUND);
		centerStringOnly(UI_ERROR_USER_DATA_FILE_NOT_FOUND);
		sleep(MID_SLEEP);
		logMessages(LOG_INFO, UI_CREATING_USER_FILE);
		centerStringOnly(UI_CREATING_USER_FILE);
		sleep(MID_SLEEP);

		FILE *userFile = fopen(USER_DATA_FILE_PATH, "w");
		if (userFile == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_CREATING_USER_DATA_FILE);
			centerStringOnly(UI_ERROR_CREATING_USER_DATA_FILE);
			sleep(MID_SLEEP);
			return;
		}
		if (fclose(userFile) != 0)
		{
			logMessages(LOG_ERROR, UI_ERROR_CLOSING_USER_DATA_FILE);
			centerStringOnly(UI_ERROR_CLOSING_USER_DATA_FILE);
			sleep(MID_SLEEP);
			return;
		}
	}
	else
	{
		if (fclose(checkUserFile) != 0)
		{
			logMessages(LOG_ERROR, UI_ERROR_CLOSING_USER_DATA_FILE);
			centerStringOnly(UI_ERROR_CLOSING_USER_DATA_FILE);
			sleep(MID_SLEEP);
			return;
		}
	}
}

void createCurrencyDBFile()
{
	FILE *checkCurrencyFile = fopen(CURRENCY_DATA_FILE_PATH, "r");
	if (checkCurrencyFile == NULL)
	{
		logMessages(LOG_WARNING, UI_ERROR_CURRENCY_DATA_FILE_NOT_FOUND);
		centerStringOnly(UI_ERROR_CURRENCY_DATA_FILE_NOT_FOUND);
		sleep(MID_SLEEP);
		logMessages(LOG_INFO, UI_CREATING_CURRENCY_FILE);
		centerStringOnly(UI_CREATING_CURRENCY_FILE);
		sleep(MID_SLEEP);

		FILE *currencyFile = fopen("DB/currencies.txt", "w");
		if (currencyFile == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_CREATING_CURRENCY_DATA_FILE);
			centerStringOnly(UI_ERROR_CREATING_CURRENCY_DATA_FILE);
			sleep(MID_SLEEP);
			return;
		}
		if (fclose(currencyFile) != 0)
		{
			logMessages(LOG_ERROR, UI_ERROR_CLOSING_CURRENCY_DATA_FILE);
			centerStringOnly(UI_ERROR_CLOSING_CURRENCY_DATA_FILE);
			sleep(MID_SLEEP);
			return;
		}
	}
	else
	{
		if (fclose(checkCurrencyFile) != 0)
		{
			logMessages(LOG_ERROR, UI_ERROR_CLOSING_CURRENCY_DATA_FILE);
			centerStringOnly(UI_ERROR_CLOSING_CURRENCY_DATA_FILE);
			sleep(MID_SLEEP);
			return;
		}
	}
}

void createExchangeRateDBFile()
{
	FILE *checkExchangeRateFile = fopen(EXCHANGE_RATE_DATA_FILE_PATH, "r");
	if (checkExchangeRateFile == NULL)
	{
		logMessages(LOG_WARNING, UI_ERROR_EXCHANGE_RATE_DATA_FILE_NOT_FOUND);
		centerStringOnly(UI_ERROR_EXCHANGE_RATE_DATA_FILE_NOT_FOUND);
		sleep(MID_SLEEP);
		logMessages(LOG_INFO, UI_CREATING_EXCHANGE_RATE_FILE);
		centerStringOnly(UI_CREATING_EXCHANGE_RATE_FILE);
		sleep(MID_SLEEP);

		FILE *exchangeRateFile = fopen(EXCHANGE_RATE_DATA_FILE_PATH, "w");
		if (exchangeRateFile == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_CREATING_EXCHANGE_RATE_DATA_FILE);
			centerStringOnly(UI_ERROR_CREATING_EXCHANGE_RATE_DATA_FILE);
			sleep(MID_SLEEP);
			return;
		}
		if (fclose(exchangeRateFile) != 0)
		{
			logMessages(LOG_ERROR, UI_ERROR_CLOSING_EXCHANGE_RATE_DATA_FILE);
			centerStringOnly(UI_ERROR_CLOSING_EXCHANGE_RATE_DATA_FILE);
			sleep(MID_SLEEP);
			return;
		}
	}
	else
	{
		if (fclose(checkExchangeRateFile) != 0)
		{
			logMessages(LOG_ERROR, UI_ERROR_CLOSING_EXCHANGE_RATE_DATA_FILE);
			centerStringOnly(UI_ERROR_CLOSING_EXCHANGE_RATE_DATA_FILE);
			sleep(MID_SLEEP);
			return;
		}
	}
}

void createTransactionDBFile()
{
	FILE *checkTransactionFile = fopen(TRANSACTION_DATA_FILE_PATH, "r");
	if (checkTransactionFile == NULL)
	{
		logMessages(LOG_WARNING, UI_ERROR_TRANSACTION_DATA_FILE_NOT_FOUND);
		centerStringOnly(UI_ERROR_TRANSACTION_DATA_FILE_NOT_FOUND);
		sleep(MID_SLEEP);
		logMessages(LOG_INFO, UI_CREATING_TRANSACTION_FILE);
		centerStringOnly(UI_CREATING_TRANSACTION_FILE);
		sleep(MID_SLEEP);

		FILE *transactionFile = fopen(TRANSACTION_DATA_FILE_PATH, "w");
		if (transactionFile == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_CREATING_TRANSACTION_DATA_FILE);
			centerStringOnly(UI_ERROR_CREATING_TRANSACTION_DATA_FILE);
			sleep(MID_SLEEP);
			return;
		}
		if (fclose(transactionFile) != 0)
		{
			logMessages(LOG_ERROR, UI_ERROR_CLOSING_TRANSACTION_DATA_FILE);
			centerStringOnly(UI_ERROR_CLOSING_TRANSACTION_DATA_FILE);
			sleep(MID_SLEEP);
			return;
		}
	}
	else
	{
		if (fclose(checkTransactionFile) != 0)
		{
			logMessages(LOG_ERROR, UI_ERROR_CLOSING_TRANSACTION_DATA_FILE);
			centerStringOnly(UI_ERROR_CLOSING_TRANSACTION_DATA_FILE);
			sleep(MID_SLEEP);
			return;
		}
	}
}

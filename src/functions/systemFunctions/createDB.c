#include "unicambio.h"
#include "createDB.h"
#include "messages.h"
#include "logger.h"
#include "utilities.h"

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
	FILE *checkUserFile = fopen("DB/user.txt", "r");
	if (checkUserFile == NULL)
	{
		logMessages(LOG_WARNING, UI_ERROR_USER_DATA_FILE_NOT_FOUND);
		centerStringOnly(UI_ERROR_USER_DATA_FILE_NOT_FOUND);
		sleep(MID_SLEEP);
		logMessages(LOG_INFO, UI_CREATING_USER_FILE);
		centerStringOnly(UI_CREATING_USER_FILE);
		sleep(MID_SLEEP);

		FILE *userFile = fopen("DB/user.txt", "w");
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
	FILE *checkCurrencyFile = fopen("DB/currencies.txt", "r");
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
	FILE *checkExchangeRateFile = fopen("DB/exchangeRate.txt", "r");
	if (checkExchangeRateFile == NULL)
	{
		logMessages(LOG_WARNING, UI_ERROR_EXCHANGE_RATE_DATA_FILE_NOT_FOUND);
		centerStringOnly(UI_ERROR_EXCHANGE_RATE_DATA_FILE_NOT_FOUND);
		sleep(MID_SLEEP);
		logMessages(LOG_INFO, UI_CREATING_EXCHANGE_RATE_FILE);
		centerStringOnly(UI_CREATING_EXCHANGE_RATE_FILE);
		sleep(MID_SLEEP);

		FILE *exchangeRateFile = fopen("DB/exchangeRate.txt", "w");
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
	FILE *checkTransactionFile = fopen("DB/transactions.txt", "r");
	if (checkTransactionFile == NULL)
	{
		logMessages(LOG_WARNING, UI_ERROR_TRANSACTION_DATA_FILE_NOT_FOUND);
		centerStringOnly(UI_ERROR_TRANSACTION_DATA_FILE_NOT_FOUND);
		sleep(MID_SLEEP);
		logMessages(LOG_INFO, UI_CREATING_TRANSACTION_FILE);
		centerStringOnly(UI_CREATING_TRANSACTION_FILE);
		sleep(MID_SLEEP);

		FILE *transactionFile = fopen("DB/transactions.txt", "w");
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

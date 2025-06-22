#include "../include/unicambio.h"
#include "../include/exchangeRateFunctions.h"
// #include "../include/transactionFunctions.h"
#include "../include/structures.h"
#include "../include/utilities.h"
#include "../include/messages.h"
#include "../include/logger.h"
#include "../include/exchangeRateDefaultSetup.h"

void createExchangeRateDefaultSetup(SystemData *sysData)
{
	FILE *checkRateFile = fopen(EXCHANGE_RATE_DATA_FILE_PATH, "r");
	if (checkRateFile == NULL)
	{
		logMessages(LOG_WARNING, UI_ERROR_EXCHANGE_RATE_DATA_FILE_NOT_FOUND);
		centerStringOnly(UI_ERROR_EXCHANGE_RATE_DATA_FILE_NOT_FOUND);
		sleep(MID_SLEEP);
		return;
	}
	fclose(checkRateFile);

	int fromCurrencyID, toCurrencyID, exchangeRateStatus;
	double fromCurrencyAmountToConvert;

	fromCurrencyID = getCurrencyID(sysData, "USD");
	toCurrencyID = getCurrencyID(sysData, "AOA");
	exchangeRateStatus = active;
	fromCurrencyAmountToConvert = FROM_CURRENCY_AMOUNT_USD;
	char *createdAt = getCurrentDateTime(TYPE_DATE_TIME);
	char *updatedAt = getCurrentDateTime(TYPE_DATE_TIME);
	char *deletedAt = NULL;

	createExchangeRate(sysData,fromCurrencyID, fromCurrencyAmountToConvert, exchangeRateStatus, toCurrencyID, createdAt, updatedAt, deletedAt);


	free(getCurrentDateTime(TYPE_DATE_TIME));
	sleep(MID_SLEEP);
	return;
}

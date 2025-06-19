#include "../include/unicambio.h"
#include "../include/currencyDefaultSetup.h"
#include "../include/messages.h"
#include "../include/logger.h"
#include "../include/structures.h"
#include "../include/utilities.h"
#include "../include/currencyFunctions.h"

void createCurrencyDefaultSetup(SystemData *sysData)
{
	FILE *checkCurrencyFile = fopen(CURRENCY_DATA_FILE_PATH, "r");
	if (checkCurrencyFile == NULL)
	{
		logMessages(LOG_INFO, UI_CREATING_CURRENCY_FILE);
		centerStringOnly(UI_CREATING_CURRENCY_FILE);
		sleep(MID_SLEEP);
		return;
	}
	fclose(checkCurrencyFile);
	// creating the first default currency
	char *name = DEFAULT_CURRENCY_NAME;
	char *abbreviation = DEFAULT_CURRENCY_ABBREVIATION;
	char *code = toUpperCase(DEFAULT_CURRENCY_CODE);
	char *symbol = DEFAULT_CURRENCY_SYMBOL;
	char *country = DEFAULT_CURRENCY_COUNTRY;
	int currencyStatus = active;
	double rateToOneKz = calculateRateToOneKz(DEFAULT_AOA_TO_1_USD_CURRENCY_RATE);
	char *createdAt = getCurrentDateTime(TYPE_DATE_TIME);
	char *updatedAt = getCurrentDateTime(TYPE_DATE_TIME);
	char *deletedAt = NULL;

	createCurrency(sysData, name, abbreviation, code, symbol, country, currencyStatus, rateToOneKz, createdAt, updatedAt, deletedAt);
	free(getCurrentDateTime(TYPE_DATE_TIME));
	// free(code);

	// creating the second default currency
	name = DEFAULT_CURRENCY_NAME_2;
	abbreviation = DEFAULT_CURRENCY_ABBREVIATION_2;
	code = DEFAULT_CURRENCY_CODE_2;
	symbol = DEFAULT_CURRENCY_SYMBOL_2;
	country = DEFAULT_CURRENCY_COUNTRY_2;
	rateToOneKz = calculateRateToOneKz(DEFAULT_AOA_TO_1_AOA_CURRENCY_RATE);
	currencyStatus = active;
	createdAt = getCurrentDateTime(TYPE_DATE_TIME);
	updatedAt = getCurrentDateTime(TYPE_DATE_TIME);
	deletedAt = NULL;

	createCurrency(sysData, name, abbreviation, code, symbol, country, currencyStatus, rateToOneKz, createdAt, updatedAt, deletedAt);
	free(getCurrentDateTime(TYPE_DATE_TIME));
	free(code);
	sleep(MID_SLEEP);
	return;
}

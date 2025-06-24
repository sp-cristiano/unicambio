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

		// Create db file
		createCurrencyDBFile();

		// allocate memory for default currency data
		char *name = (char *)malloc(strlen(MAX_NAME_LENGTH) * sizeof(char));
		char *abbreviation = (char *)malloc(strlen(MAX_NAME_LENGTH) * sizeof(char));
		char *code = (char *)malloc(strlen(MAX_CURRENCY_CODE_LENGTH) * sizeof(char));
		char *symbol = (char *)malloc(strlen(MAX_NAME_LENGTH) * sizeof(char));
		char *country = (char *)malloc(strlen(MAX_NAME_LENGTH) * sizeof(char));
		char *createdAt = (char *)malloc(strlen(MAX_DATE_LENGTH) * sizeof(char));
		char *updatedAt = (char *)malloc(strlen(MAX_DATE_LENGTH) * sizeof(char));
		char *deletedAt = (char *)malloc(strlen(MAX_DATE_LENGTH) * sizeof(char));

		if (name == NULL || abbreviation == NULL || code == NULL || symbol == NULL || country == NULL || createdAt == NULL || updatedAt == NULL || deletedAt == NULL)
		{
			logMessages(LOG_ERROR, "Memory allocation for default currency data failed [Alocação de memória para os dados padrão da moeda falhou]");
			centerStringOnly("Memory allocation for default currency data failed [Alocação de memória para os dados padrão da moeda falhou]");
			sleep(MID_SLEEP);
			return;
		}

		// initialize currency data
		strncpy(name, DEFAULT_CURRENCY_NAME, MAX_NAME_LENGTH - 1);
		name[MAX_NAME_LENGTH - 1] = '\0';

		strncpy(abbreviation, DEFAULT_CURRENCY_ABBREVIATION, MAX_NAME_LENGTH - 1);
		abbreviation[MAX_NAME_LENGTH - 1] = '\0';

		strncpy(code, DEFAULT_CURRENCY_CODE, MAX_CURRENCY_CODE_LENGTH - 1);
		code[MAX_CURRENCY_CODE_LENGTH - 1] = '\0';

		strncpy(symbol, DEFAULT_CURRENCY_SYMBOL, MAX_NAME_LENGTH - 1);
		symbol[MAX_NAME_LENGTH - 1] = '\0';

		strncpy(country, DEFAULT_CURRENCY_COUNTRY, MAX_NAME_LENGTH - 1);
		country[MAX_NAME_LENGTH - 1] = '\0';

		int currencyStatus = active;

		double rateToOneKz = calculateRateToOneKz(DEFAULT_AOA_TO_1_USD_CURRENCY_RATE);
		
		strncpy(createdAt, getCurrentDateTime(TYPE_DATE_TIME), MAX_DATE_LENGTH - 1);
		createdAt[MAX_DATE_LENGTH - 1] = '\0';

		strncpy(updatedAt, getCurrentDateTime(TYPE_DATE_TIME), MAX_DATE_LENGTH - 1);
		updatedAt[MAX_DATE_LENGTH - 1] = '\0';

		deletedAt = NULL;

		// create currency
		createCurrency(sysData, name, abbreviation, code, symbol, country, currencyStatus, rateToOneKz, createdAt, updatedAt, deletedAt);

	}

	fclose(checkCurrencyFile);
	// creating the first default currency
	char *name = DEFAULT_CURRENCY_NAME;
	char *abbreviation = DEFAULT_CURRENCY_ABBREVIATION;
	char *code = toUpperCase(DEFAULT_CURRENCY_CODE);
	if (code == NULL)
	{
		code = strdup(DEFAULT_CURRENCY_CODE);
		if (code == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			sleep(MID_SLEEP);
			return;
		}
	}
	char *symbol = DEFAULT_CURRENCY_SYMBOL;
	char *country = DEFAULT_CURRENCY_COUNTRY;
	int currencyStatus = active;
	double rateToOneKz = calculateRateToOneKz(DEFAULT_AOA_TO_1_USD_CURRENCY_RATE);
	char *createdAt = getCurrentDateTime(TYPE_DATE_TIME);
	char *updatedAt = getCurrentDateTime(TYPE_DATE_TIME);
	char *deletedAt = NULL;

	if (createdAt == NULL || updatedAt == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
		centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
		free(createdAt);
		free(updatedAt);
		free(code);
		return;
	}

	createCurrency(sysData, name, abbreviation, code, symbol, country, currencyStatus, rateToOneKz, createdAt, updatedAt, deletedAt);
	free(createdAt);
	free(updatedAt);
	free(code);

	// creating the second default currency
	name = DEFAULT_CURRENCY_NAME_2;
	abbreviation = DEFAULT_CURRENCY_ABBREVIATION_2;
	code = toUpperCase(DEFAULT_CURRENCY_CODE_2);
	if (code == NULL)
	{
		code = strdup(DEFAULT_CURRENCY_CODE);
		if (code == NULL)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			sleep(MID_SLEEP);
			return;
		}
	}
	symbol = DEFAULT_CURRENCY_SYMBOL_2;
	country = DEFAULT_CURRENCY_COUNTRY_2;
	rateToOneKz = calculateRateToOneKz(DEFAULT_AOA_TO_1_AOA_CURRENCY_RATE);
	currencyStatus = active;
	createdAt = getCurrentDateTime(TYPE_DATE_TIME);
	updatedAt = getCurrentDateTime(TYPE_DATE_TIME);
	deletedAt = NULL;
	if (createdAt == NULL || updatedAt == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
		centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
		free(createdAt);
		free(updatedAt);
		free(code);
		return;
	}

	createCurrency(sysData, name, abbreviation, code, symbol, country, currencyStatus, rateToOneKz, createdAt, updatedAt, deletedAt);

	free(createdAt);
	free(updatedAt);
	free(code);
	sleep(MID_SLEEP);
	return;
}

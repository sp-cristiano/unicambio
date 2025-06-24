#include "../include/unicambio.h"
#include "../include/currencyFunctions.h"
#include "../include/structures.h"
#include "../include/messages.h"
#include "../include/logger.h"
#include "../include/utilities.h"

void createCurrency(SystemData *sysData, char *name, char *abbreviation, char *code, char *symbol, char *country, int currencyStatus, double rateToOneKz, char *createdAt, char *updatedAt, char *deletedAt)
{
	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		sleep(MIN_SLEEP);
		return;
	}

	if (currencyStatus == active)
	{
		//  Adjust Capacity if needed [Ajuste a capacidade se necessário]
		if (sysData->currencyCount >= sysData->currencyCapacity)
		{
			size_t newCapacity = (sysData->currencyCapacity + 2) * 2;
			CurrencyInfo *tempCurrencySize = realloc(sysData->currencies, sizeof(CurrencyInfo) * newCapacity);
			if (!tempCurrencySize)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
				sleep(MIN_SLEEP);
				return;
			}
			sysData->currencies = tempCurrencySize;
			sysData->currencyCapacity = newCapacity;
		}

		int currencyID = randomNumber(10000, 11000);

		// check if currency already exists [Verifique se a moeda já existe]
		if (sysData->currencies != NULL && sysData->currencyCount > 0)
		{
			for (size_t i = 0; i < sysData->currencyCount; i++)
			{
				if (sysData->currencies[i].currencyID == currencyID)
				{
					currencyID = randomNumber(10000, 50000);
					i = 0;
					continue;
				}
				if ((sysData->currencies[i].name && strcmp(sysData->currencies[i].name, name) == 0) ||
						(sysData->currencies[i].abbreviation && strcmp(sysData->currencies[i].abbreviation, abbreviation) == 0) ||
						(sysData->currencies[i].code && strcmp(sysData->currencies[i].code, code) == 0))
				{
					logMessages(LOG_ERROR, UI_ERROR_CURRENCY_EXISTS);
					centerStringOnly(UI_ERROR_CURRENCY_EXISTS);
					sleep(MIN_SLEEP);
					return;
				}
			}
		}
		// Allocate memory for currency data and copy strings for new currency data. [Aloque memória para dados de moeda e copie strings para dados de nova moeda.]

		sysData->currencies[sysData->currencyCount].currencyID = currencyID;

		sysData->currencies[sysData->currencyCount].name = strdup(name);
		if (!sysData->currencies[sysData->currencyCount].name)
		{
			logAndFreeCurrency(sysData, sysData->currencyCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}

		sysData->currencies[sysData->currencyCount].abbreviation = strdup(abbreviation);
		if (!sysData->currencies[sysData->currencyCount].abbreviation)
		{
			logAndFreeCurrency(sysData, sysData->currencyCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}

		sysData->currencies[sysData->currencyCount].code = strdup(code);
		if (!sysData->currencies[sysData->currencyCount].code)
		{
			logAndFreeCurrency(sysData, sysData->currencyCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}

		sysData->currencies[sysData->currencyCount].symbol = strdup(symbol);
		if (!sysData->currencies[sysData->currencyCount].symbol)
		{
			logAndFreeCurrency(sysData, sysData->currencyCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}

		sysData->currencies[sysData->currencyCount].country = strdup(country);
		if (!sysData->currencies[sysData->currencyCount].country)
		{
			logAndFreeCurrency(sysData, sysData->currencyCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}

		sysData->currencies[sysData->currencyCount].currencyStatus = currencyStatus;

		sysData->currencies[sysData->currencyCount].rateToOneKz = rateToOneKz;

		sysData->currencies[sysData->currencyCount].createdAt = strdup(createdAt);
		if (!sysData->currencies[sysData->currencyCount].createdAt)
		{
			logAndFreeCurrency(sysData, sysData->currencyCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}
		sysData->currencies[sysData->currencyCount].updatedAt = strdup(updatedAt);
		if (!sysData->currencies[sysData->currencyCount].updatedAt)
		{
			logAndFreeCurrency(sysData, sysData->currencyCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}

		if (deletedAt != NULL)
		{
			sysData->currencies[sysData->currencyCount].deletedAt = strdup(deletedAt);
		}
		else
		{
			sysData->currencies[sysData->currencyCount].deletedAt = strdup(" ");
		}
		if (!sysData->currencies[sysData->currencyCount].deletedAt)
		{
			logAndFreeCurrency(sysData, sysData->currencyCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}
		sysData->currencyCount++;
		saveCurrencyData(sysData);
	}
	else
	{
		logMessages(LOG_ERROR, UI_ERROR_CURRENCY_DATA_STATUS_NOT_ACTIVE);
		centerStringOnly(UI_ERROR_CURRENCY_DATA_STATUS_NOT_ACTIVE);
		sleep(MID_SLEEP);
	}
	return;
}

void saveCurrencyData(SystemData *sysData)
{

	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		fprintf(stderr, "%s\n", UI_ERROR_SYSTEM_DATA_IS_NULL);
		return;
	}
	FILE *currencyFile = fopen(CURRENCY_DATA_FILE_PATH, "w");
	if (currencyFile == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_WRITING_CURRENCY_DATA_FILE);
		centerStringOnly(UI_ERROR_WRITING_CURRENCY_DATA_FILE);
		sleep(MID_SLEEP);
		return;
	}
	for (size_t i = 0; i < sysData->currencyCount; i++)
	{
		fprintf(currencyFile, "%d|%s|%s|%s|%s|%s|%d|%lf|%s|%s|%s\n", sysData->currencies[i].currencyID, sysData->currencies[i].name, sysData->currencies[i].abbreviation, sysData->currencies[i].code, sysData->currencies[i].symbol, sysData->currencies[i].country, sysData->currencies[i].currencyStatus, sysData->currencies[i].rateToOneKz, sysData->currencies[i].createdAt, sysData->currencies[i].updatedAt, sysData->currencies[i].deletedAt);
	}
	fclose(currencyFile);
	return;
}

// Load Currency Data to the structured currency database from the database file.

void loadCurrencyData(SystemData *sysData)
{
	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		centerStringOnly(UI_ERROR_SYSTEM_DATA_IS_NULL);
		sleep(MID_SLEEP);
		return;
	}
	FILE *currencyFile = fopen(CURRENCY_DATA_FILE_PATH, "r");
	if (currencyFile == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_READING_CURRENCY_DATA_FILE);
		centerStringOnly(UI_ERROR_READING_CURRENCY_DATA_FILE);
		sleep(MID_SLEEP);
		return;
	}
	// initialize variables for reading data
	int _currencyID, _currencyStatus;
	double _rateToOneKz;
	char _name[MAX_NAME_LENGTH], _abbreviation[MAX_CURRENCY_CODE_LENGTH], _code[MAX_CURRENCY_CODE_LENGTH], _symbol[MAX_NAME_LENGTH], _country[MAX_NAME_LENGTH], _createdAt[MAX_DATE_LENGTH], _updatedAt[MAX_DATE_LENGTH], _deletedAt[MAX_DATE_LENGTH];

	if (sysData->currencyCount >= sysData->currencyCapacity)
	{
		size_t newCapacity = (sysData->currencyCapacity + 2) * 2;
		CurrencyInfo *tempCurrencySize = realloc(sysData->currencies, sizeof(CurrencyInfo) * newCapacity);
		if (!tempCurrencySize)
		{
			logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
			sleep(MIN_SLEEP);
			return;
		}
		sysData->currencies = tempCurrencySize;
		sysData->currencyCapacity = newCapacity;
	}

	// Initializing sysData->currencyCount to 0
	sysData->currencyCount = 0;

	while (fscanf(currencyFile, "%d|%149[^|]|%9[^|]|%9[^|]|%149[^|]|%149[^|]|%d|%lf|%99[^|]|%99[^|]|%99[^|]\n", &_currencyID, _name, _abbreviation, _code, _symbol, _country, &_currencyStatus, &_rateToOneKz, _createdAt, _updatedAt, _deletedAt) != EOF && sysData->currencyCount < sysData->currencyCapacity)
	{
		if (sysData->currencyCount >= sysData->currencyCapacity)
		{
			// resize the currency capacity if necessary
			size_t newCapacity = (sysData->currencyCapacity + 2) * 2;
			CurrencyInfo *tempCurrencySize = realloc(sysData->currencies, sizeof(CurrencyInfo) * newCapacity);
			if (!tempCurrencySize)
			{
				logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
				centerStringOnly(UI_ERROR_MEMORY_ALLOCATION_FAILED);
				sleep(MIN_SLEEP);
				return;
			}
			sysData->currencies = tempCurrencySize;
			sysData->currencyCapacity = newCapacity;
		}

		// Add user to database
		sysData->currencies[sysData->currencyCount].currencyID = _currencyID;

		sysData->currencies[sysData->currencyCount].name = strdup(_name);
		if (!sysData->currencies[sysData->currencyCount].name)
		{
			logAndFreeCurrency(sysData, sysData->currencyCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}

		sysData->currencies[sysData->currencyCount].abbreviation = strdup(_abbreviation);
		if (!sysData->currencies[sysData->currencyCount].abbreviation)
		{
			logAndFreeCurrency(sysData, sysData->currencyCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}

		sysData->currencies[sysData->currencyCount].code = strdup(_code);
		if (!sysData->currencies[sysData->currencyCount].code)
		{
			logAndFreeCurrency(sysData, sysData->currencyCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}

		sysData->currencies[sysData->currencyCount].symbol = strdup(_symbol);
		if (!sysData->currencies[sysData->currencyCount].symbol)
		{
			logAndFreeCurrency(sysData, sysData->currencyCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}

		sysData->currencies[sysData->currencyCount].country = strdup(_country);
		if (!sysData->currencies[sysData->currencyCount].country)
		{
			logAndFreeCurrency(sysData, sysData->currencyCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}

		sysData->currencies[sysData->currencyCount].currencyStatus = _currencyStatus;

		sysData->currencies[sysData->currencyCount].rateToOneKz = _rateToOneKz;

		sysData->currencies[sysData->currencyCount].createdAt = strdup(_createdAt);
		if (!sysData->currencies[sysData->currencyCount].createdAt)
		{
			logAndFreeCurrency(sysData, sysData->currencyCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}
		sysData->currencies[sysData->currencyCount].updatedAt = strdup(_updatedAt);
		if (!sysData->currencies[sysData->currencyCount].updatedAt)
		{
			logAndFreeCurrency(sysData, sysData->currencyCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}
		sysData->currencies[sysData->currencyCount].deletedAt = strdup(_deletedAt);
		if (!sysData->currencies[sysData->currencyCount].deletedAt)
		{
			logAndFreeCurrency(sysData, sysData->currencyCount, UI_ERROR_MEMORY_ALLOCATION_FAILED);
			return;
		}

		sysData->currencyCount++;
	}
	// check for emptyfile scenerio
	if (sysData->currencyCount == 0)
	{
		logMessages(LOG_ERROR, UI_ERROR_CURRENCY_DATA_IS_EMPTY);
		centerStringOnly(UI_ERROR_CURRENCY_DATA_IS_EMPTY);
		sleep(MID_SLEEP);
		return;
	}
 if (ferror(currencyFile))
	{
		logMessages(LOG_ERROR, UI_ERROR_READING_CURRENCY_DATA_FILE);
		centerStringOnly(UI_ERROR_READING_CURRENCY_DATA_FILE);
		sleep(MID_SLEEP);
		return;
	}
	fclose(currencyFile);
	return;
}

// Free Currency Data
void freeCurrencyData(SystemData *sysData)
{
	if (sysData == NULL || sysData->currencies == NULL)
	{
		return;
	}

	for (size_t i = 0; i < sysData->currencyCount; i++)
	{
		safefree(sysData->currencies[i].name);
		safefree(sysData->currencies[i].abbreviation);
		safefree(sysData->currencies[i].code);
		safefree(sysData->currencies[i].symbol);
		safefree(sysData->currencies[i].country);
		safefree(sysData->currencies[i].createdAt);
		safefree(sysData->currencies[i].updatedAt);
		safefree(sysData->currencies[i].deletedAt);
	}
	free(sysData->currencies);
	sysData->currencies = NULL;
	sysData->currencyCount = 0;
	sysData->currencyCapacity = 0;

	return;
}

// Helper functin for logging and freeing fields
void logAndFreeCurrency(SystemData *sysData, size_t index, const char *message)
{
	logMessages(LOG_ERROR, message);
	free(sysData->currencies[index].name);
	free(sysData->currencies[index].abbreviation);
	free(sysData->currencies[index].code);
	free(sysData->currencies[index].symbol);
	free(sysData->currencies[index].country);
	free(sysData->currencies[index].createdAt);
	free(sysData->currencies[index].updatedAt);
	free(sysData->currencies[index].deletedAt);
	sleep(MID_SLEEP);
}
#ifndef CURRENCY_FUNCTIONS_H
#define CURRENCY_FUNCTIONS_H
#include "../include/structures.h"

// Create Currency
void createCurrency(SystemData *sysData, char *name, char *abbreviation, char *code, char *symbol, char *country, int currencyStatus, double rateToOneKz, char *createdAt, char *updatedAt, char *deletedAt);

// save currency data to file
void saveCurrencyData(SystemData *sysData);

// load currency data from file
void loadCurrencyData(SystemData *sysData);

// free currency data
void freeCurrencyData(SystemData *sysData);
#endif // CURRENCY_FUNCTIONS_H
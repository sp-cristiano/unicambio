#ifndef CURRENCY_FUNCTION_H
#define CURRENCY_FUNCTION_H

#include "../include/structures.h"
#include "../include/enum.h"

StatusInfo creatCurrency(SystemData *sysData, char *name, char *code, char *symbol, char *country, int currencyStatus, double rateToOneKz, char *dateCreated, char *lastUpdated, char *dateDeleted);

StatusInfo saveCurrencyData(SystemData *sysData);
StatusInfo loadCurrencyData(SystemData *sysData);

StatusInfo freeCurrencyData(SystemData *sysData);
StatusInfo freeCurrencyVariable(char *name, char *code, char *symbol, char *country, char *dateCreated, char *lastUpdated, char *dateDeleted);
StatusInfo freeMemoryAllocatedToCurrencyStructure(SystemData *sysData);

#endif // CURRENCY_FUNCTION_H

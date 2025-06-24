#ifndef EXCHANGE_RATE_FUNCTIONS_H
#define EXCHANGE_RATE_FUNCTIONS_H

#include "../include/structures.h"

void createExchangeRate(SystemData *sysData, int fromCurrencyID, double fromCurrencyAmountToConvert, int exchangeRateStatus, int toCurrencyID, char *createdAt, char *updatedAt, char *deletedAt);
void saveExchangeRateData(SystemData *sysData);
void loadExchangeRateData(SystemData *sysData);
void freeExchangeRateData(SystemData *sysData);
void logAndFreeExchangeRate(SystemData *sysData, size_t index, const char *message);

#endif // EXCHANGE_RATE_FUNCTIONS_H
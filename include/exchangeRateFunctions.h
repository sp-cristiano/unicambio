#ifndef EXCHANGE_RATE_FUNCTIONS_H
#define EXCHANGE_RATE_FUNCTIONS_H

void createExchangeRate(SystemData sysData, int fromCurrencyID, double fromCurrencyAmountToConvert, int exchangeRateStatus, int toCurrencyID, char *createdAt, char *updatedAt, char *deletedAt);

#endif // EXCHANGE_RATE_FUNCTIONS_H
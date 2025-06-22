#ifndef TRANSACTION_FUNCTIONS_H
#define TRANSACTION_FUNCTIONS_H

#include "../include/structures.h"

// Create Transaction
void createTransaction(SystemData *sysData, int exchangeRateID, int userID, int fromCurrencyID, double fromCurrencyAmountToConvert, int toCurrencyID, double toCurrencyAmountConvertedTo, double exchangeRate, int transactionStatus, char *createdAt, char *updatedAt, char *deletedAt);

// Save Transaction
void saveTransactionData(SystemData *sysData);

// Load Transaction
void loadTransactionData(SystemData *sysData);

// Free Transaction
void freeTransactionData(SystemData *sysData);

#endif // TRANSACTION_FUNCTIONS_H
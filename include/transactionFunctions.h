#ifndef TRANSACTION_FUNCTIONS_H
#define TRANSACTION_FUNCTIONS_H

#include "../include/structures.h"

// Create Transaction
void createTransaction(SystemData *sysData, int exchangeRateID, int userID, int fromCurrencyID, double fromCurrencyAmountToConvert, int toCurrencyID, double toCurrencyAmountConvertedTo, double exchangeRate, int exchangeRateStatus, char *fromCurrencyCode, double fromCurrencyRateToKz, char *toCurrencyCode, int transactionStatus, char *createdAt, char *updatedAt, char *deletedAt);

// Save Transaction
void saveTransactionData(SystemData *sysData);

// Load Transaction
void loadTransactionData(SystemData *sysData);

// Free Transaction
void freeTransactionData(SystemData *sysData);

// Helper function for logging and freeing fields
void logAndFreeTransaction(SystemData *sysData, size_t index, const char *message);
#endif // TRANSACTION_FUNCTIONS_H

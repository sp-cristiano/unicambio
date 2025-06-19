#include "../include/structures.h"
#include "../include/userFunctions.h"
#include "../include/currencyFunctions.h"
#include "../include/exchangeRateFunctions.h"
#include "../include/transactionFunctions.h"
void saveSystemData(SystemData *sysData)
{
	saveUserData(sysData);
	saveCurrencyData(sysData);
	saveExchangeRateData(sysData);
	saveTransactionData(sysData);
}
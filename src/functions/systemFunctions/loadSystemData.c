#include "../include/structures.h"
#include "../include/userFunctions.h"
#include "../include/currencyFunctions.h"
#include "../include/exchangeRateFunctions.h"
#include "../include/transactionFunctions.h"
#include "../include/loadSystemData.h"
void loadSystemData(SystemData *sysData)
{

	loadUserData(sysData);
	loadCurrencyData(sysData);
	loadExchangeRateData(sysData);
	loadTransactionData(sysData);
}
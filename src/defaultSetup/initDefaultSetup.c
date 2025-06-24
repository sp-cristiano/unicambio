#include "../include/unicambio.h"
#include "../include/initDefaultSetup.h"
#include "../include/messages.h"
#include "../include/logger.h"
#include "../include/structures.h"
#include "../include/userDefaultSetup.h"
#include "../include/currencyDefaultSetup.h"
#include "../include/exchangeRateDefaultSetup.h"
#include "../include/transactionDefaultSetup.h"

void initDefaultSetup(SystemData *sysData){
	createUserDefaultSetup(sysData);
	createCurrencyDefaultSetup(sysData);
	createExchangeRateDefaultSetup(sysData);
	// sleep(MAX_SLEEP);
	return;
}
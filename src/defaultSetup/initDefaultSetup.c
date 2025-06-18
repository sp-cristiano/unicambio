#include "unicambio.h"
#include "initDefaultSetup.h"
#include "messages.h"
#include "logger.h"
#include "structures.h"
#include "adminUserDefaultSetup.h"
#include "currencyDefaultSetup.h"
#include "exchangeRateDefaultSetup.h"
#include "transactionDefaultSetup.h"

void initDefaultSetup(SystemData *sysData)
{
	createAdminUserDefaultSetup(sysData);
	createCurrencyDefaultSetup(sysData);
	createExchangeRateDefaultSetup(sysData);
	createTransactionDefaultSetup(sysData);
}
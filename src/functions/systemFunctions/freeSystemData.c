
#include "../include/freeSystemData.h"
#include "../include/structures.h"
#include "../include/userFunctions.h"
#include "../include/currencyFunctions.h"
#include "../include/exchangeRateFunctions.h"
#include "../include/transactionFunctions.h"
#include "../include/env.h"

void freeSystemData(SystemData *sysData)
{
	// Free all dynamically allocated memory
	if (sysData->users != NULL)
	{
		freeMemoryAllocatedToUserStructure(sysData);
	}

	if (sysData->currencies != NULL)
	{
		freeMemoryAllocatedToCurrencyStructure(sysData);
	}

	if (sysData->exchangeRates != NULL)
	{
		freeMemoryAllocatedToExchangeRateStructure(sysData);
	}

	if (sysData->transactions != NULL)
	{
		freeMemoryAllocatedToTransactionStructure(sysData);
	}

	// Free appContext fields safely
	if (sysData->appContext != NULL)
	{
		freeMemoryAllocatedToAppContextStructure(sysData);
	}
}
#include "../include/freeSystemData.h"
#include "../include/structures.h"
#include "../include/userFunction.h"
#include "../include/enum.h"
#include "../include/utilities.h"
#include "../include/env.h"
#include "../include/logger.h"

StatusInfo freeSystemData(SystemData *sysData)
{
	if (!sysData)
	{
		logPrintMessage(LOG_ERROR, "System data is Null. Failed to free system data [ Dados do sistema nulo. Falha ao liberar dados do sistema ]", yes);
		return failed;
	}

	if (freeMemoryAllocatedToUserStructure(sysData) != successful)
	{
		return failed;
	}
	if (freeMemoryAllocatedToAppContextStructure(sysData) != successful)
	{
		return failed;
	}
	if (freeMemoryAllocatedToCurrencyStructure(sysData) != successful)
	{
		return failed;
	}

	// TODO: free memory allocated to exchange rate
	// if (freeMemoryAllocatedToExchangeRateStructure(sysData) != successful)
	// {
	// 	return failed;
	// }
	// if (freeMemoryAllocatedToTransactionStructure(sysData) != successful)
	// {
	// 	return failed;
	// }

	sysData = NULL;
	logPrintMessage(LOG_SUCCESS, "System data freed successfully [ Dados do sistema liberados com sucesso ]", yes);
	return successful;
}
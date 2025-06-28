#include "../include/unicambio.h"
#include "../include/structures.h"
#include "../include/enum.h"
#include "../include/initDefaultSetup.h"
#include "../include/userDefaultSetup.h"
#include "../include/currencyDefaultSetup.h"
#include "../include/utilities.h"
#include "../include/env.h"
#include "../include/logger.h"

StatusInfo initDefaultSetup(SystemData *sysData)
{
	StatusInfo status;
	logPrintMessage(LOG_INFO, "Initializing default system setup [ Iniciando configuração padrão do sistema ]", yes);


	processing();

	if (loadEnvFile(sysData, ENV_FILE_PATH) != successful)
	{
		status = failed;
		logPrintMessage(LOG_ERROR, "Failed to load environment file [ Falha ao carregar o arquivo de ambiente ]", yes);
		return status;
	}

	processing();

	if (createUserDefaultSetup(sysData) != successful)
	{
		status = failed;
		logPrintMessage(LOG_ERROR, "Failed to create default user setup [ Falha ao criar configuração padrão do usuário ]", yes);
		return status;
	}
	processing();
	if(createCurrencyDefaultSetup(sysData) != successful){
		status = failed;
		logPrintMessage(LOG_ERROR, "Failed to create default currency setup [ Falha ao criar configuração padrão da moeda ]", yes);
		return status;
	}
	processing();
	status = successful;
	return status;
}
/**
 * @file initSystem.c
 * @author Chinedum Odili (https://github.com/sp-cristiano)
 * @brief This file contains the implementation of system initialization settings.
 * [Este arquivo contém a implementação das configurações de inicialização do sistema.]
 * @version 0.1
 * @date 2025-06-05
 *
 * @copyright Copyright (c) 2025
 */

#include "../include/unicambio.h"
#include "../include/structures.h"
#include "../include/messages.h"
#include "../include/logger.h"

/**
 * @brief Initializes the main system data structure with default values and NULL pointers.
 *
 * This function sets all dynamic arrays to `NULL` and counters to `0` in preparation
 * for the system's runtime use. It also sets flags and context-related values for the application.
 * [Esta função inicializa a estrutura principal do sistema com valores padrão e ponteiros nulos.
 * É usada para preparar o sistema para o uso durante o tempo de execução. Define flags e valores relacionados ao contexto da aplicação.]
 *
 * @param sysData Pointer to a `SystemData` struct that will be initialized.
 *
 * This function ensures:
 * - Clean starting point for dynamic memory allocation.
 * - Default safe state before file loading or user actions.
 *
 * The following data components are initialized:
 * - Users
 * - Roles
 * - Currencies
 * - Exchange Rates
 * - Transactions
 * - Application Context (authentication, session flags, etc.)
 * [Esta função garante um ponto de partida limpo para a alocação de memória dinâmica.
 * Estado seguro antes da carregamento de arquivos ou ações do usuário.
 * Os seguintes componentes de dados são inicializados:
 * - Usuários
 * - Papéis
 * - Moedas
 * - Taxas de Câmbio
 * - Transações
 * - Contexto da Aplicação (autenticação, flags de sessão, etc.)]
 * @see SystemData, AppContext
 *
 */

StatusInfo initSystem(SystemData *sysData)
{
	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		return failed;
	}
	sysData->appContext = calloc(1, sizeof(AppContextInfo));
	if (!sysData->appContext)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		return failed;
	}
	sysData->appContextCount = 0;
	sysData->appContextCapacity = 0;
	sysData->appContextLimit = 0;
	sysData->appContext->exitFlag = false;
	sysData->appContext->isAuthenticated = false;
	sysData->appContext->loginAttempts = 0;
	sysData->appContext->session = false;
	sysData->appContext->goBack = false;
	sysData->appContext->currentUserID = 0;
	sysData->appContext->currentUserRoleID = 0;
	sysData->appContext->currentUserName = NULL;

	sysData->users = NULL;
	sysData->userCount = 0;
	sysData->userCapacity = 0;
	sysData->userLimit = 0;

	sysData->currencies = NULL;
	sysData->currencyCount = 0;
	sysData->currencyCapacity = 0;
	sysData->currencyLimit = 0;

	sysData->exchangeRates = NULL;
	sysData->exchangeRateCount = 0;
	sysData->exchangeRateCapacity = 0;
	sysData->exchangeRateLimit = 0;

	sysData->transactions = NULL;
	sysData->transactionCount = 0;
	sysData->transactionCapacity = 0;
	sysData->transactionLimit = 0;

	sysData->systemCount = 0;
	sysData->systemCapacity = 0;
	sysData->systemLimit = 0;
	sysData->systemStatus = 0;
	return successful;
}

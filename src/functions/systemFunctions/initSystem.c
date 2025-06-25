#include "../include/unicambio.h"
#include "../include/structures.h"
#include "../include/enum.h"
#include "../include/logger.h"

StatusInfo initSystem(SystemData *sysData)
{
	StatusInfo status;
	if (!sysData)
	{
		logPrintMessage(LOG_ERROR, "Failed to initialize system [ Falha ao inicializar o sistema ]", yes);
		status = failed;
		return status;
	}

	sysData->appContext = calloc(1, sizeof(AppContextInfo));
	if (!sysData->appContext)
	{
		logPrintMessage(LOG_ERROR, "Failed to initialize application context [ Falha ao inicializar o contexto da aplicação ]", yes);
		status = failed;
		return status;
	}

	sysData->appContext->exitFlag = false;
	sysData->appContext->isAuthenticated = false;
	sysData->appContext->loginAttempts = 0;
	sysData->appContext->session = false;
	sysData->appContext->currentUserID = 0;
	sysData->appContext->currentUserRoleID = 0;
	sysData->appContextCount = 0;
	sysData->appContextCapacity = 0;
	sysData->appContext->session = false;
	sysData->appContext->goBack = false;
	sysData->appContextLimit = 0;
	sysData->appContext->currentUserName = NULL;
	sysData->appContext->adminUserPassword = NULL;
	sysData->appContext->adminUserEmail = NULL;
	sysData->appContext->adminUserPhone = NULL;

	sysData->users = NULL;
	sysData->userCount = 0;
	sysData->userCapacity = 0;
	sysData->userLimit = 0;

	status = successful;

	return status;
}
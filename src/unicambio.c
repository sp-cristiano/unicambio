#include "../include/unicambio.h"
#include "../include/structures.h"
#include "../include/enum.h"
#include "../include/initSystem.h"
#include "../include/initDefaultSetup.h"
#include "../include/loadSystemData.h"
#include "../include/homePageMenu.h"
#include "../include/saveSystemData.h"
#include "../include/freeSystemData.h"
#include "../include/utilities.h"
#include "../include/logger.h"

int main()
{
	clearScreen();
	srand((unsigned int)time(NULL));

	setLocation();

	SystemData sysData;

	if (initSystem(&sysData) != successful)
	{
		logPrintMessage(LOG_ERROR, "Failed to initialize system [ Falha ao inicializar o sistema ]", yes);
		sleep(MID_SLEEP);
		return failed;
	}
	else
	{
		logPrintMessage(LOG_SUCCESS, "System initialized successfully [ Sistema inicializado com sucesso]", yes);
		sleep(MID_SLEEP);
	}

	// loadEnvFile(&sysData, ENV_FILE_PATH);

	initDefaultSetup(&sysData);

	loadSystemData(&sysData);

	homePageMenu(&sysData);

	saveSystemData(&sysData);

	freeSystemData(&sysData);

	return successful;
}
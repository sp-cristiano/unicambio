#include "../include/unicambio.h"
#include "../include/userDefaultSetup.h"
#include "../include/messages.h"
#include "../include/logger.h"
#include "../include/structures.h"
#include "../include/utilities.h"
#include "../include/userFunctions.h"

void createUserDefaultSetup(SystemData *sysData)
{
	FILE *checkUserFile = fopen(USER_DATA_FILE_PATH, "r");
	if (checkUserFile != NULL)
	{
		logMessages(LOG_WARNING, UI_ERROR_USER_DATA_FILE_NOT_FOUND);
		centerStringOnly(UI_ERROR_USER_DATA_FILE_NOT_FOUND);
		sleep(MID_SLEEP);
		return;
	}
	fclose(checkUserFile);

	char *name = DEFAULT_ADMIN_NAME;
	char *userName = DEFAULT_ADMIN_USERNAME;
	char *email = sysData->appContext->ADMIN_USER_EMAIL;
	char *password = sysData->appContext->ADMIN_USER_PASSWORD;
	char *phone = sysData->appContext->ADMIN_USER_PHONE;
	int roleID = ROLE_ADMIN;
	int userStatus = active;
	char *createAt = getCurrentDateTime(TYPE_DATE_TIME);
	char *lastSeen = getCurrentDateTime(TYPE_DATE_TIME);
	char *deleteAt = NULL;

	createUser(sysData, name, userName, email, password, phone, roleID, userStatus, createAt, lastSeen, deleteAt);

	free(getCurrentDateTime(TYPE_DATE_TIME));
	sleep(MID_SLEEP);
}


#ifndef ENV_H
#define ENV_H
#include "../include/structures.h"
#include "../include/enum.h"

StatusInfo loadEnvFile(SystemData *sysData, const char *envFilePath);
StatusInfo freeAppContext(char *currentUserName, char *adminUserPassword, char *adminUserEmail, char *adminUserPhone);
StatusInfo freeMemoryAllocatedToAppContextStructure(SystemData *sysData);

#endif // ENV_H
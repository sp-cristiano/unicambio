#ifndef USER_FUNCTION_H
#define USER_FUNCTION_H

#include "../include/structures.h"
#include "../include/enum.h"

StatusInfo createUser(SystemData *sysData, char *name, char *username, char *email, char *password, char *phone, int roleID, int userStatus, char *dateCreated, char *lastUpdated, char *lastLogin, char *dateDeleted);

StatusInfo saveUserData(SystemData *sysData);

StatusInfo loadUserData(SystemData *sysData);
StatusInfo freeUserData(SystemData *sysData);
StatusInfo freeUserDataVariable(char *name, char *username, char *email, char *password, char *phone, char *dateCreated, char *lastUpdated, char *lastLogin, char *dateDeleted);

StatusInfo freeMemoryAllocatedToUserStructure(SystemData *sysData);

#endif // USER_FUNCTION_H

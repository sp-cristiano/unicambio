

#ifndef AUTH_H
#define AUTH_H
#include "../include/structures.h"
#include "../include/enum.h"

char *hashPassword(const char *password);
int verifyPassword(const char *password, const char *hash);
StatusInfo loginPageMenu(SystemData *sysData);
BoolInfo authenticateUser(SystemData *sysData, char *username, char *password);
StatusInfo grantLoginAccess(SystemData *sysData, int userID);
#endif // AUTH_H
#ifndef OAUTH_H
#define OAUTH_H
#include "structures.h"
char *hashPassword(const char *password);
int verifyPassword(const char *password, const char *hashedPassword);
void loginPageMenu(SystemData *sysData);
int authenticateUser(SystemData *sysData, const char *username, const char *password);
void grantLoginAccess(SystemData *sysData, int userID);
#endif // OAUTH_H
#ifndef ADMIN_FUNCTIONS_H
#define ADMIN_FUNCTIONS_H
#include "../include/structures.h"

// Create User Data [Criar dados de usuários]
void createUser(SystemData *sysData, char *name, char *userName, char *email, char *password, char *phone, int roleID, int userStatus, char *createAt, char *lastSeen, char *deleteAt);

// Save User Data to file
void saveUserData(SystemData *sysData);

// Load User Data
void loadUserData(SystemData *sysData);

// Free User Data
void freeUserData(SystemData *sysData);

#endif // ADMIN_FUNCTIONS_H
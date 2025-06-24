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
// void freeUserData(SystemData *sysData);
void freeUserData(char *name, char *userName, char *email, char *password, char *phone, char *createAt, char *lastSeen, char *deleteAt);

// Free Memory Allocated to User Structure
void freeMemoryAllocatedToUserStructure(SystemData *sysData);

// Helper function for logging and freeing fields
void logAndFreeUser(SystemData *sysData, size_t index, const char *message); // TODO: DELETE THIS LATER
#endif // ADMIN_FUNCTIONS_H
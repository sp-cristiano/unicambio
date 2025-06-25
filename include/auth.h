

#ifndef AUTH_H
#define AUTH_H
#include "../include/structures.h"
char *hashPassword(const char *password);
int verifyPassword(const char *password, const char *hash);
#endif // AUTH_H
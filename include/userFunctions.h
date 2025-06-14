/**
 * @author Chinedum Odili (https://github.com/ChinedumOdili)
 * @version 1.0
 */
/*
*****************************************************************************************
This file is the header file for the unicambio project.
[Este arquivo é o arquivo de cabeçalho para o projeto unicambio.]
*****************************************************************************************
*/
#ifndef USER_FUNCTIONS
#define USER_FUNCTIONS

#include "../include/structures.h"

/*
******************************************************************************************
[Protótipos de funções.]
******************************************************************************************
*/
void createUser(SystemData *sysData, const char *name, const char *username, const char *email, const char *password, const char *phone, int is_active, const time_t created_at, const time_t last_seen, const time_t deleted_at);
#endif // USER_FUNCTIONS
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

/*
 */

#ifndef GLOBALS_H
#define GLOBALS_H

/*
******************************************************************************************
Global variables.
[Variáveis globais.]
******************************************************************************************
*/
// extern char *current_language; // Pointer to the current language setting
extern char *current_date, *current_time;
extern const char *currentUserName, *currentUserRole, *ADMIN_USER_PASSWORD, *ADMIN_USER_EMAIL, *ADMIN_USER_PHONE;
extern int exitFlag, adminPin, is_authenticated, loginAttempts, session, goBack, currentUserID;

#endif // GLOBALS_H

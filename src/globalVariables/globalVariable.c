/*
*******************************************************************************
This file contain the global variables for the unicambio project.
[Este arquivo contém as variáveis globais para o projeto unicambio.]
*******************************************************************************
*/
#include "../include/config.h"
#include "../include/globals.h"

char *current_date, *current_time;
const char *currentUserName = NULL, *currentUserRole = NULL, *ADMIN_USER_PASSWORD = NULL, *ADMIN_USER_EMAIL = NULL, *ADMIN_USER_PHONE = NULL;
int exitFlag = FALSE, adminPin, is_authenticated = FALSE, loginAttempts = 0, session = FALSE, goBack = FALSE, currentUserID;
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
#ifndef OAUTH_FUNCTIONS_H
#define OAUTH_FUNCTIONS_H

#include "../include/structures.h"
/*
******************************************************************************************
Prototypes of functions for default functionss.
[Protótipos de funções.]
******************************************************************************************
*/

//  *** PROTOTYPES FOR OAUTH FUNCTION [PROTÓTIPOS PARA FUNÇÕES DE OAUTH] ***
// Function to display login page [Função para exibir a página de login]
void loginPage(SystemData *sysData);
// Function to login [Função para login]
void grantLoginAccess(SystemData *sysData, int currenUserID);
// Function to authenticate user [Função para autenticar usuário]
int authenticateUser(SystemData *sysData, const char *username, const char *password);
// Function to hash password [Função para hashear senha]
char *hashPassword(const char *password);
// Function to verify password [Função para verificar senha]
int verifyPassword(const char *password, const char *hashedPassword);

#endif // OAUTH_FUNCTIONS_H
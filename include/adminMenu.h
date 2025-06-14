/**
 * @file adminMenu.h
 * @author Chinedum Odili (https://github.com/sp-cristiano)
 * @brief Header file containing function declarations for admin-related menus.
 * This file provides access to the admin menu interface and session management.
 * [Arquivo de cabeçalho com declarações de funções relacionadas ao menu do administrador.]
 * @param sysData Pointer to the system data structure containing user, role, currency, exchange rate, and transaction information.
 * [Apontador para a estrutura de dados do sistema contendo informações de usuário, papel, moeda, taxa de câmbio e transação.]
 * @version 1.0
 */

#ifndef ADMIN_MENU_H
#define ADMIN_MENU_H

/*
==================================================================================================================
																			File inclusion directives
																			[Diretivas de inclusão de arquivos]
==================================================================================================================
*/

#include "../include/structures.h"

/*
==================================================================================================================
																			Prototypes of functions
																			[Protótipos de funções]
==================================================================================================================
*/

// Function to start session [Função para iniciar a sessão]
void startSessionMenu(SystemData *sysData);

// Function to display the admin menu [Função para exibir o menu do administrador]
void adminMenu(SystemData *sysData);

#endif // ADMIN_MENU_H
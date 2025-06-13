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

#ifndef ROLE_FUNCTIONS_H
#define ROLE_FUNCTIONS_H

#include "../include/structures.h"
/*
******************************************************************************************
[Protótipos de funções.]
******************************************************************************************
*/

// *** PROTOTYPES FOR USER ROLES FUNCTIONS [PROTÓTIPOS PARA FUNÇÕES DE PAPÉIS DE USUÁRIO] ***
// Function to create a new role [Função para criar um novo papel]
void createRole(SystemData *sysData, const char *role_name, const char *description, const char *created_at, const char *updated_at, const char *deleted_at);
// Function to save role to file [Função para salvar papel no arquivo]
void saveRoleData(SystemData *sysData);
// Function to load role data from file [Função para carregar dados de papel do arquivo]
void loadRoleData(SystemData *sysData);
// Function to display all roles [Função para exibir todos os papéis]
void showRoles(SystemData *sysData);
// Function to update a role [Função para atualizar um papel]
void updateRole(SystemData *sysData, int role_id);
// Function to delete a role [Função para excluir um papel]
void deleteRole(SystemData *sysData, int role_id);
// Function to get user role. [Função para obter o papel do usuário]
const char *getUserRole(SystemData *sysData, int user_id);
#endif // ROLE_FUNCTIONS_H

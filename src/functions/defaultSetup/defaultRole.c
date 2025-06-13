/*
******************************************************************************
[Este arquivo contém todas as funções do sistema para o projeto unicambio.]
******************************************************************************
*/

/*
******************************************************************************
Including internal header files.
[Incluindo arquivos de cabeçalho internos.]
******************************************************************************
*/
#include "../include/config.h"
#include "../include/messages.h"
#include "../include/globals.h"
#include "../include/structures.h"
#include "../include/defaultRole.h"

/*
******************************************************************************
This function will create the default roles.
[Esta função criar padrões de papel.]
******************************************************************************
*/
void addRoleDefaultProfile(SystemData *sysData)
{
	FILE *checkRoleFile = fopen(ROLE_FILE, "r");
	if (checkRoleFile == NULL)
	{
		printf("\n%s\n", UI_ERROR_ROLE_FILE_NOT_FOUND); // If the file does not exist, create it [Se o arquivo não existir, crie-o]
		printf("%s\n", UI_CREATING_ROLE_FILE);

		FILE *roleFile = fopen(ROLE_FILE, "w");
		if (roleFile == NULL)
		{
			printf("%s\n", UI_ERROR_CREATING_ROLE_FILE);
			sleep(MID_SLEEP);
			return; // If the file cannot be created, exit the function [Se o arquivo não puder ser criado, saia da função]
		}
		fclose(roleFile);

		// Add default role to the role structure [Adicionar papel padrão à estrutura de papel]
		char *role_name = ADMIN_USER;								// Default role name for admin [Nome do papel padrão para administrador]
		char *description = ADMIN_USER_DESCRIPTION; // Default role description for admin [Descrição do papel padrão para administrador]
		char *created_at = getCurrentDateTime(2);		// Current date and time [Data e hora atual]
		char *updated_at = getCurrentDateTime(2);		// Current date and time [Data e hora atual]
		char *deleted_at = NULL;										// No deletion date for default role [Sem data de exclusão para o papel padrão]
		createRole(sysData, role_name, description, created_at, updated_at, deleted_at);
		sleep(MID_SLEEP);
		return;
	}
	else
	{
		fclose(checkRoleFile);
		return; // If the file exists, do not add the default role [Se o arquivo existir, não adicionar o papel padrão]
	}
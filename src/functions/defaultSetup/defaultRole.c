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
#include "../include/utilities.h"
#include "../include/roleFunctions.h"

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

		// Get current date and time for created_at and updated_at [Obter data e hora atual para created_at e updated_at]
		time_t timeStamp = getCurrentDateTime(1), dateStamp = getCurrentDateTime(0), created_at_time, created_at_date, updated_at_date, updated_at_time, deleted_at_date, deleted_at_time;

		created_at_time = timeStamp; // Current date and time [Data e hora atual]
		created_at_date = dateStamp;
		updated_at_time = timeStamp; // Current date and time [Data e hora atual]
		updated_at_date = dateStamp;
		deleted_at_time = NULL;			// No deletion date for default role [Sem data de exclusão para o papel padrão]
		deleted_at_date = NULL;
		createRole(sysData, role_name, description, created_at_date, created_at_time, updated_at_date, updated_at_time, deleted_at_date, deleted_at_time);
		sleep(MID_SLEEP);
		return;
	}
	else
	{
		fclose(checkRoleFile);
		return; // If the file exists, do not add the default role [Se o arquivo existir, não adicionar o papel padrão]
	}
}
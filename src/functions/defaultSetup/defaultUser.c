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
#include "../include/defaultUser.h"

/*
******************************************************************************
This function will create the default user.
[Esta função criar padrões de usuário.]
******************************************************************************
*/
void addUserDefaultProfile(SystemData *sysData)
{
	FILE *checkUserFile = fopen(USER_FILE, "r");
	if (checkUserFile == NULL)
	{
		printf("\n%s\n", UI_ERROR_USER_FILE_NOT_FOUND); // If the file does not exist, create it [Se o arquivo não existir, crie-o]
		printf("%s\n", UI_CREATING_USER_FILE);

		FILE *userFile = fopen(USER_FILE, "w");
		if (userFile == NULL)
		{
			printf("%s\n", UI_ERROR_CREATING_USER_FILE);
			sleep(MID_SLEEP);
			return; // If the file cannot be created, exit the function [Se o arquivo não puder ser criado, saia da função]
		}
		fclose(userFile);

		// Add default user to the user structure [Adicionar usuário padrão à estrutura de usuário]
		char *name = ADMIN_USER;									// Default user name for admin [Nome do usuário padrão para administrador]
		char *username = ADMIN_USER;							// Default username for admin [Nome de usuário padrão para administrador]
		char *email = ADMIN_USER_EMAIL;						// Default email for admin [Email padrão para administrador]
		char *password = ADMIN_USER_PASSWORD;			// Default password for admin [Senha padrão para administrador]
		char *phone = ADMIN_USER_PHONE;						// Default phone number for admin [Número de telefone padrão para administrador]
		int is_active = TRUE;											// Default active status for admin [Status ativo padrão para administrador]
		char *created_at = getCurrentDateTime(2); // Current date and time [Data e hora atual]
		char *last_seen = getCurrentDateTime(2);	// Current date and time [Data e hora atual]
		char *deleted_at = NULL;									// No deletion date for default user [Sem data de exclusão para o usuário padrão]

		createUser(sysData, name, username, email, password, phone, is_active, created_at, last_seen, deleted_at);

		sleep(MID_SLEEP);
		return;
	}
	else
	{
		fclose(checkUserFile);
		return; // If the file exists, do not add the default user [Se o arquivo existir, não adicionar o usuário padrão]
	}
}
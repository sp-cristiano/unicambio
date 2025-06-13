/*
******************************************************************************
This file contains all the admin functionss for the unicambio project.
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
#include "../include/structures.h"
#include "../include/globals.h"
#include "../include/userFunctions.h"

// /*
// ******************************************************************************
// This function will create roles.
// [Esta função cria papéis.]
// ******************************************************************************
// */
// void createRole(SystemData *sysData, const char *role_name, const char *description, const char *created_at, const char *updated_at, const char *deleted_at)
// {
// 	int roleAlreadyExisted = FALSE;			 // Flag to check if the role already exists [Flag para verificar se o papel já existe]
// 	int roleID = sysData->roleCount + 1; // Get the next available role ID [Obter o ID do papel disponível]

// 	// Check if the system data is initialized [Verifique se os dados do sistema estão inicializados]
// 	if (sysData == NULL)
// 	{
// 		printf("%s\n", UI_ERROR_DATA_NOT_FOUND);
// 		sleep(MIN_SLEEP);
// 		return;
// 	}

// 	// Check if the role capacity is zero or if the role count exceeds the capacity [Verifique se a capacidade do papel é zero ou se o número de papéis excede a capacidade]
// 	if (sysData->roleCapacity == 0)
// 	{
// 		sysData->roleCapacity = 2; // Initialize role capacity to 2 if it is zero [Inicializar a capacidade do papel para 2 se for zero]
// 	}
// 	else if (sysData->roleCount >= sysData->roleCapacity)
// 	{
// 		sysData->roleCapacity = (sysData->roleCapacity + 2) * 2; // Increase capacity by 2 and double it [Aumentar a capacidade em 2 e dobrá-la]
// 	}

// 	if (sysData->roleCapacity == 0)
// 	{
// 		sysData->roleCapacity = 2;
// 	}
// 	else if (sysData->roleCount >= sysData->roleCapacity)
// 	{
// 		sysData->roleCapacity = (sysData->roleCapacity + 2) * 2; // Increase capacity by 2 and double it [Aumentar a capacidade em 2 e dobrá-la]
// 	}

// 	sysData->roles = realloc(sysData->roles, (sysData->roleCapacity) * sizeof(RoleInfo)); // Increase capacity [Aumentar a capacidade]

// 	// Check if memory allocation was successful
// 	if (sysData->roles == NULL)
// 	{
// 		printf("%s\n", UI_ERROR_MEMORY_ALLOCATION);
// 		return;
// 	}

// 	if (role_name == NULL || description == NULL || created_at == NULL || updated_at == NULL)
// 	{
// 		printf("%s\n", UI_ERROR_INVALID_INPUT);
// 		return;
// 	}

// 	// Check if the role already exists [Verifique se o papel já existe]
// 	for (int i = 0; i < sysData->roleCount; i++)
// 	{
// 		if (sysData->roles[i].role_id == roleID || strcmp(sysData->roles[i].role_name, role_name) == 0)
// 		{
// 			printf("%s\n", UI_ERROR_ROLE_EXISTS);
// 			sleep(MIN_SLEEP);
// 			roleAlreadyExisted = TRUE; // Set the flag to true if role already exists [Definir a flag como verdadeira se o papel já existir]
// 			return;
// 		}
// 	}
// 	if (roleAlreadyExisted == FALSE)
// 	{
// 		sysData->roles[sysData->roleCount].role_id = roleID;									// Assign the role ID [Atribuir o ID do papel]
// 		sysData->roles[sysData->roleCount].role_name = strdup(role_name);			// Duplicate the role name string [Duplicar a string do nome do papel]
// 		sysData->roles[sysData->roleCount].description = strdup(description); // Duplicate the description string [Duplicar a string de descrição]
// 		sysData->roles[sysData->roleCount].created_at = strdup(created_at);		// Duplicate the created_at string [Duplicar a string created_at]
// 		sysData->roles[sysData->roleCount].updated_at = strdup(updated_at);		// Duplicate the updated_at string [Duplicar a string updated_at]
// 		if (deleted_at != NULL)
// 		{
// 			sysData->roles[sysData->roleCount].deleted_at = strdup(deleted_at); // Duplicate the deleted_at string if not NULL [Duplicar a string deleted_at se não for NULL]
// 		}
// 		else
// 		{
// 			sysData->roles[sysData->roleCount].deleted_at = strdup(""); // Set deleted_at to empty string if NULL [Definir deleted_at como string vazia se for NULL]
// 		}
// 		sysData->roleCount++; // Increment the role count [Incrementar o número de papéis]

// 		saveRole(sysData); // Save the role data to a file [Salvar os dados do papel em um arquivo]
// 	}
// 	return;
// }

/*
******************************************************************************
This function will create admin users.
[Esta função cria usuários administradores.]
******************************************************************************
*/
void createUsers(SystemData *sysData, RoleInfo *role, const char *name, const char *username, const char *email, const char *password, const char *phone, int is_active, const char *created_at, const char *last_seen, const char *deleted_at)
{
	int userAlreadyExisted = FALSE; // Flag to check if the user already exists [Flag para verificar se o usuário já existe]
	// Generate a random user ID [Gerar um ID de usuário aleatório]
	int userID = randomNumber(1000, 9000);

	// Check if the system data is initialized [Verifique se os dados do sistema estão inicializados]
	if (sysData == NULL)
	{
		printf("%s\n", UI_ERROR_DATA_NOT_FOUND);
		sleep(MIN_SLEEP);
		return;
	}
	if (sysData->userCapacity == 0)
	{
		sysData->userCapacity = 2;
	}
	else if (sysData->userCount >= sysData->userCapacity)
	{
		sysData->userCapacity = (sysData->userCapacity + 2) * 2; // Increase capacity by 2 and double it [Aumentar a capacidade em 2 e dobrá-la]
	}

	sysData->users = realoc(sysData->users, (sysData->userCapacity) * sizeof(UserInfo)); // Increase capacity [Aumentar a capacidade]

	// Check if memory allocation was successful
	if (sysData->users == NULL)
	{
		printf("%s\n", UI_ERROR_MEMORY_ALLOCATION);
		return;
	}

	// Check if the input is valid
	if (name == NULL || email == NULL || password == NULL || phone == NULL || created_at == NULL || last_seen == NULL)
	{
		printf("%s\n", UI_ERROR_INVALID_INPUT);
		return;
	}

	// Check if the user already exists [Verifique se o usuário já existe]
	for (int i = 0; i < sysData->userCount; i++)
	{
		if (sysData->users[i].user_id == userID || strcmp(sysData->users[i].email, email) == 0 || strcmp(sysData->users[i].phone, phone) == 0 || strcmp(sysData->users[i].username, username) == 0)
		{
			// User already exists
			printf("%s\n", UI_ERROR_USER_EXISTS);
			userAlreadyExisted = TRUE; // Set the flag to true if user already exists [Definir a flag como verdadeira se o usuário já existir]
			return;
		}
	}

	if (userAlreadyExisted == FALSE)
	{
		if (strcmp(role, "admin") == 0)
		{
			// TODO: Create admin user
			sysData->users[sysData->userCount].user_id = userID; // Assign the user ID [Atribuir o ID do usuário]
			strncpy(sysData->users[sysData->userCount].username, username, MAX_NAME_LENGTH - 1);
			sysData->users[sysData->userCount].user_role = NULL; // Set user role to NULL for now [Definir o papel do usuário como NULL por enquanto]
			sysData->users[sysData->userCount].is_active = is_active;
			// strncpy(sysData->users[sysData->userCount].created_at, created_at, MAX_DATE_TIME_LENGTH - 1);
			// strncpy(sysData->users[sysData->userCount].last_seen, last_seen, MAX_DATE_TIME_LENGTH - 1);
			if (deleted_at != NULL)
				// strncpy(sysData->users[sysData->userCount].deleted_at, deleted_at, MAX_DATE_TIME_LENGTH - 1);
				sysData->users[sysData->userCount].deleted_at[0] = '\0';			// Set deleted_at to empty string if NULL [Definir deleted_at como string vazia se for NULL]
			sysData->users[sysData->userCount].user_id = userID;						// Assign the user ID [Atribuir o ID do usuário]
			sysData->users[sysData->userCount].name = strdup(name);					// Duplicate the name string [Duplicar a string do nome]
			sysData->users[sysData->userCount].email = strdup(email);				// Duplicate the email string [Duplicar a string do email]
			sysData->users[sysData->userCount].password = strdup(password); // Duplicate the password string [Duplicar a string da senha]
			sysData->users[sysData->userCount].phone = strdup(phone);				// Duplicate the phone string [Duplicar a string do telefone]
			sysData->userCount++;																						// Increment the user count [Incrementar a contagem de usuários]
																																			// printf("%s\n", UI_SUCCESS_USER_CREATED);
		}
		else if (strcmp(role, "user") == 0)
		{
			// TODO: Create user
		}
		else
		{
			// printf("%s\n", UI_ERROR_INVALID_ROLE) return;
		}
	}

	// // Create a new user
	// UserInfo newUser;
	// strncpy(newUser.name, name, MAX_NAME_LENGTH - 1);
	// strncpy(newUser.email, email, MAX_EMAIL_LENGTH - 1);
	// strncpy(newUser.password, password, MAX_PASSWORD_LENGTH - 1);
	// strncpy(newUser.phone, phone, MAX_PHONE_LENGTH - 1);
	// newUser.is_active = is_active;
	// strncpy(newUser.created_at, created_at, MAX_DATE_TIME_LENGTH - 1);
	// strncpy(newUser.last_seen, last_seen, MAX_DATE_TIME_LENGTH - 1);
	// if (deleted_at != NULL)
	// 	strncpy(newUser.deleted_at, deleted_at, MAX_DATE_TIME_LENGTH - 1);
	// else
	// 	newUser.deleted_at[0] = '\0'; // Set deleted_at to empty string if NULL

	// // Add the new user to the system
	// if (sysData->userCount >= sysData->userCapacity)
	// {
	// 	sysData->userCapacity += USER_CAPACITY_INCREMENT;
	// 	sysData->users = realloc(sysData->users, sysData->userCapacity * sizeof(UserInfo));
	// 	if (sysData->users == NULL)
	// 	{
	// 		printf("%s\n", UI_ERROR_MEMORY_ALLOCATION);
	// 		return;
	// 	}
	// }

	// sysData->users[sysData->userCount++] = newUser;

	// printf("%s\n", UI_SUCCESS_USER_CREATED);
}
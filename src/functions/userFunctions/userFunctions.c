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
#include "../include/utilities.h"
#include "../include/userFunctions.h"

void createUser(SystemData *sysData, const char *name, const char *username, const char *email, const char *password, const char *phone, int is_active, const time_t created_at, const time_t last_seen, const time_t deleted_at)
{

	int userAlreadyExisted = FALSE;				 // Flag to check if the user already exists [Flag para verificar se o usuário já existe]
	int userID = randomNumber(1000, 9000); // Get a random user ID [Obter um ID de usuário aleatório]

	// Check if the system data is initialized [Verifique se os dados do sistema estão inicializados]
	if (sysData == NULL)
	{
		printf("%s\n", UI_ERROR_DATA_NOT_FOUND);
		sleep(MIN_SLEEP);
		return;
	}

	// Check if the user capacity is zero or if the user count exceeds the capacity [Verifique se a capacidade do usuário é zero ou se o número de usuários excede a capacidade]
	if (sysData->userCapacity == 0)
	{
		sysData->userCapacity = 2; // Initialize user capacity to 2 if it is zero [Inicializar a capacidade do usuário para 2 se for zero]
	}
	else if (sysData->userCount >= sysData->userCapacity)
	{
		sysData->userCapacity = (sysData->userCapacity + 2) * 2; // Increase capacity by 2 and double it [Aumentar a capacidade em 2 e dobrá-la]
	}
	sysData->users = realloc(sysData->users, (sysData->userCapacity) * sizeof(UserInfo)); // Increase capacity [Aumentar a capacidade]
	// Check if memory allocation was successful
	if (sysData->users == NULL)
	{
		printf("%s\n", UI_ERROR_MEMORY_ALLOCATION);
		return; // If memory allocation fails, exit the function [Se a alocação de memória falhar, saia da função]
	}
	if (name == NULL || username == NULL || email == NULL || password == NULL || phone == NULL || created_at == NULL || last_seen == NULL)
	{
		printf("%s\n", UI_ERROR_INVALID_INPUT);
		return; // If any of the input parameters are NULL, exit the function [Se algum dos parâmetros de entrada for NULL, saia da função]
	}

	// check if userID already existed
	for (int i = 0; i < sysData->userCount; i++)
	{
		if (sysData->users[i].user_id == userID || sysData->users[i].username == username || sysData->users[i].email == email || sysData->users[i].phone == phone)
		{
			userAlreadyExisted = TRUE; // Set the flag to true if the user ID already exists [Definir a flag como verdadeira se o ID do usuário já existir]

			if (userAlreadyExisted == TRUE && (strcmp(username, sysData->users[i].username) == 0 || strcmp(email, sysData->users[i].email) == 0 || strcmp(phone, sysData->users[i].phone) == 0))
			{
				printf("%s\n", UI_ERROR_USER_EXISTS);
				sleep(MIN_SLEEP);
				return; // If the user ID already exists, exit the function [Se o ID do usuário já existir, saia da função]
			}
			else if (userAlreadyExisted == TRUE && userID == sysData->users[i].user_id)
			{
				userID = randomNumber(1000, 9000); // Generate a new user ID if the current one already exists [Gerar um novo ID de usuário se o atual já existir]
				i = -1;														 // Reset the loop to check again from the beginning [Redefinir o loop para verificar novamente do início]
			}
			else if (userAlreadyExisted == TRUE && ((strcmp(username, sysData->users[i].username) == 0 || strcmp(email, sysData->users[i].email) == 0 || strcmp(phone, sysData->users[i].phone) == 0) && (userID == sysData->users[i].user_id)))
			{
				printf("%s\n", UI_ERROR_USER_EXISTS);
				sleep(MIN_SLEEP);
				return; // If the user ID already exists, exit the function [Se o ID do usuário já existir, saia da função]
			}
		}
		else
		{
			userID = userID;
		}
	}
	// If the user does not already exist, create a new user [Se o usuário não existir, crie um novo usuário]
	if (userAlreadyExisted == FALSE)
	{
		sysData->users[sysData->userCount].user_id = userID;								// Set the user ID [Definir o ID do usuário]
		sysData->users[sysData->userCount].name = strdup(name);							// Set the user name [Definir o nome do usuário]
		sysData->users[sysData->userCount].username = strdup(username);			// Set the username [Definir o nome de usuário]
		sysData->users[sysData->userCount].email = strdup(email);						// Set the user email [Definir o email do usuário]
		sysData->users[sysData->userCount].password = strdup(password);			// Set the user password [Definir a senha do usuário]
		sysData->users[sysData->userCount].phone = strdup(phone);						// Set the user phone number [Definir o número de telefone do usuário]
		sysData->users[sysData->userCount].is_active = is_active;						// Set the user active status [Definir o status ativo do usuário]
		sysData->users[sysData->userCount].created_at = created_at;					// Set the user creation date [Definir a data de criação do usuário]
		sysData->users[sysData->userCount].last_seen = strdup(last_seen);		// Set the user last seen date [Definir a data de visita do usuário]
		sysData->users[sysData->userCount].deleted_at = strdup(deleted_at); // Set the user deletion date [Definir a data de exclusão do usuário]
		sysData->userCount++;																								// Increase the user count [Aumentar o número de usuários]
	}
}
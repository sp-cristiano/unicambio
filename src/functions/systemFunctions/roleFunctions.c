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
#include "../include/roleFunctions.h"

/*
******************************************************************************
******************************************************************************
*/
/*
******************************************************************************
This function will create roles.
[Esta função cria papéis.]
******************************************************************************
*/
void createRole(SystemData *sysData, const char *role_name, const char *description, time_t created_at_date, time_t created_at_time, time_t updated_at_date, time_t updated_at_time, time_t deleted_at_date, time_t deleted_at_time)
{
	int roleAlreadyExisted = FALSE;			 // Flag to check if the role already exists [Flag para verificar se o papel já existe]
	int roleID = sysData->roleCount + 1; // Get the next available role ID [Obter o ID do papel disponível]

	// Check if the system data is initialized [Verifique se os dados do sistema estão inicializados]
	if (sysData == NULL)
	{
		printf("%s\n", UI_ERROR_DATA_NOT_FOUND);
		sleep(MIN_SLEEP);
		return;
	}
	// Check if the role capacity is zero or if the role count exceeds the capacity [Verifique se a capacidade do papel é zero ou se o número de papéis excede a capacidade]
	if (sysData->roleCapacity == 0)
	{
		sysData->roleCapacity = 2; // Initialize role capacity to 2 if it is zero [Inicializar a capacidade do papel para 2 se for zero]
	}
	else if (sysData->roleCount >= sysData->roleCapacity)
	{
		sysData->roleCapacity = (sysData->roleCapacity + 2) * 2; // Increase capacity by 2 and double it [Aumentar a capacidade em 2 e dobrá-la]
	}

	sysData->roles = realloc(sysData->roles, (sysData->roleCapacity) * sizeof(RoleInfo)); // Increase capacity [Aumentar a capacidade]

	// Check if memory allocation was successful
	if (sysData->roles == NULL)
	{
		printf("%s\n", UI_ERROR_MEMORY_ALLOCATION);
		return;
	}

	if (role_name == NULL || description == NULL || created_at_date == NULL || created_at_time == NULL || updated_at_date == NULL || updated_at_time == NULL)
	{
		printf("%s\n", UI_ERROR_INVALID_INPUT);
		return;
	}

	// Check if the role already exists [Verifique se o papel já existe]
	for (int i = 0; i < sysData->roleCount; i++)
	{
		if (sysData->roles[i].role_id == roleID || strcmp(sysData->roles[i].role_name, role_name) == 0)
		{
			printf("%s\n", UI_ERROR_ROLE_EXISTS);
			sleep(MIN_SLEEP);
			roleAlreadyExisted = TRUE; // Set the flag to true if role already exists [Definir a flag como verdadeira se o papel já existir]
			return;
		}
	}
	if (roleAlreadyExisted == FALSE)
	{
		sysData->roles[sysData->roleCount].role_id = roleID;									// Assign the role ID [Atribuir o ID do papel]
		sysData->roles[sysData->roleCount].role_name = strdup(role_name);			// Duplicate the role name string [Duplicar a string do nome do papel]
		sysData->roles[sysData->roleCount].description = strdup(description); // Duplicate the description string [Duplicar a string de descrição]
		sysData->roles[sysData->roleCount].created_at_date = created_at_date; // Duplicate the created_at string [Duplicar a string created_at]
		sysData->roles[sysData->roleCount].created_at_time = created_at_time;
		sysData->roles[sysData->roleCount].updated_at_date = updated_at_date; // Duplicate the updated_at string [Duplicar a string updated_at]
		sysData->roles[sysData->roleCount].updated_at_time = updated_at_time; // Duplicate the updated_at string [Duplicar a string updated_at]

		if (deleted_at_date != NULL || deleted_at_time != NULL)
		{
			sysData->roles[sysData->roleCount].deleted_at_date = deleted_at_date; // Duplicate the deleted_at string if not NULL [Duplicar a string deleted_at se não for NULL]
			sysData->roles[sysData->roleCount].deleted_at_time = deleted_at_time; // Duplicate the deleted_at string if not NULL [Duplicar a string deleted_at se não for NULL]
		}
		else
		{
			sysData->roles[sysData->roleCount].deleted_at_date = ""; // Set deleted_at to empty string if NULL [Definir deleted_at como string vazia se for NULL]
			sysData->roles[sysData->roleCount].deleted_at_time = "";
		}
		sysData->roleCount++; // Increment the role count [Incrementar o número de papéis]

		saveRoleData(sysData); // Save the role data to a file [Salvar os dados do papel em um arquivo]
	}
	return;
}

/*
******************************************************************************
This function will save the role data to a file.
[Esta função salvará os dados do papel em um arquivo.]
******************************************************************************
*/
void saveRoleData(SystemData *sysData)
{
	if (sysData == NULL)
	{
		printf("%s\n", UI_ERROR_DATA_NOT_FOUND);
		sleep(MIN_SLEEP);
		return;
	}

	FILE *roleFile = fopen(ROLE_FILE, "w");
	if (roleFile == NULL)
	{
		printf("%s\n", UI_ERROR_FILE_WRITE);
		sleep(MID_SLEEP);
		return;
	}
	if (sysData->roleCount == 0)
	{
		printf("%s\n", UI_ERROR_ROLE_NOT_FOUND);
		sleep(MID_SLEEP);
		fclose(roleFile);
		return; // If there are no roles, exit the function [Se não houver papéis, saia da função]
	}
	else
	{
		for (int i = 0; i < sysData->roleCount; i++)
		{
			fprintf(roleFile, "%d|%s|%s|%s|%s|%s|%s|%s|%s\n",
							sysData->roles[i].role_id,
							sysData->roles[i].role_name,
							sysData->roles[i].description,
							sysData->roles[i].created_at_date,
							sysData->roles[i].created_at_time,
							sysData->roles[i].updated_at_date,
							sysData->roles[i].updated_at_time,
							sysData->roles[i].deleted_at_date,
							sysData->roles[i].deleted_at_time);
		}
	}
	if (fclose(roleFile) != 0)
	{
		printf("%s\n", UI_ERROR_CLOSING_ROLE_FILE);
		sleep(MID_SLEEP);
		return; // If the file cannot be closed, exit the function [Se o arquivo não puder ser fechado, saia da função]
	}
	else
	{
		printf("%s\n", UI_SUCCESSFUL_ROLE_DATA_SAVED);
		sleep(MID_SLEEP);
		return; // If the file is saved successfully, exit the function [Se o arquivo for salvo com sucesso, saia da função]
	}
}

/*
******************************************************************************
This function will load the role data from a file.
[Esta função carregará os dados do papel de um arquivo.]
******************************************************************************
*/
void loadRoleData(SystemData *sysData)
{
	if (sysData == NULL)
	{
		printf("%s\n", UI_ERROR_DATA_NOT_FOUND);
		sleep(MIN_SLEEP);
		return;
	}

	FILE *roleFile = fopen(ROLE_FILE, "r");
	if (roleFile == NULL)
	{
		printf("%s\n", UI_ERROR_FILE_READ);
		sleep(MID_SLEEP);
		return; // If the file cannot be opened, exit the function [Se o arquivo não puder ser aberto, saia da função]
	}
	int _roleID;
	time_t _created_at_date, _created_at_time, _updated_at_date, _updated_at_time, _deleted_at_date, _deleted_at_time;
	size_t _roleCount, _roleCapacity;

	char *_role_name = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
	char *_description = (char *)malloc(MAX_DESCRIPTION_LENGTH * sizeof(char));

	// char role_name[MAX_NAME_LENGTH], description[MAX_DESCRIPTION_LENGTH];
	// time_t created_at_date, created_at_time, updated_at_date, updated_at_time, deleted_at_date, deleted_at_time;

	if (sysData->roleCapacity == 0)
	{
		sysData->roleCapacity = 2; // Initialize role capacity to 2 if it is zero [Inicializar a capacidade do papel para 2 se for zero]
	}
	else
	{
		sysData->roleCapacity = (sysData->roleCapacity + 2) * 2; // Increase capacity by 2 and double it [Aumentar a capacidade em 2 e dobrá-la]
	}

	sysData->roles = realloc(sysData->roles, (sysData->roleCapacity) * sizeof(RoleInfo)); // Increase capacity [Aumentar a capacidade]
	// Check if memory allocation was successful
	if (sysData->roles == NULL)
	{
		printf("%s\n", UI_ERROR_MEMORY_ALLOCATION);
		fclose(roleFile);
		return; // If memory allocation fails, exit the function [Se a alocação de memória falhar, saia da função]
	}

	sysData->roleCount = 0; // Reset role count before loading [Redefinir o número de papéis antes de carregar]

	// Read the file line by line
	while (fscanf(roleFile, "%d|%149[^|]|%499[^|]|%99[^|]|%99[^|]|%99[^\n]|%99[^|]|%99[^|]|%99[^\n]", &_roleID, _role_name, _description, _created_at_date, _created_at_time, _updated_at_date, _updated_at_time, _deleted_at_date, _deleted_at_time) != EOF && sysData->roleCount < sysData->roleCapacity)
	{
		sysData->roles[sysData->roleCount].role_id = _roleID;
		sysData->roles[sysData->roleCount].role_name = strdup(_role_name);
		sysData->roles[sysData->roleCount].description = strdup(_description);
		sysData->roles[sysData->roleCount].created_at_date = _created_at_date;
		sysData->roles[sysData->roleCount].created_at_time = _created_at_time;
		sysData->roles[sysData->roleCount].updated_at_date = _updated_at_date;
		sysData->roles[sysData->roleCount].updated_at_time = _updated_at_time;
		sysData->roles[sysData->roleCount].deleted_at_date = _deleted_at_date;
		sysData->roles[sysData->roleCount].deleted_at_time = _deleted_at_time;
		sysData->roleCount++;

		if (sysData->roleCount >= sysData->roleCapacity)
		{
			sysData->roleCapacity = (sysData->roleCapacity + 2) * 2;
			sysData->roles = realloc(sysData->roles, sysData->roleCapacity * sizeof(RoleInfo));

			if (sysData->roles == NULL)
			{
				printf("%s\n", UI_ERROR_MEMORY_ALLOCATION);
				free(sysData->roles);
				fclose(roleFile);
				return;
			}
		}
	}
	fclose(roleFile);
	return;
}

/*
******************************************************************************
This function will show available roles.
[Esta função mostra os papéis disponíveis.]
******************************************************************************
*/
void showRoles(SystemData *sysData)
{

	if (sysData == NULL)
	{
		printf("%s\n", UI_ERROR_DATA_NOT_FOUND);
		sleep(MIN_SLEEP);
		return;
	}
	if (sysData->roleCount == 0)
	{
		printf("%sn", UI_ERROR_NO_ROLES_FOUND);
		sleep(MID_SLEEP);
		return; // If there are no roles, exit the function [Se não houver papéis, saia da função]
	}
	else
	{
		printf("\tID   | ROLE [PAPEL]\n");
		printf("\t********************\n");
		for (int i = 0; i < sysData->roleCount; i++)
		{
			printf("\t%d        %s\n", sysData->roles[i].role_id, sysData->roles[i].role_name);
		}
	}
}

/*
******************************************************************************
This function will update roles
[Esta função atualizará os papéis]
******************************************************************************
*/
void updateRole(SystemData *sysData, int role_id)
{
	int rolePosition, roleFound = FALSE;
	if (sysData->roleCount == 0)
	{
		printf("%s\n", UI_ERROR_NO_ROLES_FOUND);
		sleep(MID_SLEEP);
		return; // If there are no roles, exit the function [Se não houver papéis, saia da função]
	}

	for (rolePosition = 0; rolePosition < sysData->roleCount; rolePosition++)
	{
		if (sysData->roles[rolePosition].role_id == role_id)
		{
			roleFound = TRUE;
			break;
		}
	}

	if (roleFound == TRUE)
	{
		int choice;
		do
		{
			displayBanner();
			printf("UPDATE ROLE DATA WITH ROLE ID: %d[ATUALIZE OS DADOS DO PAPEL COM O ID: %d] \n", role_id, role_id);
			printf("ROLE NAME [ NOME DO PAPEL]: %s\n", sysData->roles[rolePosition].role_name);
			printf("ROLE DESCRIPTION [DESCRIÇÃO DO PAPEL]: %s\n", sysData->roles[rolePosition].description);
			printf("Input 1 or 2 to update the role data. Input 0 to go back. [Digite 1 ou 2 para atualizar os dados do papel. Digite 0 para voltar.]\n");
			printf("\t1. Update Role Name [Atualizar o nome do papel]\n");
			printf("\t2. Update Role Description [Atualizar a descrição do papel]\n");
			printf("\t0. Go Back [Voltar]\n");
			printf("Enter your choice [Digite sua escolha]: ");
			scanf("%d", &choice);
			switch (choice)
			{
			case 0:
				goBack = TRUE;			 // Set the flag to true to go back [Definir a flag como verdadeira para voltar]
				showRoles(&sysData); // Show available roles [Mostrar papéis disponíveis]
				break;
			case 1:
				printf("Enter new role name[Digite o novo nome do papel]: ");
				scanf("%s", sysData->roles[rolePosition].role_name);
				time_t timeStamp = getCurrentDateTime(1), dateStamp  = getCurrentDateTime(0);
				sysData->roles[rolePosition].updated_at_time = timeStamp; // Update the updated_at field
				sysData->roles[rolePosition].updated_at_date = dateStamp;

				saveRoleData(&sysData); // Save the updated role data [Salvar os dados do papel atualizado]
				showRoles(&sysData);		// Show available roles [Mostrar papéis disponíveis]
				break;
			case 2:
				printf("Enter new role description[Digite a nova descrição do papel]: ");
				scanf("%[^\n]%*c", sysData->roles[rolePosition].description);
				time_t timeStamp = getCurrentDateTime(1), dateStamp = getCurrentDateTime(0);
				sysData->roles[rolePosition].updated_at_time = timeStamp; // Update the updated_at field
				sysData->roles[rolePosition].updated_at_date = dateStamp;

				saveRoleData(&sysData); // Save the updated role data [Salvar os dados do papel atualizado]
				showRoles(&sysData);		// Show available roles [Mostrar papéis disponíveis]
				break;
			default:
				printf("%s\n", UI_ERROR_INVALID_INPUT);
				sleep(MID_SLEEP);
				break;
			}
		} while (choice < 0 || choice > 2);
	}
	else
	{
		printf("Role with ID %d not found. [Papel com ID %d não encontrado.]\n", role_id, role_id);
		sleep(MID_SLEEP);
		return; // If the role is not found, exit the function [Se o papel não for encontrado, saia da função]
	}
}

/*
******************************************************************************
This function will delete roles.
[Esta função excluirá papéis.]
******************************************************************************
*/
void deleteRole(SystemData *sysData, int role_id)
{
	int rolePosition, roleFound = FALSE, reOrderRolePosition;
	if (sysData->roleCount == 0)
	{
		printf("%s\n", UI_ERROR_NO_ROLES_FOUND);
		sleep(MID_SLEEP);
		return; // If there are no roles, exit the function [Se não houver papéis, saia da função]
	}

	for (rolePosition = 0; rolePosition < sysData->roleCount; rolePosition++)
	{
		if (sysData->roles[rolePosition].role_id == role_id)
		{
			roleFound = TRUE;
			break;
		}
	}

	if (roleFound == TRUE)
	{
		time_t timeStamp = getCurrentDateTime(1), dateStamp = getCurrentDateTime(0);
		sysData->roles[rolePosition].deleted_at_date = dateStamp; // Set the deleted_at field to current date and time
		sysData->roles[rolePosition].deleted_at_time = timeStamp;

		for (reOrderRolePosition = rolePosition; reOrderRolePosition < sysData->roleCount - 1; reOrderRolePosition++)
		{
			sysData->roles[reOrderRolePosition] = sysData->roles[reOrderRolePosition + 1]; // Shift roles to the left [Deslocar papéis para a esquerda]
		}
		sysData->roleCount--; // Decrease the role count [Diminuir o número de papéis]
		printf("Role with ID %d has been deleted successfully. [Papel com ID %d foi excluído com sucesso.]\n", role_id, role_id);
		saveRoleData(&sysData); // Save the updated role data [Salvar os dados do papel atualizado]
		sleep(MID_SLEEP);
		return;
	}
	else
	{
		printf("Role with ID %d not found. [Papel com ID %d não encontrado.]\n", role_id, role_id);
		sleep(MID_SLEEP);
		return; // If the role is not found, exit the function [Se o papel não for encontrado, saia da função]
	}
}

/*
******************************************************************************
This function will get the current user role.
[Esta função obterá o papel do usuário atual.]
******************************************************************************
*/
const char *getUserRole(SystemData *sysData, int currentUserID)
{
	if (sysData == NULL)
	{
		printf("%s\n", UI_ERROR_DATA_NOT_FOUND);
		sleep(MIN_SLEEP);
		return NULL; // If the system data is not initialized, exit the function [Se os dados do sistema não estiverem inicializados, saia da função]
	}

	for (int i = 0; i < sysData->userCount; i++)
	{
		if (sysData->users[i].user_id == currentUserID)
		{
			if (sysData->users[i].user_role == NULL || sysData->users[i].user_role->role_name == NULL)
			{
				printf("User with ID %d has no role assigned. [Usuário com ID %d não tem papel atribuído.]\n", currentUserID, currentUserID);
				sleep(MID_SLEEP);
				return NULL; // Set currentUserRole to NULL if no role is assigned [Definir currentUserRole como NULL se nenhum papel for atribuído]
			}
			else
			{
				currentUserRole = sysData->users[i].user_role->role_name; // Get the role name of the user [Obter o nome do papel do usuário]
				return currentUserRole;																		// Return the role name of the user [Retornar o nome do papel do usuário]
			}
		}
	}
	printf("User with ID %d not found. [Usuário com ID %d não encontrado.]\n", currentUserID, currentUserID);
	sleep(MID_SLEEP);
	return NULL; // If the user is not found, return NULL [Se o usuário não for encontrado, retornar NULL]
}
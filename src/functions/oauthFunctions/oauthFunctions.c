/*
******************************************************************************
This file contains all the oauth functionss for the unicambio project.
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
#include "../include/oauthFunctions.h"

/*
******************************************************************************
This function will display the login page.
[Esta função exibirá a página de login.]
******************************************************************************
*/
void loginPage(SystemData *sysData)
{
	exitFlag = FALSE;
	is_authenticated = FALSE;
	session = FALSE;
	char username[MAX_NAME_LENGTH], password[MAX_NAME_LENGTH];
	if (sysData == NULL)
	{
		printf("%s\n", UI_ERROR_DATA_NOT_FOUND);
		sleep(MIN_SLEEP);
		return; // If the system data is not initialized, exit the function [Se os dados do sistema não estiverem inicializados, saia da função]
	}
	if (sysData->userCount == 0)
	{
		printf("%s\n", UI_ERROR_NO_USERS);
		sleep(MIN_SLEEP);
		return; // If there are no users in the system, exit the function [Se não houver usuários no sistema, saia da função]
	}
	else
	{
		do
		{
			while (loginAttempts < MAX_LOGIN_ATTEMPTS && is_authenticated == FALSE)
			{
				displayBanner();
				if (is_authenticated == FALSE)
				{
					printf("\n\n            Maximum Trials [Tentativas Máximas]: %d \n", MAX_LOGIN_ATTEMPTS);
					printf("                Remaining Attempts [Tentativas Restantes]: %d \n\n", MAX_LOGIN_ATTEMPTS - loginAttempts);
					printf("                              %s\\n\n", UI_LOGIN);

					printf("Inpute 0 to go back to the previous page [Digite 0 para voltar à página anterior]\n");

					printf("\t%s\n", UI_USERNAME);
					scanf("%149s", username);
					if (username[0] == '0' && strlen(username) == 1)
					{
						goBack = TRUE; // Set goBack flag to TRUE to return to the previous page [Definir a flag goBack como TRUE para retornar à página anterior]
						return;				 // Exit the login page if goBack is TRUE [Sair da página de login se goBack for TRUE]
					}
					printf("\t%s\n", UI_PASSWORD);
					scanf("%149s", password);
					if (password[0] == '0' && strlen(password) == 1)
					{
						goBack = TRUE; // Set goBack flag to TRUE to return to the previous page [Definir a flag goBack como TRUE para retornar à página anterior]
						return;				 // Exit the login page if goBack is TRUE [Sair da página de login se goBack for TRUE]
					}
					if (strlen(username) == 0 || strlen(password) == 0)
					{
						printf("\n   %s\n", UI_ERROR_INVALID_INPUT);
						sleep(MID_SLEEP);
						continue; // Continue to the next iteration if input is invalid [Continuar para a próxima iteração se a entrada for inválida]
					}

					is_authenticated = authenticateUser(sysData, username, password); // Authenticate the user [Autenticar o usuário]
					if (is_authenticated == FALSE)
					{
						if (loginAttempts == MAX_LOGIN_ATTEMPTS)
						{
							printf("\n   %s\n", MAX_LOGIN_ATTEMPTS);
							exitFlag = TRUE;	 // Exit the login page if maximum attempts reached [Sair da página de login se o número máximo de tentativas for atingido]
							loginAttempts = 0; // Reset login attempts [Redefinir tentativas de login]
							sleep(MID_SLEEP);
							startSession(sysData); // Restart the session [Reiniciar a sessão]
							return;
						}
					}
					loginAttempts++;
				}
			}

		} while (exitFlag == FALSE && is_authenticated == FALSE && loginAttempts < MAX_LOGIN_ATTEMPTS);
	}
	if (is_authenticated == TRUE)
	{
		grantLoginAccess(sysData, currentUserID); // Login function [Função de login]
	}
}

int authenticateUser(SystemData *sysData, const char *username, const char *password)
{
	char temp_username[MAX_NAME_LENGTH], temp_password[MAX_NAME_LENGTH];

	// Check if the system data is initialized [Verifique se os dados do sistema estão inicializados]
	if (sysData == NULL || sysData->users == NULL)
	{
		printf("%s\n", UI_ERROR_DATA_NOT_FOUND);
		sleep(MIN_SLEEP);
		return FALSE; // If the system data or users are not initialized, return FALSE [Se os dados do sistema ou usuários não estiverem inicializados, retornar FALSE]
	}

	for (int i = 0; i < sysData->userCount; i++)
	{
		strcpy(temp_username, sysData->users[i].username);
		strcpy(temp_password, sysData->users[i].password);

		// Compare the input username and password with the stored username and password [Comparar o nome de usuário e a senha inseridos com o nome de usuário e a senha armazenados]
		if (strcmp(temp_username, username) == 0)
		{
			if (strcmp(temp_password, password) == 0)
			{
				is_authenticated = TRUE;
				session = TRUE;																						// Set the session flag to TRUE [Definir a flag de sessão como TRUE]
				currentUserID = sysData->users[i].user_id;								// Set the current user ID [Definir o ID do usuário atual]
				currentUserName = sysData->users[i].username;							// Set the current user name [Definir o nome do usuário atual]
				currentUserRole = sysData->users[i].user_role->role_name; // Set the current user role [Definir o papel do usuário atual]
				sysData->users[i].last_seen = getCurrentDateTime(2);			// Update the last seen time [Atualizar o horário da última visualização]
				is_authenticated = TRUE;																	// Set the authentication flag to TRUE [Definir a flag de autenticação como TRUE]
				printf("\n   %s\n", UI_SUCCESSFUL_LOGIN);
				sleep(MID_SLEEP);
				return is_authenticated; // Return TRUE if authentication is successful [Retornar TRUE se a autenticação for bem-sucedida]
			}
			else
			{
				printf("\n   %s\n", UI_ERROR_INVALID_PASSWORD);
				sleep(MID_SLEEP);
				is_authenticated = FALSE; // Set the authentication flag to FALSE if the password is incorrect [Definir a flag de autenticação como FALSE se a senha estiver incorreta]
				return is_authenticated;	// Return FALSE if the password is incorrect [Retornar FALSE se a senha estiver incorreta]
			}
		}
		else if (strcmp(temp_password, password) == 0)
		{
			printf("\n   %s\n", UI_ERROR_INVALID_USERNAME);
			sleep(MID_SLEEP);
			is_authenticated = FALSE; // Set the authentication flag to FALSE if the username is incorrect [Definir a flag de autenticação como FALSE se o nome de usuário estiver incorreto]
			return is_authenticated;	// Return FALSE if the username is incorrect [Retornar FALSE se o nome de usuário estiver incorreto]
		}
		else
		{
			printf("\n   %s\n", UI_ERROR_INVALID_CREDENTIALS); // Invalid username or password [Nome de usuário ou senha inválidos]
			sleep(MID_SLEEP);
			is_authenticated = FALSE; // Set the authentication flag to FALSE if the credentials are invalid [Definir a flag de autenticação como FALSE se as credenciais forem inválidas]
			return is_authenticated;	// Return FALSE if the credentials are invalid [Retornar FALSE se as credenciais forem inválidas]
		}
	}
	return is_authenticated; // User authentication failed [Falha na autenticação do usuário]
}

void grantLoginAccess(SystemData *sysData, int currentUserID)
{
	if (sysData == NULL || currentUserID < 0)
	{
		printf("%s\n", UI_ERROR_DATA_NOT_FOUND);
		sleep(MIN_SLEEP);
		return; // If the system data or input is invalid, exit the function [Se os dados do sistema ou a entrada forem inválidos, saia da função]
	}
	currentUserRole = getUserRole(sysData, currentUserID); // Get the user role based on username and password [Obter o papel do usuário com base no nome de usuário e na senha]

	if (currentUserRole != NULL)
	{
		if (strcmp(currentUserRole, "admin") == 0 || strcmp(currentUserRole, "Admin") == 0)
		{
			adminMenu(sysData); // If the user is an admin, grant access to the admin menu [Se o usuário for um administrador, conceder acesso ao menu de administração]
		}
		else
		{
			userMenu(sysData); // If the user is not an admin, grant access to the user menu [Se o usuário não for um administrador, conceder acesso ao menu de usuário]
		}
	}
	else
	{
		printf("%s\n", UI_ERROR_ROLE_NOT_FOUND);
		sleep(MIN_SLEEP);
		return;
	}

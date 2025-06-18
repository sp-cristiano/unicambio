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
#include "unicambio.h"
#include "structures.h"
#include "messages.h"
#include "oauth.h"
#include "utilities.h"
#include "logger.h"
#include "homePageMenu.h"

char *hashPassword(const char *password)
{
	// Hash the password using a secure hashing algorithm [Hashear a senha usando um algoritmo de hash seguro]

	char *hashStr = malloc(crypto_pwhash_STRBYTES);

	if (hashStr == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
		return NULL;
	}

	if (crypto_pwhash_str(hashStr, password, strlen(password), crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0)
	{

		logMessages(LOG_ERROR, UI_ERROR_HASHING_PASSWORD);
		free(hashStr);
		return NULL;
	}
	return hashStr;
}

// Verify the password against the hashed password
int verifyPassword(const char *password, const char *hashedPassword)
{

	if (crypto_pwhash_str_verify(hashedPassword, password, strlen(password)) == 0)
	{
		return true; // If verification succeeds, return TRUE [Se a verificação for bem-sucedida, retornar TRUE]
	}
	// printf("%s\n", UI_ERROR_INVALID_PASSWORD);
	return false; // If verification fails, return FALSE [Se a verificação falhar, retornar FALSE]
}

/*
******************************************************************************
This function will display the login page.
[Esta função exibirá a página de login.]
******************************************************************************
*/
void loginPageMenu(SystemData *sysData)
{
	int exitFlag = sysData->appContext->exitFlag, loginAttempts = sysData->appContext->loginAttempts, goBack = sysData->appContext->goBack, is_authenticated = sysData->appContext->isAuthenticated;
	char username[MAX_NAME_LENGTH], password[MAX_PASSWORD_LENGTH];

	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		centerStringOnly(UI_ERROR_SYSTEM_DATA_IS_NULL);
		// printf("%s\n", UI_ERROR_SYSTEM_DATA_IS_NULL);
		sleep(MIN_SLEEP);
		return; // If the system data is not initialized, exit the function [Se os dados do sistema não estiverem inicializados, saia da função]
	}
	if (sysData->userCount == 0)
	{
		logMessages(LOG_ERROR, UI_ERROR_USER_NOT_FOUND);
		centerStringOnly(UI_ERROR_USER_NOT_FOUND);
		// printf("%s\n", UI_ERROR_NO_USERS);
		sleep(MIN_SLEEP);
		return; // If there are no users in the system, exit the function [Se não houver usuários no sistema, saia da função]
	}
	else
	{
		do
		{
			while (loginAttempts < MAX_LOGIN_ATTEMPTS && is_authenticated == false)
			{
				displayBanner();
				if (is_authenticated == false)
				{
					printf("\n\n            Maximum Trials [Tentativas Máximas]: %d \n", MAX_LOGIN_ATTEMPTS);
					printf("                Remaining Attempts [Tentativas Restantes]: %d \n\n", MAX_LOGIN_ATTEMPTS - loginAttempts);
					printf("                              %s\\n\n", UI_LABEL_LOGIN_PAGE);

					printf("Inpute 0 to go back to the previous page [Digite 0 para voltar à página anterior]\n");

					printf("\t%s\n", UI_USERNAME);
					scanf("%149s", username);
					if (username[0] == '0' && strlen(username) == 1)
					{
						goBack = true; // Set goBack flag to TRUE to return to the previous page [Definir a flag goBack como TRUE para retornar à página anterior]
						sysData->appContext->goBack = goBack;
						return; // Exit the login page if goBack is TRUE [Sair da página de login se goBack for TRUE]
					}
					printf("\t%s\n", UI_PASSWORD);
					scanf("%149s", password);
					if (password[0] == '0' && strlen(password) == 1)
					{
						goBack = true; // Set goBack flag to TRUE to return to the previous page [Definir a flag goBack como TRUE para retornar à página anterior]
						return;				 // Exit the login page if goBack is TRUE [Sair da página de login se goBack for TRUE]
					}
					if (strlen(username) == 0 || strlen(password) == 0)
					{
						printf("\n   %s\n", UI_ERROR_INVALID_INPUT);
						sleep(MID_SLEEP);
						continue; // Continue to the next iteration if input is invalid [Continuar para a próxima iteração se a entrada for inválida]
					}

					is_authenticated = authenticateUser(sysData, username, password); // Authenticate the user [Autenticar o usuário]
					if (is_authenticated == false)
					{
						if (loginAttempts == MAX_LOGIN_ATTEMPTS)
						{
							logMessages(LOG_ERROR, UI_ERROR_MAX_LOGIN_ATTEMPTS_REACHED);
							// printf("\n   %s\n", MAX_LOGIN_ATTEMPTS);
							exitFlag = true;											// Exit the login page if maximum attempts reached [Sair da página de login se o número máximo de tentativas for atingido]
							loginAttempts = 0;										// Reset login attempts [Redefinir tentativas de login]
							sysData->appContext->session = false; // Set the session flag to FALSE [Definir a flag de sessão como FALSE]
							sleep(MID_SLEEP);
							goBack = true;				 // Set goBack flag to TRUE to return to the previous page [Definir a flag goBack como TRUE para retornar à página anterior]
							homePageMenu(sysData); // Restart the session [Reiniciar a sessão]
							return;
						}
					}
					loginAttempts++;
				}
			}

		} while (exitFlag == false && is_authenticated == false && loginAttempts < MAX_LOGIN_ATTEMPTS);
	}
	if (is_authenticated == true)
	{
		grantLoginAccess(sysData, sysData->appContext->currentUserID); // Login function [Função de login]
	}
}

int authenticateUser(SystemData *sysData, const char *username, const char *password)
{
	char temp_username[MAX_NAME_LENGTH], temp_password[MAX_PASSWORD_LENGTH];
	int passwordIsVerified = false;

	// Check if the system data is initialized [Verifique se os dados do sistema estão inicializados]
	if (sysData == NULL || sysData->users == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		// printf("%s\n", UI_ERROR_DATA_NOT_FOUND);
		sleep(MIN_SLEEP);
		return false; // If the system data or users are not initialized, return FALSE [Se os dados do sistema ou usuários não estiverem inicializados, retornar FALSE]
	}

	for (size_t i = 0; i < sysData->userCount; i++)
	{
		strcpy(temp_username, sysData->users[i].userName);
		strcpy(temp_password, sysData->users[i].password);
		passwordIsVerified = verifyPassword(password, temp_password);

		// Compare the input username and password with the stored username and password [Comparar o nome de usuário e a senha inseridos com o nome de usuário e a senha armazenados]
		if (strcmp(temp_username, username) == 0)
		{
			// if (strcmp(temp_password, password) == 0)
			if (passwordIsVerified == true)
			{
				// Update the appContextInfo [Atualizar as informações do appContextInfo]
				sysData->appContext->session = true;															 // Set the session flag to TRUE [Definir a flag de sessão como TRUE]
				sysData->appContext->currentUserID = sysData->users[i].userID;		 // Set the current user ID [Definir o ID do usuário atual]
				sysData->appContext->currentUserName = sysData->users[i].userName; // Set the current user name [Definir o nome do usuário atual]
				sysData->appContext->currentUserRoleID = sysData->users[i].roleID; // Set the current user role [Definir o papel do usuário atual]
				// sysData->users[i].last_seen = getCurrentDateTime(2);			// Update the last seen time [Atualizar o horário da última visualização]
				sysData->appContext->isAuthenticated = true; // Set the authentication flag to TRUE [Definir a flag de autenticação como TRUE]
				logMessages(LOG_INFO, UI_SUCCESSFUL_LOGIN);
				// printf("\n   %s\n", UI_SUCCESSFUL_LOGIN);
				sleep(MID_SLEEP);
				return sysData->appContext->isAuthenticated; // Return TRUE if authentication is successful [Retornar TRUE se a autenticação for bem-sucedida]
			}
			else
			{
				logMessages(LOG_ERROR, UI_ERROR_INVALID_PASSWORD);
				// printf("\n   %s\n", UI_ERROR_INVALID_PASSWORD);
				sleep(MID_SLEEP);
				sysData->appContext->isAuthenticated = false; // Set the authentication flag to FALSE if the password is incorrect [Definir a flag de autenticação como FALSE se a senha estiver incorreta]
				return sysData->appContext->isAuthenticated;	// Return FALSE if the password is incorrect [Retornar FALSE se a senha estiver incorreta]
			}
		}
		// else if (strcmp(temp_password, password) == 0)
		else if (passwordIsVerified == true)
		{
			logMessages(LOG_ERROR, UI_ERROR_INVALID_USERNAME);
			// printf("\n   %s\n", UI_ERROR_INVALID_USERNAME);
			sleep(MID_SLEEP);
			sysData->appContext->isAuthenticated = false; // Set the authentication flag to FALSE if the username is incorrect [Definir a flag de autenticação como FALSE se o nome de usuário estiver incorreto]
			return sysData->appContext->isAuthenticated;	// Return FALSE if the username is incorrect [Retornar FALSE se o nome de usuário estiver incorreto]
		}
		else
		{
			logMessages(LOG_ERROR, UI_ERROR_INVALID_CREDENTIALS);
			// printf("\n   %s\n", UI_ERROR_INVALID_CREDENTIALS); // Invalid username or password [Nome de usuário ou senha inválidos]
			sleep(MID_SLEEP);
			sysData->appContext->isAuthenticated = false; // Set the authentication flag to FALSE if the credentials are invalid [Definir a flag de autenticação como FALSE se as credenciais forem inválidas]
			return sysData->appContext->isAuthenticated;	// Return FALSE if the credentials are invalid [Retornar FALSE se as credenciais forem inválidas]
		}
	}
	return sysData->appContext->isAuthenticated; // User authentication failed [Falha na autenticação do usuário]
}

void grantLoginAccess(SystemData *sysData, int userID)
{
	if (sysData == NULL || userID < 0)
	{
		logMessages(LOG_ERROR, UI_ERROR_USER_NOT_FOUND);
		// printf("%s\n", UI_ERROR_DATA_NOT_FOUND);
		sleep(MIN_SLEEP);
		return; // If the system data or input is invalid, exit the function [Se os dados do sistema ou a entrada forem inválidos, saia da função]
	}
	sysData->appContext->currentUserRoleID = getUserRoleByID(sysData, userID); // Get the user role based on username and password [Obter o papel do usuário com base no nome de usuário e na senha]

	if (sysData->appContext->currentUserRoleID != false)
	{
		if (sysData->users->userStatus != active)
		{
			logMessages(LOG_WARNING, UI_USER_NOT_ACTIVE);
			logMessages(LOG_WARNING, UI_REDIRECT_TO_LIMITED_ACCESS);
			// printf("%s\n", UI_USER_NOT_ACTIVE);
			sleep(MID_SLEEP);
			// limitedAccessMenu(sysData);
			return;
		}
		else
		{
			// if (strcmp(currentUserRole, "admin") == 0 || strcmp(currentUserRole, "Admin") == 0)
			if (sysData->appContext->currentUserRoleID == ROLE_ADMIN)
			{
				// adminMenu(sysData); // If the user is an admin, grant access to the admin menu [Se o usuário for um administrador, conceder acesso ao menu de administração]
			}
			else if (sysData->appContext->currentUserRoleID == ROLE_USER)
			{
				// userMenu(sysData); // If the user is not an admin, grant access to the user menu [Se o usuário não for um administrador, conceder acesso ao menu de usuário]
			}
			else
			{
				logMessages(LOG_ERROR, UI_USER_ROLE_NOT_FOUND);
				// printf("%s\n", UI_ERROR_ROLE_NOT_FOUND);
				sleep(MIN_SLEEP);
				return;
			}
		}
	}
	else
	{
		logMessages(LOG_ERROR, UI_USER_ROLE_NOT_FOUND);
		// printf("%s\n", UI_ERROR_ROLE_NOT_FOUND);
		sleep(MIN_SLEEP);
		return;
	}
}

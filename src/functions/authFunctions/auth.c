#include "../include/unicambio.h"
#include "../include/auth.h"
#include "../include/utilities.h"
#include "../include/logger.h"
#include "../include/structures.h"
#include "../include/enum.h"
#include "../include/homePageMenu.h"
#include "../include/grantAdminAccessMenu.h"
#include "../include/grantUserAccessMenu.h"
#include "../include/grantLimitedAccessMenu.h"

char *hashPassword(const char *password)
{
	char *hashStr = malloc(crypto_pwhash_STRBYTES);

	if (!hashStr)
	{
		printf("\n\n");
		logPrintMessage(LOG_ERROR, "Failed to allocate memory for hash string [ Falha ao alocar memória para a string de hash ]", yes);
		return NULL;
	}
	if (crypto_pwhash_str(hashStr, password, strlen(password), crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0)
	{
		printf("\n\n");
		logPrintMessage(LOG_ERROR, "Failed to hash password [ Falha ao hashar a senha ]", yes);
		free(hashStr);
		return NULL;
	}
	else
	{
		return hashStr;
	}
}

int verifyPassword(const char *password, const char *hash)
{
	if (crypto_pwhash_str_verify(hash, password, strlen(password)) == 0)
	{
		return true;
	}
	return false;
}

StatusInfo loginPageMenu(SystemData *sysData)
{
	StatusInfo status = failed;

	if (!sysData->appContext)
	{
		printf("\n\n");
		logPrintMessage(LOG_ERROR, "Failed to access app context [ Falha ao acessar o contexto da aplicação ]", yes);
		status = failed;
		return status;
	}

	char username[MAX_NAME_LENGTH], password[MAX_PASSWORD_LENGTH];

	if (sysData->userCount == 0)
	{
		printf("\n\n");
		logPrintMessage(LOG_ERROR, "No user in the system. Please create a default admin user by filling the .env file", yes);
		logPrintMessage(LOG_ERROR, "[ Nenhuma pessoa cadastrada no sistema. Por favor, crie um usuário admin padrão preenchendo o arquivo .env ]", yes);
		status = failed;
		return status;
	}
	else
	{
		int usernameInputResult, passwordInputResult;

		while (sysData->appContext->exitFlag == false && sysData->appContext->isAuthenticated == false)
		{
			displayBanner(sysData);
			printf("\n\t\t\t\t\t\t\t  Maximum Trials [Máximo de tentativas]: %d\n", MAX_LOGIN_ATTEMPTS);
			printf("\t\t\t\t\t\t\tRemaining Trials [Tentativas restantes]: %d\n\n", MAX_LOGIN_ATTEMPTS - sysData->appContext->loginAttempts);

			centerStrings("LOGIN PAGE [PÁGINA DE LOGIN]\n\n");
			centerStrings("Input 0 to go back to the previous page [Digite 0 para voltar para a página anterior]\n\n");

			printf("Enter your username [Digite seu nome de usuário]: ");
			usernameInputResult = scanf("%[^\n]", username);
			clearInputBuffer();

			if (usernameInputResult != 1 || strlen(username) == 0)
			{
				printf("\n\n");
				logPrintMessage(LOG_ERROR, "Username cannot be empty [O nome de usuário não pode estar vazio]", yes);
				continue;
			}
			if (strcmp(username, "0") == 0)
			{
				sysData->appContext->goBack = true;
				status = successful;
				return status;
			}
			printf("\n\n");
			printf("Enter your password [Digite sua senha]: ");
			passwordInputResult = scanf("%[^\n]", password);
			clearInputBuffer();

			if (passwordInputResult != 1 || strlen(password) == 0)
			{
				printf("\n\n");
				logPrintMessage(LOG_ERROR, "Password cannot be empty [A senha nao pode estar vazia]", yes);
				continue;
			}
			if (strcmp(password, "0") == 0)
			{
				sysData->appContext->goBack = true;
				status = successful;
				return status;
			}

			sysData->appContext->isAuthenticated = authenticateUser(sysData, username, password);

			if (sysData->appContext->isAuthenticated == false && sysData->appContext->loginAttempts == (MAX_LOGIN_ATTEMPTS - 1))
			{
				printf("\n\n");
				logPrintMessage(LOG_ERROR, "Maximum login attempts reached. Please try again later", yes);
				logPrintMessage(LOG_ERROR, " [O limite de tentativas de login foi alcancado. Por favor, tente novamente mais tarde]", yes);
				sysData->appContext->goBack = true;
				sysData->appContext->loginAttempts = 0;
				status = failed;
				return status;
			}
			sysData->appContext->loginAttempts++;
		}

		if (sysData->appContext->isAuthenticated == true)
		{
			sysData->appContext->goBack = false;
			status = grantLoginAccess(sysData, sysData->appContext->currentUserID);
		}
		return status;
	}
	return status;
}

BoolInfo authenticateUser(SystemData *sysData, char *username, char *password)
{
	BoolInfo auth = false;

	char temp_username[MAX_NAME_LENGTH], temp_password[MAX_PASSWORD_LENGTH];
	if (!sysData)
	{

		printf("\n\n");
		logPrintMessage(LOG_ERROR, "Failed to access system data [ Falha ao acessar os dados do sistema ]", yes);
		auth = false;
		return auth;
	}
	if (sysData->userCount == 0)
	{
		printf("\n\n");
		logPrintMessage(LOG_ERROR, "No user in the system. Please create a default admin user by filling the .env file", yes);
		logPrintMessage(LOG_ERROR, "[ Nenhuma pessoa cadastrada no sistema. Por favor, crie um usuário admin padrão preenchendo o arquivo .env ]", yes);
		auth = false;
		return auth;
	}
	for (size_t i = 0; i < sysData->userCount; i++)
	{
		strcpy(temp_username, sysData->users[i].username);
		strcpy(temp_password, sysData->users[i].password);

		if (strcmp(username, temp_username) == 0)
		{
			if (verifyPassword(password, temp_password))
			{
				if (sysData->users[i].userStatus == deleted)
				{
					printf("\n\n");
					logPrintMessage(LOG_ERROR, "User is deleted [ Usuário excluído ]", yes);
					sysData->appContext->isAuthenticated = false;
					auth = false;
					return auth;
				}
				sysData->appContext->currentUserID = sysData->users[i].userID;
				sysData->appContext->currentUserRoleID = sysData->users[i].roleID;
				sysData->appContext->session = true;
				sysData->appContext->currentUserName = sysData->users[i].username;
				sysData->appContext->isAuthenticated = true;
				printf("\n\n");
				logPrintMessage(LOG_SUCCESS, "User authenticated successfully [ Usuário autenticado com sucesso ]", yes);
				auth = true;
				return auth;
			}
			else
			{
				printf("\n\n");
				logPrintMessage(LOG_ERROR, "Password is incorrect [ Senha incorreta ]", yes);
				auth = false;
				return auth;
			}
		}
		else if (strcmp(username, temp_username) != 0)
		{
			if (verifyPassword(password, temp_password))
			{
				printf("\n\n");
				logPrintMessage(LOG_ERROR, "Username is incorrect [ Nome de usuário incorreto ]", yes);
				auth = false;
				return auth;
			}
		}
	}
	printf("\n\n");
	logPrintMessage(LOG_ERROR, "Invalid Username and Password [ Nome de usuário e senha inválidos ]", yes);
	return auth;
}

StatusInfo grantLoginAccess(SystemData *sysData, int userID)
{
	StatusInfo status;
	displayBanner(sysData);
	if (!sysData)
	{
		printf("\n\n");
		logPrintMessage(LOG_ERROR, "Failed to access system data [ Falha ao acessar os dados do sistema ]", yes);
		status = failed;
		return status;
	}
	if (userID < 0)
	{
		printf("\n\n");
		logPrintMessage(LOG_ERROR, "Invalid user ID [ID de usuário inválido]", yes);
		status = failed;
		return status;
	}
	if (!sysData->appContext)
	{
		printf("\n\n");
		logPrintMessage(LOG_ERROR, "Failed to access application context [ Falha ao acessar o contexto da aplicação ]", yes);
		status = failed;
		return status;
	}

	size_t zerro = 0;

	size_t userIndex = getUserIndexByID(sysData, userID);
	if (userIndex < zerro)
	{
		printf("\n\n");
		logPrintMessage(LOG_ERROR, "Invalid user ID [ID de usuário inválido]", yes);
		status = failed;
		return status;
	}
	if (sysData->users[userIndex].userStatus == active)
	{
		if (sysData->appContext->currentUserRoleID == ROLE_ADMIN)
		{
			printf("\n\n");
			logPrintMessage(LOG_SUCCESS, "Login Successful [Login efetuado com sucesso]", yes);
			logPrintMessage(LOG_SUCCESS, "Admin Access Granted [Acesso de admin concedido]", yes);
			processing();
			grantAdminAccessMenu(sysData);
			status = successful;
			return status;
		}
		else if (sysData->appContext->currentUserRoleID == ROLE_USER)
		{
			printf("\n\n");
			logPrintMessage(LOG_SUCCESS, "Login Successful [Login efetuado com sucesso]", yes);
			logPrintMessage(LOG_SUCCESS, "User Access Granted [Acesso de usuário concedido]", yes);
			processing();
			grantUserAccessMenu(sysData);
			status = successful;
			return status;
		}
		else
		{
			printf("\n\n");
			logPrintMessage(LOG_ERROR, "Invalid role ID [ID de papel inválido]", yes);
			logPrintMessage(LOG_WARNING, "User will be limited to view only functions.", yes);
			logPrintMessage(LOG_WARNING, " [Usuário será limitado aos funções de visualização]", yes);
			grantLimitedAccessMenu(sysData);
			status = successful;
			return status;
		}
	}
	else
	{
		printf("\n\n");
		logPrintMessage(LOG_WARNING, "User is inactive and will be limited to view only functions.", yes);
		logPrintMessage(LOG_WARNING, " [Usuário inativo e serão limitados aos funções de visualização]", yes);
		grantLimitedAccessMenu(sysData);
		status = successful;
		return status;
	}
	return status;
}

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
		logPrintMessage(LOG_ERROR, "Failed to allocate memory for hash string [ Falha ao alocar memória para a string de hash ]", yes);
		return NULL;
	}
	if (crypto_pwhash_str(hashStr, password, strlen(password), crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0)
	{
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
	if (!sysData->appContext)
	{
		logPrintMessage(LOG_ERROR, "Failed to access app context [ Falha ao acessar o contexto da aplicação ]", yes);
		return failed;
	}
	int exitFlag = sysData->appContext->exitFlag, loginAttempts = sysData->appContext->loginAttempts, session = sysData->appContext->session, goBack = sysData->appContext->goBack, isAuthenticated = sysData->appContext->isAuthenticated;
	char username[MAX_NAME_LENGTH], password[MAX_PASSWORD_LENGTH];

	if (sysData->userCount == 0)
	{
		logPrintMessage(LOG_ERROR, "No user in the system. Please create a default admin user by filling the .env file", yes);
		logPrintMessage(LOG_ERROR, "[ Nenhuma pessoa cadastrada no sistema. Por favor, crie um usuário admin padrão preenchendo o arquivo .env ]", yes);
		return failed;
	}
	else
	{
		do
		{
			while (loginAttempts < MAX_LOGIN_ATTEMPTS && isAuthenticated == false)
			{
				displayBanner();
				if (isAuthenticated == false)
				{
					printf("\n\t\t\t\t\t\tMaximum Trials [Máximo de tentativas]: %d\n", MAX_LOGIN_ATTEMPTS);
					printf("\t\t\t\t\t\tRemaining Trials [Tentativas restantes]: %d\n\n", MAX_LOGIN_ATTEMPTS - loginAttempts);

					centerStrings("LOGIN PAGE [PÁGINA DE LOGIN]\n\n");
					centerStrings("Input 0 to go back to the previous page [Digite 0 para voltar para a página anterior]\n\n");

					printf("Enter your username [Digite seu nome de usuário]: ");
					scanf("%149s", username);
					if (username[0] == '0' && strlen(username) == 1)
					{
						goBack = true;
						homePageMenu(sysData);
					}

					printf("Enter your password [Digite sua senha]: ");
					scanf("%149s", password);
					if (password[0] == '0' && strlen(password) == 1)
					{
						goBack = true;
						homePageMenu(sysData);
					}
					if (strlen(username) == 0 || strlen(password) == 0)
					{
						centerStrings(UI_ERROR_INVALID_DATE);
						continue;
					}

					isAuthenticated = authenticateUser(sysData, username, password);

					// if (isAuthenticated == false)
					// {
					// if (loginAttempts == MAX_LOGIN_ATTEMPTS)
					// {
					// 	logPrintMessage(LOG_ERROR, "Maximum login attempts reached [Limite de tentativas de login alcancado]", yes);
					// 	logPrintMessage(LOG_ERROR, "[Limite de tentativas de login alcancado]", yes);
					// 	exitFlag = true;
					// 	loginAttempts = 0;
					// 	session = false;
					// 	goBack = true;
					// 	homePageMenu(sysData);
					// 	return isAuthenticated;
					// }
					// }
					loginAttempts++;
				}
			}
			if (isAuthenticated == false)
			{
				if (loginAttempts >= MAX_LOGIN_ATTEMPTS)
				{
					displayBanner();
					logPrintMessage(LOG_ERROR, "Maximum login attempts reached [Limite de tentativas de login alcancado]", yes);
					logPrintMessage(LOG_ERROR, "[Limite de tentativas de login alcancado]", yes);
					exitFlag = true;
					loginAttempts = 0;
					session = false;
					goBack = true;
					homePageMenu(sysData);
					return isAuthenticated;
				}
			}

		} while (exitFlag == false && isAuthenticated == false);
	}
	if (isAuthenticated == true)
	{
		grantLoginAccess(sysData, sysData->appContext->currentUserID);
	}
}

int authenticateUser(SystemData *sysData, char *username, char *password)
{
	int isAuthenticated = false, passwordIsVerified = false;
	char temp_username[MAX_NAME_LENGTH], temp_password[MAX_PASSWORD_LENGTH];
	if (!sysData)
	{
		logPrintMessage(LOG_ERROR, "Failed to access system data [ Falha ao acessar os dados do sistema ]", yes);
		return false;
	}
	if (sysData->userCount == 0)
	{
		logPrintMessage(LOG_ERROR, "No user in the system. Please create a default admin user by filling the .env file", yes);
		logPrintMessage(LOG_ERROR, "[ Nenhuma pessoa cadastrada no sistema. Por favor, crie um usuário admin padrão preenchendo o arquivo .env ]", yes);
		return false;
	}
	for (size_t i = 0; i < sysData->userCount; i++)
	{
		strcpy(temp_username, sysData->users[i].username);
		strcpy(temp_password, sysData->users[i].password);
		passwordIsVerified = verifyPassword(password, temp_password);
		if (strcmp(temp_username, username) == 0)
		{
			if (passwordIsVerified == true)
			{
				sysData->appContext->session = true;
				sysData->appContext->currentUserID = sysData->users[i].userID;
				sysData->appContext->currentUserName = sysData->users[i].username;
				sysData->appContext->currentUserRoleID = sysData->users[i].roleID;
				sysData->appContext->isAuthenticated = true;
				logPrintMessage(LOG_SUCCESS, "User authenticated successfully [ Usuário autenticado com sucesso ]", yes);
				return sysData->appContext->isAuthenticated;
			}
			else
			{
				logPrintMessage(LOG_ERROR, "Password is incorrect [ Senha incorreta ]", yes);
				sysData->appContext->isAuthenticated = false;
				return sysData->appContext->isAuthenticated;
			}
		}
		else if (passwordIsVerified == true)
		{
			logPrintMessage(LOG_ERROR, "Username is incorrect [ Nome de usuário incorreto ]", yes);
			sysData->appContext->isAuthenticated = false;
			return sysData->appContext->isAuthenticated;
		}
		else
		{
			logPrintMessage(LOG_ERROR, "Invalid Credentials [Credenciais inválidas]", yes);
		}
	}
	return sysData->appContext->isAuthenticated;
}

StatusInfo grantLoginAccess(SystemData *sysData, int userID)
{
	displayBanner();
	if (!sysData)
	{
		logPrintMessage(LOG_ERROR, "Failed to access system data [ Falha ao acessar os dados do sistema ]", yes);
		return failed;
	}
	if (userID < 0)
	{
		logPrintMessage(LOG_ERROR, "Invalid user ID [ID de usuário inválido]", yes);
		return failed;
	}
	if (!sysData->appContext)
	{
		logPrintMessage(LOG_ERROR, "Failed to access application context [ Falha ao acessar o contexto da aplicação ]", yes);
		return failed;
	}

	int userRole = sysData->appContext->currentUserRoleID;

	size_t userIndex = getUserIndexByID(sysData, userID);
	if (userIndex < 0)
	{
		logPrintMessage(LOG_ERROR, "Invalid user ID [ID de usuário inválido]", yes);
		return failed;
	}
	if (sysData->users[userIndex].userStatus == active)
	{
		if (sysData->users[userIndex].roleID == ROLE_ADMIN)
		{
			logPrintMessage(LOG_SUCCESS, "Login Successful [Login efetuado com sucesso]", yes);
			logPrintMessage(LOG_SUCCESS, "Admin Access Granted [Acesso de admin concedido]", yes);
			processing();
			grantAdminAccessMenu(sysData);
			return successful;
		}
		else if (sysData->users[userIndex].roleID == ROLE_USER)
		{
			logPrintMessage(LOG_SUCCESS, "Login Successful [Login efetuado com sucesso]", yes);
			logPrintMessage(LOG_SUCCESS, "User Access Granted [Acesso de usuário concedido]", yes);
			processing();
			grantUserAccessMenu(sysData);
			return successful;
		}
		else
		{
			logPrintMessage(LOG_ERROR, "Invalid role ID [ID de papel inválido]", yes);
			logPrintMessage(LOG_WARNING, "User will be limited to view only functions.", yes);
			logPrintMessage(LOG_WARNING, " [Usuário será limitado aos funções de visualização]", yes);
			grantLimitedAccessMenu(sysData);
			return successful;
		}
	}
	else
	{
		logPrintMessage(LOG_WARNING, "User is inactive and will be limited to view only functions.", yes);
		logPrintMessage(LOG_WARNING, " [Usuário inativo e serão limitados aos funções de visualização]", yes);
		grantLimitedAccessMenu(sysData);
		return successful;
	}

	return failed;
}

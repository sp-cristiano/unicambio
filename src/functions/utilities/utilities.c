/**
 * @file utilities.c
 * @author Chinedum Odili (https://github.com/sp-cristiano)
 * @version 0.1
 * @date 2025-06-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../include/unicambio.h"
#include "../include/messages.h"
#include "../include/utilities.h"
#include "../include/structures.h"
#include "../include/logger.h"
#include "../include/homePageMenu.h"

// convert to uppercase
char *toUpperCase(char *str)
{
	char *p = str;
	while (*p)
	{
		*p = (char)toupper((unsigned char)*p);
		p++;
	}
	return str;
}

void centerStringOnly(char *string)
{
	int len = strlen(string);
	int leftSpaces = (SCREEN_WIDTH - len) / 2;

	for (int i = 0; i < leftSpaces; i++)
	{
		printf(" ");
	}
	printf("%s\n", string);
	return;
}

void alignStringRightOnly(char *string)
{

	int len = strlen(string);
	int leftSpaces = (SCREEN_WIDTH - len);
	for (int i = 0; i < leftSpaces; i++)
	{
		printf(" ");
	}
	printf("%s\n", string);
	return;
}

//  print specific simbol
void printSymbols(int quantity, char simbol)
{
	for (int i = 0; i < quantity; i++)
	{
		printf("%c", simbol);
	}
	printf("\n");
}
/*
******************************************************************************
This function will display the banner of the program.
[Esta função exibirá o banner do programa.]
******************************************************************************
*/
void displayBanner()
{
	clearScreen();
	printf("\n");
	char *dateTime = getCurrentDateTime(TYPE_DATE_TIME);
	printSymbols(SCREEN_WIDTH, '*');
	alignStringRightOnly(SYSTEM_VERSION);
	centerStringOnly(UI_LABEL_TITLE);
	centerStringOnly(" ");
	centerStringOnly(UI_LABEL_TITLE_DESCRIPTION1);
	centerStringOnly(UI_LABEL_TITLE_DESCRIPTION2);
	centerStringOnly(" ");
	printSymbols(SCREEN_WIDTH, '*');
	printf("\n");
	alignStringRightOnly(dateTime);

	// Free dynamically allocated memory [Liberar memória dinâmica]
	free(dateTime);
}

/*
******************************************************************************
This function will clear the screen.
[Esta função limpará a tela.]
******************************************************************************
*/
void clearScreen()
{
#ifdef _WIN32
	system("cls"); // For Windows
#else
	system("clear"); // For Unix/Linux
#endif
}

/*
******************************************************************************
This function will set the current locale to the user's locale.
[Esta função definirá o local atual para o local do usuário.]
******************************************************************************
*/
int setLocation()
{
	if (setlocale(LC_ALL, "") == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_LOCALE);
		// printf("%s\n", UI_ERROR_LOCALE);
		return -1; // Return -1 on error
	}
	return 0;
}

/*
******************************************************************************
This function will print the current date and time.
[Esta função imprimirá a data e hora atuais.]
******************************************************************************
*/

char *getCurrentDateTime(int type)
{
	time_t now = time(NULL);
	struct tm t;
	char formatBuffer[MAX_DATE_LENGTH];

	if (localtime_r(&now, &t) == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_INVALID_DATE);
		return strdup(UI_ERROR_INVALID_DATE); // Allocated error message [Mensagem de erro alocada]
	}

	switch (type)
	{
	case TYPE_DATE:
		strftime(formatBuffer, sizeof(formatBuffer), DATE_FORMAT, &t);
		break;
	case TYPE_TIME:
		strftime(formatBuffer, sizeof(formatBuffer), TIME_FORMAT, &t);
		break;
	default:
		strftime(formatBuffer, sizeof(formatBuffer), DATE_TIME_FORMAT, &t);
		break;
	}

	return strdup(formatBuffer); // Caller must free()
}

/*
******************************************************************************
This function generates random numbers within a specified range.
[Esta função gera números aleatórios dentro de um intervalo especificado.]
******************************************************************************
*/
int randomNumber(int min, int max)
{
	if (min > max)
	{
		// printf("%s\n", UI_ERROR_RANDOM_NUMBER);
		logMessages(LOG_ERROR, UI_ERROR_RANDOM_NUMBER);
		return -1; // Return -1 on error
	}
	else
	{
		// Seed the random number generator to ensure different results each time the program runs
		// [para garantir resultados diferentes cada vez que o programa é executado]
		srand(time(NULL));
		int rand_num = rand() % (max - min + 1) + min;
		return rand_num; // Return the generated random number
	}
}

/*
******************************************************************************
This function will terminate user session
[Esta função encerrará a sessão do usuário]
******************************************************************************
*/

void logOut(SystemData *sysData)
{
	char choice;
	do
	{
		displayBanner();

		printf("   %s", UI_CONFIRMATION_LOGOUT);
		scanf(" %c", &choice);
		if (choice != 'y' && choice != 'Y' && choice != 's' && choice != 'S' && choice != 'n' && choice != 'N')
		{
			logMessages(LOG_ERROR, UI_ERROR_INVALID_INPUT);
			// printf("\n\n   %s\n", UI_ERROR_INVALID_INPUT);
			sleep(MID_SLEEP);
		}
	} while (choice != 'y' && choice != 'Y' && choice != 's' && choice != 'S' && choice != 'n' && choice != 'N');

	if (choice == 'y' || choice == 'Y' || choice == 's' || choice == 'S')
	{
		displayBanner();

		sysData->appContext->exitFlag = false;				// Set the exit flag to FALSE[Definir a flag de saída como FALSE]
		sysData->appContext->isAuthenticated = false; // Set the authentication flag to FALSE[Definir a flag de autenticação como FALSE]
		sysData->appContext->loginAttempts = 0;				// Reset login attempts [Redefinir tentativas de login]
		sysData->appContext->session = false;					// Set the session flag to FALSE[Definir a flag de sessão como FALSE]
		sysData->appContext->goBack = false;					// Set the go back flag to FALSE[Definir a flag de voltar como FALSE]
		sysData->appContext->currentUserID = 0;				// Set the current user ID to 0[Definir o ID do usuário atual como 0]
		sysData->appContext->currentUserRoleID = 0;		// Set the current user role ID to 0[Definir o ID do papel do usuário atual como 0]
		sysData->appContext->currentUserName = NULL;	// Set the current user name to NULL[Definir o nome do usuário atual como NULL]

		logMessages(LOG_INFO, UI_SUCCESSFUL_LOGOUT); // Log the logout message
		// printf("\n        %s\n", UI_SUCCESSFUL_LOGOUT);
		// printf("        %s\n", UI_LABEL_EXIT);
		sleep(MID_SLEEP);
		clearScreen();
	}
	else if (choice == 'n' || choice == 'N')
	{
		return; // Return to the previous menu [Retornar ao menu anterior]
	}
}

/*
******************************************************************************
This function will exit the program gracefully.
[Esta função encerrará o programa de forma elegante.]
******************************************************************************
*/

void exitProgram(SystemData *sysData)
{
	char choice;
	do
	{
		displayBanner();

		printf("   %s", UI_CONFIRM_EXIT);
		scanf(" %c", &choice);
		if (choice != 'y' && choice != 'Y' && choice != 's' && choice != 'S' && choice != 'n' && choice != 'N')
		{
			logMessages(LOG_ERROR, UI_ERROR_INVALID_INPUT);
			// printf("\n\n   %s\n", UI_ERROR_INVALID_INPUT);
			sleep(MID_SLEEP);
		}
	} while (choice != 'y' && choice != 'Y' && choice != 's' && choice != 'S' && choice != 'n' && choice != 'N');

	if (choice == 'y' || choice == 'Y' || choice == 's' || choice == 'S')
	{
		displayBanner();
		sysData->appContext->exitFlag = true;					// Set the exit flag to TRUE[Definir a flag de saída como TRUE]
		sysData->appContext->isAuthenticated = false; // Set the authentication flag to FALSE[Definir a flag de autenticação como FALSE]
		sysData->appContext->loginAttempts = 0;				// Reset login attempts [Redefinir tentativas de login]
		sysData->appContext->session = false;					// Set the session flag to FALSE[Definir a flag de sessão como FALSE]
		sysData->appContext->goBack = false;					// Set the go back flag to FALSE[Definir a flag de voltar como FALSE]
		sysData->appContext->currentUserID = 0;				// Set the current user ID to 0[Definir o ID do usuário atual como 0]
		sysData->appContext->currentUserRoleID = 0;		// Set the current user role ID to 0[Definir o ID do papel do usuário atual como 0]
		sysData->appContext->currentUserName = NULL;	// Set the current user name to NULL[Definir o nome do usuário atual como NULL]

		logMessages(LOG_INFO, UI_LABEL_EXIT); // Log the exit message
		// printf("\n        %s\n", UI_LABEL_EXIT);
		sleep(MID_SLEEP);
		logMessages(LOG_INFO, UI_LABEL_EXIT_MESSAGE);
		// printf("\n        %s\n", UI_LABEL_EXIT_MESSAGE);
		sleep(MID_SLEEP);
		// sleep(MID_SLEEP);
		clearScreen();
		exit(0); // Exit the program [Sair do programa]
	}
	else if (choice == 'n' || choice == 'N')
	{
		homePageMenu(sysData); // Return to the session menu [Retornar ao menu de sessão]
		return;								 // Return to the previous menu [Retornar ao menu anterior]
	}
}

/*
******************************************************************************
This function will get the current user role.
[Esta função obterá o papel do usuário atual.]
******************************************************************************
*/
// const char *getUserRoleByID(SystemData *sysData, int currentUserID)
int getUserRoleByID(SystemData *sysData, int userID)
{
	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		// printf("%s\n", UI_ERROR_DATA_NOT_FOUND);
		sleep(MIN_SLEEP);
		return failed; // If the system data is not initialized, exit the function [Se os dados do sistema não estiverem inicializados, saia da função]
	}

	for (size_t i = 0; i < sysData->userCount; i++)
	{
		if (sysData->users[i].userID == userID)
		{
			return sysData->users[i].roleID; // Return the found user Role ID [Retorne o ID do papel do usuário encontrado]
		}
	}
	printf("User with ID %d not found. [Usuário com ID %d não encontrado.]\n", userID, userID);
	sleep(MID_SLEEP);
	logMessages(LOG_ERROR, UI_ERROR_USER_NOT_FOUND);
	return failed; // If the user is not found, return NULL [Se o usuário não for encontrado, retornar NULL]
}

// Get currency by code, abbreviation or id
int getCurrencyID(SystemData *sysData, const char *code)
{
	if (sysData == NULL)
	{
		logMessages(LOG_ERROR, UI_ERROR_SYSTEM_DATA_IS_NULL);
		centerString(UI_ERROR_SYSTEM_DATA_IS_NULL);
		sleep(MIN_SLEEP);
		return failed;
	}
	char *tempCharCode = malloc(sizeof(char) * MAX_NAME_LENGTH);
	tempCharCode = strcpy(tempCharCode, code);

	toUpperCase(tempCharCode);

	int tempIntCode = atoi(tempCharCode);

	for (size_t i = 0; i < sysData->currencyCount; i++)
	{
		if (sysData->currencies[i].currencyID == tempIntCode || strcmp(sysData->currencies[i].code, tempCharCode) == 0 || strcmp(sysData->currencies[i].abbreviation, tempCharCode) == 0)
		{
			free(tempCharCode);
			return sysData->currencies[i].currencyID;
		}
	}

	free(tempCharCode);
	logMessage(LOG_ERROR, UI_ERROR_CURRENCY_NOT_FOUND);
	centerStringOnly(UI_ERROR_CURRENCY_NOT_FOUND);
	return failed;
}
double calculateRateToOneKz(double rate)
{
	double rateToOneKz = 1 / rate;
	return rateToOneKz;
}
double revertRateFromOneKz(double rateToOneKz){
	double rate = 1 / rateToOneKz;
	return rate;
}

double getCurrencyRateToOneKzByID(SystemData sysData, int currencyID)
{
	for (size_t i = 0; i < sysData.currencyCount; i++)
	{
		if (sysData.currencies[i].currencyID == currencyID)
		{
			return sysData.currencies[i].rateToOneKz;
		}
	}
	return failed;
}
char *getCurrencyCodeByID(SystemData sysData, int currencyID)
{
	for (size_t i = 0; i < sysData.currencyCount; i++)
	{
		if (sysData.currencies[i].currencyID == currencyID)
		{
			return sysData.currencies[i].code;
		}
	}
	return NULL;
}
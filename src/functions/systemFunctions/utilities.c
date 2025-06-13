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
		printf("%s\n", UI_ERROR_LOCALE);
		return -1; // Return -1 on error
	}
	else
	{
		// printf("Locale set to[Local Definido para]: %s\n", setlocale(LC_ALL, NULL));
		setlocale(LC_ALL, NULL);
		return 0; // Return 0 on success
	}
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
This function generates random numbers within a specified range.
[Esta função gera números aleatórios dentro de um intervalo especificado.]
******************************************************************************
*/
int randomNumber(int min, int max)
{
	if (min > max)
	{
		printf("%s\n", UI_ERROR_RANDOM_NUMBER);
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
This function will print the current date and time.
if input is 0 it prints date
if input is 1 it prints time
if input is not 0 or 1 it prints date and time
[Esta função imprimirá a data e hora atuais.
Se a entrada for 0, imprime a data
Se a entrada for 1, imprime a hora
Se a entrada não for 0 ou 1, imprime a data e hora]
******************************************************************************
*/
const char *getCurrentDateTime(int type)
{
	static char dateTime[MAX_DATE_LENGTH];
	time_t now = time(NULL);
	struct tm *t = localtime(&now);

	if (type == 0)
	{ // Date
		strftime(dateTime, sizeof(dateTime), DATE_FORMAT, t);
	}
	else if (type == 1)
	{ // Time
		strftime(dateTime, sizeof(dateTime), TIME_FORMAT, t);
	}
	else
	{
		strftime(dateTime, sizeof(dateTime), DATE_TIME_FORMAT, t);
	}
	return dateTime;
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
	// printf("********************************************************************************************\n");
	// printf("*                                                             Version[Versãon: %s      *\n", SYSTEM_VERSION);
	// printf("*                                                                                          *\n");
	// printf("*                           UNICAMBIO SYSTEM [SISTEMA UNICAMBIO]                           *\n");
	// printf("*                                                                                          *\n");
	// printf("*         A complete solution for currency exchange and transaction management.            *\n");
	// printf("*          [Uma solução completa para troca de moedas e gestão de transações.]             *\n");
	// printf("*                                                                                          *\n");
	// printf("********************************************************************************************\n");

	printf("********************************************************************************************\n");
	printf("*                                                             Version[Versãon: %s      *\n", SYSTEM_VERSION);
	printf("*                                                                                          *\n");
	printf("*                             %s                                                             *\n", UI_TITLE);
	printf("*                                                                                          *\n");
	printf("*         %s                                                                               *\n", UI_TITLE_DESCRIPTION1);
	printf("*         %s                                                                               *\n", UI_TITLE_DESCRIPTION2);
	printf("*                                                                                          *\n");
	printf("********************************************************************************************\n");
	// printf("\n");
	printf("            Current Date and Time [Data e Hora Atuais]: %s        \n\n", getCurrentDateTime(2));
}

/*
******************************************************************************
This function will terminate user session
[Esta função encerrará a sessão do usuário]
******************************************************************************
*/

void terminateSession(SystemData *sysData)
{
	char choice;
	do
	{
		displayBanner();

		printf("   %s", UI_CONFIRM_TERMINATE_SESSION);
		scanf(" %c", &choice);
		if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
		{
			printf("\n\n   %s\n", UI_ERROR_INVALID_INPUT);
			sleep(MID_SLEEP);
		}
	} while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

	if (choice == 'y' || choice == 'Y')
	{
		displayBanner();

		exitFlag = FALSE;					// Set the exit flag to FALSE[Definir a flag de saída como FALSE]
		is_authenticated = FALSE; // Set the authentication flag to FALSE[Definir a flag de autenticação como FALSE]
		session = FALSE;					// Set the session flag to FALSE[Definir a flag de sessão como FALSE]
		loginAttempts = 0;				// Reset login attempts [Redefinir tentativas de login]

		printf("\n        %s\n", UI_SUCCESSFUL_SESSION_ENDED);
		printf("        %s\n", UI_EXIT);
		sleep(MID_SLEEP);
		clearScreen();
	}
	else if (choice == 'n' || choice == 'N')
	{
		// startSession(sysData); // Return to the session menu [Retornar ao menu de sessão]
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
		if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
		{
			printf("\n\n   %s\n", UI_ERROR_INVALID_INPUT);
			sleep(MID_SLEEP);
		}
	} while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

	if (choice == 'y' || choice == 'Y')
	{
		displayBanner();
		exitFlag = TRUE;					// Set the exit flag to TRUE[Definir a flag de saída como TRUE]
		is_authenticated = FALSE; // Set the authentication flag to FALSE[Definir a flag de autenticação como FALSE]
		session = FALSE;					// Set the session flag to FALSE[Definir a flag de sessão como FALSE]
		loginAttempts = 0;				// Reset login attempts [Redefinir tentativas de login]

		printf("\n        %s\n", UI_EXIT);

		printf("\n        %s\n", UI_EXIT_MESSAGE);
		sleep(MID_SLEEP);
		// sleep(MID_SLEEP);
		clearScreen();
		exit(0); // Exit the program [Sair do programa]
	}
	else if (choice == 'n' || choice == 'N')
	{
		startSession(sysData); // Return to the session menu [Retornar ao menu de sessão]
		return;								 // Return to the previous menu [Retornar ao menu anterior]
	}
}
#include "../include/unicambio.h"
#include "../include/structures.h"
#include "../include/enum.h"
#include "../include/logger.h"
#include "../include/saveSystemData.h"
#include "../include/freeSystemData.h"
#include "../include/utilities.h"
#include "../include/homePageMenu.h"

void centerStrings(char *string)
{
	int stringLength = strlen(string);
	int spaces = (SCREEN_WIDTH - stringLength) / 2;
	for (int i = 0; i < spaces; i++)
	{
		printf(" ");
	}
	printf("%s\n", string);
	return;
}

void alignTextRight(char *string)
{
	int stringLength = strlen(string) + 2;
	int spaces = (SCREEN_WIDTH - stringLength);
	for (int i = 0; i < spaces; i++)
	{
		printf(" ");
	}
	printf("%s\n", string);
	return;
}

void printSymbols(int quantity, char symbol)
{
	for (int i = 0; i < quantity; i++)
	{
		printf("%c", symbol);
	}
	printf("\n");
	return;
}

void displayBanner()
{
	clearScreen();
	printf("\n");
	char *dateTime = getCurrentDateTime(TYPE_DATETIME);
	printSymbols(SCREEN_WIDTH, '*');
	alignTextRight(SYSTEM_VERSION);
	centerStrings(UI_LABEL_TITLE);
	centerStrings(" ");
	centerStrings(UI_LABEL_TITLE_DESCRIPTION1);
	centerStrings(UI_LABEL_TITLE_DESCRIPTION2);
	centerStrings(" ");
	printf("\n");
	printSymbols(SCREEN_WIDTH, '*');
	printf("\n");
	alignTextRight(dateTime);
	free(dateTime);
	return;
}

void clearScreen()
{
#ifdef _WIN32
	system("cls"); // Windows
#else
	system("clear"); // Linux
#endif
}

StatusInfo setLocation()
{
	StatusInfo localSet;

	if (setlocale(LC_ALL, "") == NULL)
	{
		logPrintMessage(LOG_WARNING, "Failed to set locale [ Falha ao definir local ]", yes);
		localSet = failed;
		return localSet;
	}
	else
	{
		localSet = successful;
		return localSet;
	}
	return localSet;
}

char *getCurrentDateTime(int type)
{
	time_t now = time(NULL);
	struct tm t;
	char formatBuffer[MAX_DATE_LENGTH];

	if (localtime_r(&now, &t) == NULL)
	{
		logPrintMessage(LOG_ERROR, UI_ERROR_INVALID_DATE, yes);
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
int randomNumber(int min, int max)
{
	if (min > max)
	{
		// printf("%s\n", UI_ERROR_RANDOM_NUMBER);
		logPrintMessage(LOG_ERROR, UI_ERROR_RANDOM_NUMBER, yes);
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

void exitProgram(SystemData *sysData)
{
	char choice;
	do
	{
		displayBanner();
		centerStrings("Are you sure you want to exit this program(y/n)? [Deseja realmente sair deste programa (s/n)?]\n");
		scanf(" %c", &choice);
		if (choice != 'y' && choice != 'Y' && choice != 's' && choice != 'S' && choice != 'n' && choice != 'N')
		{
			logPrintMessage(LOG_ERROR, "Invalid input [Entrada inválida]", yes);
			sleep(MID_SLEEP);
		}
	} while (choice != 'y' && choice != 'Y' && choice != 's' && choice != 'S' && choice != 'n' && choice != 'N');
	if (choice == 'y' || choice == 'Y' || choice == 's' || choice == 'S')
	{
		sysData->appContext->exitFlag = true;
		logPrintMessage(LOG_SUCCESS, "Exiting program... [Saindo do programa...]", yes);
		sleep(MAX_SLEEP);

		saveSystemData(sysData);

		freeSystemData(sysData);
		clearScreen();
		exit(0);
	}
	else if (choice == 'n' || choice == 'N')
	{
		logPrintMessage(LOG_SUCCESS, "Returning to main menu... [Retornando ao menu principal...]", yes);
		sleep(MIN_SLEEP);
		homePageMenu(sysData);
		return;
	}
}
void processing()
{
	printf("Processing [Processando]: ");
	for (int i = 0; i < 90; i++)
	{
		printf("#");
		// sleep(MIN_SLEEP);
	}
	printf("\n");
}
#include "../include/unicambio.h"
#include "../include/structures.h"
#include "../include/enum.h"
#include "../include/logger.h"
#include "../include/saveSystemData.h"
#include "../include/freeSystemData.h"
#include "../include/utilities.h"
#include "../include/homePageMenu.h"
#include "../include/auth.h"

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
// This function will clear input buffer
void clearInputBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
	{
	}
}
// void alignTextTwentyPercentFromLeft(char *string)
// {
// 	int stringLength = strlen(string);
// 	int spaces = (SCREEN_WIDTH - stringLength) / 2;
// 	for (int i = 0; i < spaces; i++)
// 	{
// 		printf(" ");
// 	}
// 	printf("%s\n", string);
// 	return;
// }

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

void displayBanner(SystemData *sysData)
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
	if (sysData->appContext->isAuthenticated == true)
	{
		printf("WELCOME %s [BEM VINDO %s]\n", sysData->appContext->currentUserName, sysData->appContext->currentUserName);
	}
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
void logoutUser(SystemData *sysData)
{
	char choice;
	do
	{
		displayBanner(sysData);
		centerStrings("Are you sure you want to logout(y/n)? [Deseja realmente sair (s/n)?]\n");
		scanf(" %c", &choice);
		if (choice != 'y' && choice != 'Y' && choice != 's' && choice != 'S' && choice != 'n' && choice != 'N')
		{
			logPrintMessage(LOG_ERROR, "Invalid input [Entrada inválida]", yes);
			sleep(MID_SLEEP);
		}
	} while (choice != 'y' && choice != 'Y' && choice != 's' && choice != 'S' && choice != 'n' && choice != 'N');
	if (choice == 'y' || choice == 'Y' || choice == 's' || choice == 'S')
	{
		logPrintMessage(LOG_INFO, "Logging out... [Deslogando...]", yes);
		processing();
		logPrintMessage(LOG_INFO, "Logout successful [Logout realizado com sucesso]", yes);
		sysData->appContext->session = false;
		sysData->appContext->isAuthenticated = false;
		sysData->appContext->currentUserRoleID = 0;
		sysData->appContext->currentUserID = 0;
		sysData->appContext->exitFlag = false;
		sysData->appContext->currentUserName = NULL;

		saveSystemData(sysData);

		loginPageMenu(sysData);
	}
	else if (choice == 'n' || choice == 'N')
	{
		homePageMenu(sysData);
	}
}

void exitProgram(SystemData *sysData)
{
	char choice;
	do
	{
		displayBanner(sysData);
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

		// freeSystemData(sysData);
		clearScreen();
		exit(0);
		return;
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

// size_t getUserIndexByID(SystemData *sysData, int userID)
// {
// 	for (size_t i = 0; i < sysData->userCount; i++)
// 	{
// 		if (sysData->users[i].userID == userID)
// 		{
// 			return i;
// 		}
// 	}
// 	logPrintMessage(LOG_ERROR, "User index not found  [Indice do usuário nao encontrado]", yes);
// 	return failed;
// }
// int getUserIDByMultipleSearch(SystemData *sysData, char *multiSearch)
// {
// if (!sysData)
// {
// 	logPrintMessage(LOG_ERROR, "System data is Null. Failed to get user ID [ Dados do sistema nulo. Falha ao obter ID do usuário ]", yes);
// 	return failed;
// }
// if (!multiSearch)
// {
// 	logPrintMessage(LOG_ERROR, "Invalid input [Entrada inválida]", yes);
// 	return failed;
// }

// char *tempCharMultipleSearch = malloc(sizeof(char) * MAX_NAME_LENGTH);
// if (!tempCharMultipleSearch)
// {
// 	logPrintMessage(LOG_ERROR, "Failed to allocate memory for temporary string [ Falha ao alocar memória para a string temporária ]", yes);
// 	return failed;
// }
// strncpy(tempCharMultipleSearch, multiSearch, MAX_NAME_LENGTH - 1);
// tempCharMultipleSearch[MAX_NAME_LENGTH - 1] = '\0';

// if (strlen(tempCharMultipleSearch) == 0)
// {
// 	logPrintMessage(LOG_ERROR, "Invalid input [Entrada inválida]", yes);
// 	free(tempCharMultipleSearch);
// 	return failed;
// }
// int userID = failed;
// int tempIntMultipleSearch = atoi(tempCharMultipleSearch);

// for (size_t i = 0; i < sysData->userCount; i++)
// {
// 	if (sysData->users[i].userID == tempIntMultipleSearch || (sysData->users[i].username && strcmp(sysData->users[i].username, tempCharMultipleSearch) == 0) || (sysData->users[i].email && strcmp(sysData->users[i].email, tempCharMultipleSearch) == 0) || (sysData->users[i].phone && strcmp(sysData->users[i].phone, tempCharMultipleSearch) == 0))
// 	{
// 		// free(tempCharMultipleSearch);
// 		userID = sysData->users[i].userID;
// 		// printf("%d\n", tempIntMultipleSearch);
// 		return userID;
// 	}
// }
// free(tempCharMultipleSearch);
// if (userID == failed)
// {
// 	logPrintMessage(LOG_ERROR, "User not found while searching [Usuário nao encontrado ao procurar]", yes);
// }
// return userID;
// }

// // Better version
// int getUserIndexByID(SystemData *sysData, int userID, size_t *outIndex)
// {
// 	for (size_t i = 0; i < sysData->userCount; i++)
// 	{
// 		if (sysData->users[i].userID == userID)
// 		{
// 			if (outIndex)
// 				*outIndex = i;
// 			return 0; // success
// 		}
// 	}
// 	return -1; // not found
// }

// int getUserIDByMultipleSearch(SystemData *sysData, char *multiSearch)
// {
// 	if (!sysData || !multiSearch)
// 	{
// 		logPrintMessage(LOG_ERROR, "Invalid input: System data or search string is NULL", yes);
// 		return failed;
// 	}

// 	char tempCharMultipleSearch[MAX_NAME_LENGTH];
// 	strncpy(tempCharMultipleSearch, multiSearch, sizeof(tempCharMultipleSearch) - 1);
// 	tempCharMultipleSearch[sizeof(tempCharMultipleSearch) - 1] = '\0';

// 	if (strlen(tempCharMultipleSearch) == 0)
// 	{
// 		logPrintMessage(LOG_ERROR, "Invalid input: Empty search string", yes);
// 		return failed;
// 	}

// 	errno = 0;
// 	char *endptr;
// 	long tempLong = strtol(tempCharMultipleSearch, &endptr, 10);
// 	int tempIntMultipleSearch = 0;

// 	if (errno == ERANGE || tempLong > INT_MAX || tempLong < INT_MIN)
// 	{
// 		tempIntMultipleSearch = 0; // Out of range
// 	}
// 	else if (endptr != tempCharMultipleSearch && *endptr == '\0')
// 	{
// 		tempIntMultipleSearch = (int)tempLong;
// 	}
// 	else
// 	{
// 		tempIntMultipleSearch = 0; // Not a valid integer
// 	}

// 	int userID = failed;

// 	for (size_t i = 0; i < sysData->userCount; i++)
// 	{
// 		if (sysData->users[i].userID == tempIntMultipleSearch ||
// 				(sysData->users[i].username && strcmp(sysData->users[i].username, tempCharMultipleSearch) == 0) ||
// 				(sysData->users[i].email && strcmp(sysData->users[i].email, tempCharMultipleSearch) == 0) ||
// 				(sysData->users[i].phone && strcmp(sysData->users[i].phone, tempCharMultipleSearch) == 0))
// 		{
// 			userID = sysData->users[i].userID;
// 			break;
// 		}
// 	}

// 	if (userID == failed)
// 	{
// 		logPrintMessage(LOG_ERROR, "User not found while searching [Usuário nao encontrado ao procurar]", yes);
// 	}

// 	return userID;
// }

int getUserIndexByID(SystemData *sysData, int userID)
{
	for (size_t i = 0; i < sysData->userCount; i++)
	{
		if (sysData->users[i].userID == userID)
		{
			return i;
		}
	}
	return failed;
}

StatusInfo viewSingleUser(SystemData *sysData, size_t userIndex)
{
	if (!sysData)
	{
		logPrintMessage(LOG_ERROR, "Failed to access system data [ Falha ao acessar os dados do sistema ]", yes);
		return failed;
	}
	printf("\n");
	centerStrings("===== USER DATA [DADOS DO USUARIO] =====\n");
	printf("User ID [ID do usuário]: %d\n", sysData->users[userIndex].userID);
	printf("User Name [Nome do usuário]: %s\n", sysData->users[userIndex].name);
	printf("User Username [Username do usuário]: %s\n", sysData->users[userIndex].username);
	printf("User Email [Email do usuário]: %s\n", sysData->users[userIndex].email);
	// printf("User Password [Senha do usuário]: %s\n", sysData->users[userIndex].password);
	printf("User Phone [Telefone do usuário]: %s\n", sysData->users[userIndex].phone);
	printf("User Role [Papel do usuário]: %d\n", sysData->users[userIndex].roleID);
	printf("User Status [Status do usuário]: %d\n", sysData->users[userIndex].userStatus);
	printf("User Date Created [Data de criação do usuário]: %s\n", sysData->users[userIndex].dateCreated);
	printf("User Last Updated [Data de atualização do usuário]: %s\n", sysData->users[userIndex].lastUpdated);
	printf("User Last Login [Data de login do usuário]: %s\n", sysData->users[userIndex].lastLogin);
	printf("User Date Deleted [Data de exclusão do usuário]: %s\n", sysData->users[userIndex].dateDeleted);
}
void selectOptionToUpdateUserByAdmin(SystemData *sysData, size_t userIndex)
{
	centerStrings("UPDATE USER PROFILE ");
	printf("FOR %s\n ", sysData->users[userIndex].name);
	centerStrings(" [ATUALIZAR PERFIL DE USUARIO ");
	printf("PARA %s\n", sysData->users[userIndex].name);
	printf("\n");
	centerStrings("Select option from  1 to 7 to navigate this menu. Select 0 to Logout.\n");
	centerStrings("Selecione a opção de 1 a 7 para navegar nesta menu. Selecione 0 para sair.\n");
	printf("\n");
	printf("\n\t\t1. - Update name [Atualizar nome]\n\n");
	printf("\t\t2. - Update username [Atualizar username]\n\n");
	printf("\t\t3. - Update user email [Atualizar email]\n\n");
	printf("\t\t4. - Update user password [Atualizar senha]\n\n");
	printf("\t\t5. - Update user phone [Atualizar telefone]\n\n");
	printf("\t\t6. - Update user role [Atualizar papel]\n\n");
	printf("\t\t7. - Update user status [Atualizar status]\n\n");
	// printf("\t\t8. - Update all user data [Atualizar todos os dados]\n\n");
	printf("\t\t0. - Go Back [Sair]\n\n");
}

double convertRateToOneKz(double rate)
{
	double result = (1 / rate);
	return result;
}
double convertRateFromOneKz(double rateToOneKz)
{
	double result = 1 / rateToOneKz;
	return result;
}
double getCurrencyRateToOneKz(SystemData *sysData, int currencyID)
{
	for (size_t i = 0; i < sysData->currencyCount; i++)
	{
		if (sysData->currencies[i].currencyID == currencyID)
		{
			return sysData->currencies[i].rate;
		}
	}
	return failed;
}
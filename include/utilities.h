#ifndef UTILITIES_H
#define UTILITIES_H

#include "../include/structures.h"

// convert string to uppercase
char *toUpperCase(const char *str);

// Function to print centered lines [Função para imprimir linhas centralizadas]
// void printCenteredLine(char *line);

// Function to center a string [Função para centralizar uma string]
// void centerString(char *string);
void centerStringOnly(char *string);

// Function to align a string to the left [Função para alinhar uma string para a esquerda]
// void alignStringRight(char *string);
void alignStringRightOnly(char *string);

// Function to align a string to the right [Função para alinhar uma string para a direita]
// void rightWrappedString(char *text);

// Function will print simbols [Função para imprimir simbolos]
void printSymbols(int quantity, char simbol);

// Function to display the banner [Função para exibir o banner]
void displayBanner();

// Function to clear the screen [Função para limpar a tela]
void clearScreen();

int setLocation(); // |Function to set location [Função para definir local]

// Function to get the current date and time [Função para obter a data e hora atual]
char *getCurrentDateTime(int type); // type: 0 for date, 1 for time, other for both [tipo: 0 para data, 1 para hora, outro para ambos]

//  Function to generate a random number within a specified range [Função para gerar um número aleatório dentro de um intervalo especificado]
int randomNumber(int min, int max);
// Function to terminate the session [Função para encerrar a sessão]
void logOut(SystemData *sysData);
// Function to exit the application [Função para sair da aplicação]
void exitProgram(SystemData *sysData);
// Function to get the user role by ID [Função para obter o papel do usuário por ID]
int getUserRoleByID(SystemData *sysData, int userID);
// Function to get the currency ID [Função para obter o ID da moeda]
int getCurrencyID(SystemData *sysData, const char *currencyName);
// Function to calculate currencty rate to  one kz of currency
double calculateRateToOneKz(double rate);
// Function to revert rate from one kz
double revertRateFromOneKz(double rateToOneKz);
// Function to get the currency rate by ID [Função para obter o valor do caâmbio por ID]
double getCurrencyRateToOneKzByID(SystemData *sysData, int currencyID);
// Function to get the currency code by id
char *getCurrencyCodeByID(SystemData *sysData, int currencyID);
int getUserIDByMultipleSearch(SystemData *sysData, const char *multipleSearch);
#endif // UTILITIES_H
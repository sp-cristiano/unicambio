/**
 * @author Chinedum Odili (https://github.com/ChinedumOdili)
 * @version 1.0
 */
/*
*****************************************************************************************
This file is the header file for the unicambio project.
[Este arquivo é o arquivo de cabeçalho para o projeto unicambio.]
*****************************************************************************************
*/

// *** PROTOTYPES FOR UTILITIES FUNCTIONS [PROTÓTIPOS PARA FUNÇÕES DE UTILIDADES] ***

#ifndef UTILITIES_H
#define UTILITIES_H
#include "../include/structures.h"

int setLocation(); // |Function to set location [Função para definir local]

// Function to get the current date and time [Função para obter a data e hora atual]
char *getCurrentDateTime(int type); // type: 0 for date, 1 for time, other for both [tipo: 0 para data, 1 para hora, outro para ambos]

// Function to clear the screen [Função para limpar a tela]
void clearScreen();
//  Function to generate a random number within a specified range [Função para gerar um número aleatório dentro de um intervalo especificado]
int randomNumber(int min, int max);
// Function to display the banner [Função para exibir o banner]
void displayBanner();
// Function to terminate the session [Função para encerrar a sessão]
void terminateSession(SystemData *sysData);
// Function to exit the application [Função para sair da aplicação]
void exitProgram(SystemData *sysData);
// Function to get the value of an environment variable from a file [Função para obter o valor de uma variável de ambiente de um arquivo]
char *get_env_value(const char *key, const char *filename);
// Function to load environment variables from a file [Função para carregar variáveis de ambiente de um arquivo]
int load_env(const char *filename);
void free_env();
#endif // UTILITIES_H
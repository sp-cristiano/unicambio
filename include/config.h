/**
 * @file config.h
 * @author Chinedum Odili (https://github.com/ChinedumOdili)
 * @brief A header file for the unicambio project [Arquivo de cabeçalho para o projeto unicambio]
 * This file is used to define macros or constant values.
 * [Este arquivo é usado para definir macros ou valores constantes.]
 * @version 1.0
 */

/*
*****************************************************************************************
This file is the header file for the unicambio project.
[Este arquivo é o arquivo de cabeçalho para o projeto unicambio.]
*****************************************************************************************
*/
#ifndef CONFIG_H
#define CONFIG_H

/*
*****************************************************************************************
File inclusion directives.
[Diretivas de inclusão de arquivos.]
*****************************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>

/*
*****************************************************************************************
Macro definitions.
[Definições de macros.]
*****************************************************************************************
*/
#define SYSTEM_NAME "unicambio"
#define SYSTEM_DESCRIPTION "A simple currency exchange system [Um sistema simples de câmbio de moedas]"
#define SYSTEM_VERSION "1.0.0"
#define LOG_FILE "unicambio.log"
#define CONFIG_FILE "unicambio.conf"
#define CURRENCY_FILE "currencies.txt"
#define USER_FILE "../../DB/users.txt"
#define ROLE_FILE "../../DB/roles.txt"
#define RATE_FILE "../../DB/rates.txt"
#define TRANSACTION_FILE "../../DB/transactions.txt"
#define TRUE 1
#define FALSE 0
#define MIN_SLEEP 2
#define MID_SLEEP 3
#define MAX_SLEEP 4
#define MAX_LOGIN_ATTEMPTS 5
#define MAX_NAME_LENGTH 150
#define MAX_DATE_LENGTH 100
#define MAX_DESCRIPTION_LENGTH 500
#define ADMIN_USER "admin"
#define ADMIN_USER_DESCRIPTION "Administrator role with full access [Papel de administrador com acesso completo]"
#define ADMIN_USER_EMAIL "odili.official@gmail.com"
#define ADMIN_USER_PASSWORD "password123" // Default password for admin [Senha padrão para administrador]
#define ADMIN_USER_PHONE "930725410"			// Default phone number for admin [Número de telefone padrão para administrador]

#define DATE_FORMAT "%d-%m-%Y"									 // Date format: day-month-year [Formato de data: dia-mês-ano]
#define TIME_FORMAT "%H:%M:%S"									 // Time format: hour:minute:second [Formato de hora: hora:minuto:segundo]
#define DATE_TIME_FORMAT "%d-%m-%Y  |  %H:%M:%S" // Date and time format: day-month-year hour:minute:second [Formato de data e hora: dia-mês-ano hora:minuto:segundo]

#endif // CONFIG_H

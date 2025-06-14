/**
 * @file config.h
 * @author Chinedum Odili (https://github.com/ChinedumOdili)
 * @brief Header file containing library file inclusion directives, macro definitions, and constant values for the unicambio project.
 * [Arquivo de cabeçalho contendo diretivas de inclusão de arquivos de biblioteca, definições de macros e valores constantes para o projeto unicambio.]
 *
 * @version 1.0
 */

#ifndef CONFIG_H
#define CONFIG_H

/*
==================================================================================================================
																			File inclusion directives
																			[Diretivas de inclusão de arquivos]
==================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>
#include <stddef.h>
#include <sodium.h>

/*
==================================================================================================================

																			Macro definitions
																			[Definições de macros]
==================================================================================================================

*/

// System Profile
#define SYSTEM_NAME "unicambio"
#define SYSTEM_DESCRIPTION "A simple currency exchange system [Um sistema simples de câmbio de moedas]"
#define SYSTEM_VERSION "1.0.0"

// System Files
// TODO: will be moved to the .env file later as i have decide not to hard code the directories.
#define LOG_FILE "../../LOG/unicambio.log"
#define CONFIG_FILE "../.env"
#define CURRENCY_FILE "../../DB/currencies.txt"
#define USER_FILE "../../DB/users.txt"
#define ROLE_FILE "../../DB/roles.txt"
#define RATE_FILE "../../DB/rates.txt"
#define TRANSACTION_FILE "../../DB/transactions.txt"

// Boolean
#define TRUE 1	// todo:remove later because i have decided to use Enum
#define FALSE 0 // todo: remove later because i have decided to use Enum

// Sleep time in seconds
#define MIN_SLEEP 2
#define MID_SLEEP 3
#define MAX_SLEEP 4

#define MAX_LOGIN_ATTEMPTS 5
#define MAX_NAME_LENGTH 150
#define MAX_PASSWORD_LENGTH 300
#define MAX_DATE_LENGTH 100
#define MAX_DESCRIPTION_LENGTH 500
#define ADMIN_USER "admin"
#define ADMIN_USER_DESCRIPTION "Administrator role with full access [Papel de administrador com acesso completo]"
// #define ADMIN_USER_EMAIL "odili.official@gmail.com"
// #define ADMIN_USER_PASSWORD "$argon2id$v=19$m=65536,t=2,p=1$vuRO48pVeLeXJdWK1wkfLg$w3rhLPRQ9nhkMDvAWw9d3ZaAuyv8SvNj8cjODTHiT2g" // Already hashed password for admin [Senha já hasheada para administrador]
// #define ADMIN_USER_PHONE "930725410"																																														// Default phone number for admin [Número de telefone padrão para administrador]

#define DATE_FORMAT "%d-%m-%Y"																								 // Date format: day-month-year [Formato de data: dia-mês-ano]
#define TIME_FORMAT "%H:%M:%S"																								 // Time format: hour:minute:second [Formato de hora: hora:minuto:segundo]
#define UI_ERROR_INVALID_TIME "Invalid time format [Formato de hora inválido]" // Error message for invalid time format [Mensagem de erro para formato de hora inválido]

#define DATE_TIME_FORMAT "%d-%m-%Y  |  %H:%M:%S" // Date and time format: day-month-year hour:minute:second [Formato de data e hora: dia-mês-ano hora:minuto:segundo]

#endif // CONFIG_H

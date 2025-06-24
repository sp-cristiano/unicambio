/**
 * @file unicambio.h
 * @author Chinedum Odili (https://github.com/sp-cristiano)
 * @brief This file contains configuration settings for the application.
 * [Este arquivo contém configurações para a aplicação.]
 * @version 0.1
 * @date 2025-06-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef CONFIG_H
#define CONFIG_H
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <stddef.h>
#include <sodium.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <strings.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <unistd.h>
#endif

// ====================================================================================================================================================================
// System Metadata [Metadados do sistema]
// ====================================================================================================================================================================
/**
 * @brief Name of the system [Nome do sistema]
 */
#define SYSTEM_NAME "Unicambio"

/**
 * @brief Default admin name [Nome de admin padrão]
 *
 */
#define DEFAULT_ADMIN_NAME "Default Admin [Administrador padrão]"


/**
 * @brief Default admin username [Nome de usuário de admin padrão]
 */
#define DEFAULT_ADMIN_USERNAME "unicambio"

/**
 * @brief System description [Descrição do sistema]
 */
#define SYSTEM_DESCRIPTION "A simple currency exchange system[Um sistema simples de câmbio de moedas]"

/**
 * @brief Version of the system [Versão do sistema]
 */
#define SYSTEM_VERSION "Version[Versãon] : 0.10"

/**
 * @brief Screen width [Largura da tela]
 */
#define SCREEN_WIDTH 100
#define MAX_LINE_CONTENT (SCREEN_WIDTH - 2)

/**
 * @brief Default Curency name [Nome de moeda padrão]
 */
#define DEFAULT_CURRENCY_NAME "United States Dollar [Dolar dos Estados Unidos]"
#define DEFAULT_CURRENCY_NAME_2 "Angolan Kwanza [Kwanza Angola]"

/**
 * @brief Default Curency abbreviation [Abreviação de moeda padrão]
 */
#define DEFAULT_CURRENCY_ABBREVIATION "US$"
#define FROM_CURRENCY_AMOUNT_USD 1.00
#define DEFAULT_CURRENCY_ABBREVIATION_2 "AOA"

#define safefree(ptr)                                       \
	if ((ptr) && (ptr)[0] != '\0' && strcmp((ptr), " ") != 0) \
	{                                                         \
		free((ptr));                                            \
		(ptr) = NULL;                                           \
	}

/**
 * @brief Default Curency code [Código de moeda padrão]
 */
#define DEFAULT_CURRENCY_CODE "USD"
#define DEFAULT_CURRENCY_CODE_2 "AOA"

/**
 * @brief Default Currency Symbol [Simbolo de moeda padrão]
 */
#define DEFAULT_CURRENCY_SYMBOL "$"
#define DEFAULT_CURRENCY_SYMBOL_2 "Kz"

/**
 * @brief Default currency rate [Taxa de câmbio padrão]
 *
 */
#define DEFAULT_AOA_TO_1_USD_CURRENCY_RATE 939.316
#define DEFAULT_AOA_TO_1_AOA_CURRENCY_RATE 1.00

#define MAX_CURRENCY_CODE_LENGTH 10

/**
 * @brief Default Currency Country
 */
#define DEFAULT_CURRENCY_COUNTRY "United States"
#define DEFAULT_CURRENCY_COUNTRY_2 "Angola"

// ====================================================================================================================================================================
// File Paths for Persistent Data Storage [Caminhos para armazenamento de dados persistentes]
// ====================================================================================================================================================================

/**
 * @brief Environmental variable file path [Caminho para o arquivo de variáveis de ambiente]
 *
 */
#define ENV_FILE_PATH ".env"
// #define ENV_FILE_PATH ".env"
/**
 * @brief Log file for system activities [Arquivo de log para atividades do sistema]
 */
#define LOG_FILE_PATH "logs/system.log"

/**
 * @brief File path to store and load user data. [Caminho para armazenar e carregar dados de usuário.]
 */
#define USER_DATA_FILE_PATH "DB/users.txt"

/**
 * @brief File path to store and load currency data. [Caminho para armazenar e carregar dados de moeda.]
 */
#define CURRENCY_DATA_FILE_PATH "DB/currencies.txt"

/**
 * @brief File path to store and load exchange rate data. [Caminho para armazenar e carregar dados de câmbio.]
 */
#define EXCHANGE_RATE_DATA_FILE_PATH "DB/exchangeRates.txt"

/**
 * @brief File path to store and load transaction data. [Caminho para armazenar e carregar dados de transação.]
 */
#define TRANSACTION_DATA_FILE_PATH "DB/transactions.txt"

// ====================================================================================================================================================================
// Sleep Durations (used for UX pacing or delay control) [Durações de pausa (usadas para controle de UX ou controle de delay)]
// ====================================================================================================================================================================
/**
 * @brief Minimum sleep duration in seconds. [Duração mínima de pausa em segundos.]
 */
#define MIN_SLEEP 2

/**
 * @brief Medfium sleep duration in seconds. [Duração média de pausa em segundos.]
 */
#define MID_SLEEP 3

/**
 * @brief Maximum sleep duration in seconds. [Duração máxima de pausa em segundos.]
 */
#define MAX_SLEEP 4

/**
 * @brief Maximum line length for console output. [Tamanho máximo de linha para saída de console.]
 *
 */
#define MAX_LINE_LENGTH 512

// ====================================================================================================================================================================
// Application Limits and Formatting [Limites e formatação da aplicação]
// ====================================================================================================================================================================

/**
 * @brief Maximum number of login attempts before lockout [Número máximo de tentativas de login antes de bloqueio]
 */
#define MAX_LOGIN_ATTEMPTS 5

/**
 * @brief Maximum length for names [Tamanho máximo para nomes]
 */
#define MAX_NAME_LENGTH 150

/**
 * @brief Maximum allowed length for passwords [Tamanho máximo permitido para senhas]
 */
#define MAX_PASSWORD_LENGTH 300
/**
 * @brief Maximum length of a date string [Tamanho máximo de uma data]
 */
#define MAX_DATE_LENGTH 100

/**
 * @brief Date format used across the system (DD-MM-YYYY) [Formato de data usado pelo sistema (DD-MM-YYYY)]
 */
#define DATE_FORMAT "%d-%m-%Y"
/**
 * @brief Time format used across the system (HH:MM:SS) [Formato de hora usado pelo sistema (HH:MM:SS)]
 */
#define TIME_FORMAT "%H:%M:%S"

/**
 * @brief Combined date-time format used across the system (DD-MM-YYYY HH:MM:SS) [Formato combinado de data-hora usado pelo sistema (DD-MM-YYYY HH:MM:SS)]
 */
#define DATE_TIME_FORMAT "%d-%m-%Y %H:%M:%S"

#endif // CONFIG_H
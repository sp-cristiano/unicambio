#ifndef UNICAMBIO_H
#define UNICAMBIO_H

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <stddef.h>
#include <ctype.h>
#include <errno.h>

// Platform detection
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define strcasecmp _stricmp
#else
#include <strings.h>
#include <unistd.h>
#endif

// Sodium for password hashing
#include <sodium.h>

// Constants
#define SYSTEM_NAME "Unicambio"
#define DEFAULT_ADMIN_NAME "Default Admin [Administrador padrão]"
#define DEFAULT_ADMIN_USERNAME "unicambio"
#define SYSTEM_VERSION "Version[Versão] : 0.10"

// UI Labels
#define UI_LABEL_TITLE "UNICAMBIO SYSTEM [SISTEMA UNICAMBIO]"
#define UI_LABEL_TITLE_DESCRIPTION1 "A complete solution for currency exchange and transaction management."
#define UI_LABEL_TITLE_DESCRIPTION2 "[Uma solução completa para troca de moedas e gestão de transações.]"
#define UI_LABEL_WELCOME "Welcome to UNICAMBIO [Bem-vindo ao UNICAMBIO]"
#define UI_ERROR_INVALID_DATE "Invalid Date [Data inválida]"

// Numeric Values
#define SCREEN_WIDTH 100
#define MIN_SLEEP 2
#define MID_SLEEP 3
#define MAX_SLEEP 4
#define MAX_LINE_LENGTH 512
#define MAX_LOGIN_ATTEMPTS 5
#define MAX_NAME_LENGTH 150
#define MAX_PASSWORD_LENGTH 300
#define MAX_DATE_LENGTH 100
#define DEFAULT_USD_RATE 939.317
#define DEFAULT_KZ_RATE 1.00

// Date formats
#define DATE_FORMAT "%d-%m-%Y"
#define TIME_FORMAT "%H:%M:%S"
#define DATE_TIME_FORMAT "%d-%m-%Y %H:%M:%S"
#define EMPTY_STRING " "

// File paths
#define ENV_FILE_PATH ".env"
#define LOG_FILE_PATH "logs/system.log"
#define USER_DATA_FILE_PATH "DB/users.txt"
#define CURRENCY_DATA_FILE_PATH "DB/currencies.txt"
#define EXCHANGE_RATE_DATA_FILE_PATH "DB/exchangeRates.txt"
#define TRANSACTION_DATA_FILE_PATH "DB/transactions.txt"

// Error Messages
#define UI_ERROR_RANDOM_NUMBER "Error generating random number. Minimum can not be greater than Maximum [Erro ao gerar número aleatório. O mínimo não pode ser maior que o máximo]"

#endif // UNICAMBIO_H
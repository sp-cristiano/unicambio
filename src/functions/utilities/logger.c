/**
 * @file logger.c
 * @author Chinedum Odili (https://github.com/sp-cristiano)
 * @brief This file contains the implementation of logging messages.
 * @version 0.1
 * @date 2025-06-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../include/unicambio.h"
#include "../include/messages.h"
#include "../include/logger.h"

/**
 * @brief Logs an error or event message to the log file.
 * If the log file does not exist, it attempts to create it.
 * If writing or closing fails, appropriate errors are shown on stderr.
 * [Logs um erro ou mensagem de evento no arquivo de log. Se o arquivo de log não existir, tenta criá-lo. Se a escrita ou fechamento falhar, são mostrados erros adequados no stderr.]
 *
 * @param message The message to be written to the log file. [Mensagem a ser escrita no arquivo de log.]
 */
void logMessages(LogLevel level, const char *message)
{
	time_t now = time(NULL);
	char *timeStr = ctime(&now);

	// Remove the trailing newline character [Remove o caractere de nova linha final]
	if (timeStr[strlen(timeStr) - 1] == '\n')
	{
		timeStr[strlen(timeStr) - 1] = '\0';
	}

	// convert LogLevele num to string
	const char *levelStr;
	switch (level)
	{
	case LOG_DEBUG:
		levelStr = "DEBUG";
		break;
	case LOG_INFO:
		levelStr = "INFO";
		break;
	case LOG_WARNING:
		levelStr = "WARNING";
		break;
	case LOG_ERROR:
		levelStr = "ERROR";
		break;
	default:
		levelStr = "UNKNOWN";
		break;
	}

	// Check if log file exist [Verifique se o arquivo de log existe]
	FILE *checkLogFile = fopen(LOG_FILE_PATH, "r");

	if (checkLogFile == NULL)
	{
		fprintf(stderr, "[%s]\tWARNING: %s\n", timeStr, UI_ERROR_LOG_FILE_NOT_FOUND);
		fprintf(stderr, "[%s]\tINIT - INFO: %s\n", timeStr, UI_CREATING_LOG_FILE);

		FILE *logFile = fopen(LOG_FILE_PATH, "w");

		if (logFile == NULL)
		{
			fprintf(stderr, "[%s]\tERROR: %s\n", timeStr, UI_ERROR_CREATING_LOG_FILE);
			sleep(MID_SLEEP);
			return;
		}

		// Writing header message to the new log file [Escrita da mensagem de cabeçalho para o novo arquivo de log]
		fprintf(logFile, "[%s]\tINFO: %s\n", timeStr, UI_LOG_FILE_MESSAGE);

		if (fclose(logFile) == EOF)
		{
			fprintf(stderr, "[%s]\tERROR: %s\n", timeStr, UI_ERROR_CLOSING_LOG_FILE);
			sleep(MID_SLEEP);
		}

		return;
	}
	else if (fclose(checkLogFile) == EOF)
	{
		fprintf(stderr, "[%s]\tERROR: %s\n", timeStr, UI_ERROR_CLOSING_LOG_FILE);
		sleep(MID_SLEEP);
	}

	// Append new message to log file
	FILE *logFile = fopen(LOG_FILE_PATH, "a");

	if (logFile == NULL)
	{
		fprintf(stderr, "[%s]\tERROR: %s\n", timeStr, UI_ERROR_APPENDING_TO_LOG_FILE);
		sleep(MID_SLEEP);
		return;
	}

	fprintf(logFile, "[%s]\t%s: %s\n", timeStr, levelStr, message);
	if (fclose(logFile) == EOF)
	{
		fprintf(stderr, "[%s]\tERROR: %s\n", timeStr, UI_ERROR_CLOSING_LOG_FILE);
		sleep(MID_SLEEP);
	}
}
#include "../include/unicambio.h"
#include "../include/utilities.h"
#include "../include/logger.h"

void logPrintMessage(LogLevel level,  char *message, yesOrNoInfo displayMessageInTerminal)
{
	time_t now = time(NULL);
	char *timeStr = ctime(&now);

	if (timeStr[strlen(timeStr) - 1] == '\n')
	{
		timeStr[strlen(timeStr) - 1] = '\0';
	}

	const char *levelStr;

	switch (level)
	{
	case LOG_ERROR:
		levelStr = "ERROR";
		break;
	case LOG_INFO:
		levelStr = "INFO";
		break;
	case LOG_DEBUG:
		levelStr = "DEBUG";
		break;
	case LOG_WARNING:
		levelStr = "WARNING";
		break;
	case LOG_SUCCESS:
		levelStr = "SUCCESS";
		break;
	default:
		levelStr = "NONE";
		break;
	}
	FILE *checkLogFile = fopen(LOG_FILE_PATH, "r");
	if (!checkLogFile)
	{
		centerStrings("WARNING: Log file not found [Arquivo de log nao encontrado]\n");
		centerStrings("INFO: Creating log file with name system.log [Criando arquivo de log com nome system.log]\n");
		sleep(MID_SLEEP);

		FILE *logFile = fopen(LOG_FILE_PATH, "w");
		if (!logFile)
		{
			centerStrings("ERROR: Failed to create log file [Falha ao criar arquivo de log]\n");
			sleep(MID_SLEEP);
			return;
		}
		fprintf(logFile, "[%s] \tSUCCESS: Log file created Successfully. [Arquivo de log criado com sucesso.]\n", timeStr);
		centerStrings("SUCCESS: Log file created Successfully. [Arquivo de log criado com sucesso.]");
		sleep(MID_SLEEP);

		if (fclose(logFile) == EOF)
		{
			centerStrings("ERROR: Failed to close log file [Falha ao fechar arquivo de log]\n");
			sleep(MID_SLEEP);
		}
		return;
	}
	else if (fclose(checkLogFile) == EOF)
	{
		centerStrings("ERROR: Failed to close log file [Falha ao fechar arquivo de log]\n");
		sleep(MID_SLEEP);
	}

	// Append new message to log file.
	FILE *logFile = fopen(LOG_FILE_PATH, "a");
	if (!logFile)
	{
		centerStrings("ERROR: Failed to append message to log file [Falha ao adicionar mensagem ao arquivo de log]\n");
		sleep(MID_SLEEP);
		return;
	}
	if (displayMessageInTerminal == yes)
	{
		fprintf(logFile, "[%s] \t%s %s\n", timeStr, levelStr, message);
		centerStrings(message);
		sleep(MID_SLEEP);
	}
	else if (displayMessageInTerminal == no)
	{
		fprintf(logFile, "[%s] \t%s %s\n", timeStr, levelStr, message);
	}
	if (fclose(logFile) == EOF)
	{
		centerStrings("ERROR: Failed to close log file [Falha ao fechar arquivo de log]\n");
		sleep(MID_SLEEP);
	}
}
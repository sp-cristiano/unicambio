/**
 * @file logger.h
 * @author Chinedum Odili (https://github.com/sp-cristiano)
 * @brief This file contains the header for logging messages. [Este arquivo contém o cabeçalho para os logs de mensagens.]
 * @param message The message to be logged [Mensagem a ser registrada]
 * @version 0.1
 * @date 2025-06-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef LOGGER_H
#define LOGGER_H
#include "../include/unicambio.h"
#include "../include/structures.h"
/**
 * @brief Logs a message
 *
 * @param message
 */
void logMessages(LogLevel level, const char *message);
#endif
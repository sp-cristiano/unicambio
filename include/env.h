/**
 * @file env.h
 * @author Chinedum Odili (https://github.com/sp-cristiano)
 * @brief Functions to handle environment variables
 * [Funções para lidar com variáveis de ambiente]
 * @version 0.1
 * @date 2025-06-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef ENV_H
#define ENV_H

#include "../include/structures.h"
/**
 * @brief Loads environment variables from a file [Carrega variáveis de ambiente de um arquivo]
 * This function allocates and initialize the AppContextInfo inside SystemData. It then reads key-Value pairs and stores them in the context.
 * [Esta função aloca e inicializa o AppContextInfo dentro de SystemData. Ela então lida com pares chave-valor e os armazena no contexto.]
 * @param sysData Pointer to the SystemData struct [Ponteiro para a estrutura SystemData]
 * @param filePath Path to the environment file [Caminho para o arquivo de ambiente]
 *@return StatusInfo Status of the operation [Status da operação]
 *
 */

StatusInfo loadEnvFile(SystemData *sysData, const char *filePath);
void freeAppContext(char *currentDate, char *currentTime, char *currentUserName, char *ADMIN_USER_PASSWORD, char *ADMIN_USER_EMAIL, char *ADMIN_USER_PHONE);
freeMemoryAllocatedToAppContextStructure(SystemData *sysData)

#endif // ENV_H
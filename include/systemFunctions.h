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
#ifndef SYSTEM_FUNCTIONS_H
#define SYSTEM_FUNCTIONS_H

#include "../include/structures.h"
/*
******************************************************************************************
[Protótipos de funções.]
******************************************************************************************
*/

void saveSystemData(SystemData *sysData); // Save system data to file [Salvar dados do sistema no arquivo]
void loadSystemData(SystemData *sysData); // Load system data from file [Carregar dados do sistema do arquivo]

#endif // SYSTEM_FUNCTIONS_H
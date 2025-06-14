/**
 * @file currencyFunctions.h
 * @author Chinedum Odili (https://github.com/sp-cristiano)
 * @brief
 * @param sysData Pointer to the system data structure containing user, role, currency, exchange rate, and transaction information.
 * [Apontador para a estrutura de dados do sistema contendo informações de usuário, papel, moeda, taxa de câmbio e transação.]
 * @version 1.0
 */

#ifndef CURRENCY_FUNCTIONS_H
#define CURRENCY_FUNCTIONS_H

/*
==================================================================================================================
																			File inclusion directives
																			[Diretivas de inclusão de arquivos]
==================================================================================================================
*/
#include "../include/structures.h"

/*
==================================================================================================================
																			Prototypes of functions
																			[Protótipos de funções]
==================================================================================================================
*/


// *** PROTOTYPES FOR CURRENCY FUNCTIONS [PROTÓTIPOS PARA FUNÇÕES DE MOEDA] ***

// Function to create a new currency [Função para criar uma nova moeda]
void createCurrency(SystemData *sysData,const char *name, const char code,  const char *abbreviation, const char *country, time_t created_at_date, time_t created_at_time, time_t updated_at_date, time_t updated_at_time, time_t deleted_at_date, time_t deleted_at_time);

// Function to save currency data to file [Função para salvar dados de moeda no arquivo]
void saveCurrencyData(SystemData *sysData);

// Function to load currency data from file [Função para carregar dados de moeda do arquivo]
void loadCurrencyData(SystemData *sysData);

// Function to display all currencies [Função para exibir todas as moedas]
void showCurrencies(SystemData *sysData);

// Function to update a currency [Função para atualizar uma moeda]
void updateCurrency(SystemData *sysData, int currency_id);

// Function to delete a currency [Função para excluir uma moeda]
void deleteCurrency(SystemData *sysData, int currency_id);

// Function to get currency by code, name or currency_id [Função para obter uma moeda pelo código, nome ou currency_id]
CurrencyInfo *getCurrency(SystemData *sysData, const char *code, const char *name, int currency_id);



#endif // CURRENCY_FUNCTIONS_H
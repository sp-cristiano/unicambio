/*
******************************************************************************
[Este arquivo contém todas as funções do sistema para o projeto unicambio.]
******************************************************************************
*/

/*
******************************************************************************
Including internal header files.
[Incluindo arquivos de cabeçalho internos.]
******************************************************************************
*/
#include "../include/config.h"
#include "../include/messages.h"
#include "../include/structures.h"
#include "../include/defaultUser.h"
#include "../include/defaultRole.h"
#include "../include/defaultCurrency.h"
#include "../include/defaultExchangeRate.h"
#include "../include/defaultTransaction.h"

/*
******************************************************************************
******************************************************************************
*/
void initDefaultSetup(SystemData *sysData)
{
	addUserDefaultProfile(sysData);							 // Add default user profile [Adicionar perfil de usuário padrão]
	addRoleDefaultProfile(sysData);							 // Add default role profile [Adicionar perfil de papel padrão]
	addCurrencyDefaultProfile(sysData);					 // Add default currency profile [Adicionar perfil de moeda padrão]
	addExchangeRateDefaultProfile(sysData);			 // Add default exchange rate profile [Adicionar perfil de taxa de câmbio padrão]
	addTransactionDefaultProfile(sysData);			 // Add default transaction profile [Adicionar perfil de transação padrão]
	printf("%s\n", UI_SUCCESSFUL_DEFAULT_SETUP); // Print success message for default setup [Imprimir mensagem de sucesso para configuração padrão]
	sleep(MID_SLEEP);
}

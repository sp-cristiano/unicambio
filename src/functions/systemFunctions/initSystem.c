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
#include "../include/initSystem.h"

/*
******************************************************************************
******************************************************************************
*/

/*
******************************************************************************
This function initializes the system data structure.
[Esta função inicializa a estrutura de dados do sistema.]
******************************************************************************
*/
void initSystem(SystemData *sysData)
{
	// Initialize user data
	sysData->users = NULL; // Pointer to the array of users in the system [Apontador para o array de usuários no sistema]
	sysData->userCapacity = 0;
	sysData->userCount = 0;
	sysData->userLimit = 0;

	// Initialize role data
	sysData->roles = NULL; // Pointer to the array of roles in the system [Apontador para o array de papéis no sistema]
	sysData->roleCapacity = 0;
	sysData->roleCount = 0;
	sysData->roleLimit = 0;

	// Initialize currency data
	sysData->currencies = NULL; // Pointer to the array of currencies in the system [Apontador para o array de moedas no sistema]
	sysData->currencyCapacity = 0;
	sysData->currencyCount = 0;
	sysData->currencyLimit = 0;

	// Initialize exchange rate data
	sysData->rates = NULL; // Pointer to the array of exchange rates in the system [Apontador para o array de taxas de câmbio no sistema]
	sysData->rateCapacity = 0;
	sysData->rateCount = 0;
	sysData->rateLimit = 0;

	// Initialize transaction data
	sysData->transactions = NULL; // Pointer to the array of transactions in the system [Apontador para o array de transações no sistema]
	sysData->transactionCapacity = 0;
	sysData->transactionCount = 0;
	sysData->transactionLimit = 0;

	printf("%s\n", UI_SUCCESSFUL_INIT);
}

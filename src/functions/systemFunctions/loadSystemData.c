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
#include "../include/unicambio.h"

/*
******************************************************************************
******************************************************************************
*/
void loadSystemData(SystemData *sysData)
{
	loadUserData(sysData);				 // Load user data from file [Carregar dados do usuário do arquivo]
	loadRoleData(sysData);				 // Load role data from file [Carregar dados do papel do arquivo]
	loadCurrencyData(sysData);		 // Load currency data from file [Carregar dados da moeda do arquivo]
	loadExchangeRateData(sysData); // Load exchange rate data from file [Carregar dados da taxa de câmbio do arquivo]
	loadTransactionData(sysData);	 // Load transaction data to file [Carregar dados da transação do arquivo]
	printf("\nAll system datas were loaded successfully from file. [Todos os dados do sistema foram salvos com sucesso.]\n");
	sleep(MID_SLEEP);
}

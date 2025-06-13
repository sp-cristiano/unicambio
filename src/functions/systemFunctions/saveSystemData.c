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
void saveSystemData(SystemData *sysData)
{
	saveUserData(sysData);				 // Save user data to file [Salvar dados do usuário no arquivo]
	saveRoleData(sysData);				 // Save role data to file [Salvar dados do papel no arquivo]
	saveCurrencyData(sysData);		 // Save currency data to file [Salvar dados da moeda no arquivo]
	saveExchangeRateData(sysData); // Save exchange rate data to file [Salvar dados da taxa de câmbio no arquivo]
	saveTransactionData(sysData);	 // Save transaction data to file [Salvar dados da transação no arquivo]
	printf("All system datas saved successfully [Todos os dados do sistema foram salvos com sucesso.]\n");
	sleep(MID_SLEEP);
}

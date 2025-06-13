/*
*******************************************************************************
This file contain the main function for the unicambio project.
[Este arquivo contém a função principal para o projeto unicambio.]
*******************************************************************************
*/

/*
*******************************************************************************
Including internal header files.
[Incluindo arquivos de cabeçalho internos.]
*******************************************************************************
*/
#include "unicambio.h"

int main()
{
	// Set the locale to the user's locale [Defina o local para o local do usuário]
	setLocation();

	// Initialize the system data structure [Inicializar a estrutura de dados do sistema]
	SystemData sysData;

	initSystem(&sysData);

	// initialize the system with default data [Inicializar o sistema com dados padrão]
	initDefaultSetup(&sysData);

	// TODO: Load system data from file [Carregar dados do sistema do arquivo]
	// loadSystemData(&sysData);

	// Clear the screen [Limpar a tela]
	startSessionMenu(&sysData);

	// TODO: Save system data to file [Salvar dados do sistema no arquivo]
	// saveSystemData(&sysData);

	// Free allocated memory [Liberar memória alocada]
	// freeSystemData(&sysData);

	return 0;
}
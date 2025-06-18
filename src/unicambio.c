// /**
//  * @file main.c
//  * @author Chinedum Odili (https://github.com/sp-cristiano)
//  * @brief This file contains the main function of the application.[Este arquivo contém a função principal da aplicação.
//  * @version 0.1
//  * @date 2025-06-05
//  * @copyright Copyright (c) 2025
//  */

// /**
//  * @brief Main function of the Unicâmbio currency exchange system.
//  *        [Função principal do sistema de câmbio Unicâmbio]
//  *
//  * Steps performed:
//  * 1. Initializes random seed for session randomness.
//  * 2. Allocates memory for the system's main data structure (`SystemData`).
//  * 3. Loads configuration values from `.env` into the application context.
//  * 4. Loads saved system data from file, if it exists.
//  * 5. Applies default setup if no data exists (e.g. admin user).
//  * 6. Starts the main session menu for user interaction.
//  * 7. Saves all system data to disk before exiting.
//  * 8. Frees all dynamically allocated memory.
//  *
//  * [Etapas realizadas:
//  * 1. Inicializa a semente aleatória para a sessão.
//  * 2. Aloca memória para a estrutura de dados principal do sistema (`SystemData`).
//  * 3. Carrega valores de configuração do arquivo `.env` para o contexto da aplicação.
//  * 4. Carrega os dados salvos do sistema do arquivo, se existirem.
//  * 5. Aplica a configuração padrão, se necessário (por exemplo, usuário admin).
//  * 6. Inicia o menu principal de sessão para interação com o usuário.
//  * 7. Salva todos os dados do sistema no disco antes de sair.
//  * 8. Libera toda a memória alocada dinamicamente.]
//  *
//  * @return int 0 on successful execution, 1 on memory allocation failure.
//  *             [0 em caso de execução bem-sucedida, 1 em falha de alocação de memória.]
//  */
#include "unicambio.h"
#include "structures.h"
#include "initSystem.h"
#include "messages.h"
#include "createDB.h"
#include "logger.h"
#include "env.h"
#include "utilities.h"
#include "oauth.h"
#include "homePageMenu.h"
int main()
{
	// Set the location of the application [Defina a localização da aplicação]
	setLocation();

	// Initialize the system [Inicie o sistema]
	SystemData sysData;

	// verify initialization [verifique a inicialização]
	// verifyInitSystem(&sysData);

	if (initSystem(&sysData) != successful)
	{
		logMessages(LOG_ERROR, UI_ERROR_MEMORY_ALLOCATION_FAILED);
		return failed;
	}
	else
	{
		logMessages(LOG_INFO, UI_INFO_SYSTEM_INITIALIZING);
		sleep(MID_SLEEP);
		logMessages(LOG_INFO, UI_SUCCESSFUL_INIT);
	}

	// Create database file for stroing system data [Crie um arquivo de banco de dados para armazenar dados do sistema]
	createDB(&sysData);

	loadEnvFile(&sysData, ENV_FILE_PATH);

	// initialize default setup [inicie a configuração padrão]
	initDefaultSetup(&sysData);

	// Load system data from file [Carregue dados do sistema do arquivo]
	loadSystemData(&sysData);

	// HOME PAGE
	homePageMenu(&sysData);

	// Save system data to file [Salve dados do sistema no arquivo]
	saveSystemData(&sysData);

	// Add default Setups [Adicione perfis padrões]
	// addDefaultSetups(&sysData);
	printf("%s\n", sysData.appContext->ADMIN_USER_EMAIL);
	printf("%s\n", sysData.appContext->ADMIN_USER_PASSWORD);
	printf("%s\n", sysData.appContext->ADMIN_USER_PHONE);

	return successful;
}

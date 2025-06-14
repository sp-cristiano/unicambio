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

#ifndef MESSAGES_H
#define MESSAGES_H

/*
*****************************************************************************************
Macro definitions for user interface messages.
[Definições de macros para mensagens da interface do usuário.]
*****************************************************************************************
*/

// *********** SUCCESSFUL MESSAGES ***********
#define UI_SUCCESSFUL_INIT "Initialization successful [Inicialização bem-sucedida]"
#define UI_SUCCESSFUL_ROLE_CREATED "Role created successfully [Papel criado com sucesso]"
#define UI_SUCCESSFUL_ROLE_DELETED "Role deleted successfully [Papel excluído com sucesso]"
#define UI_SUCCESSFUL_ROLE_UPDATED "Role updated successfully [Papel editado com sucesso]"
#define UI_SUCCESSFUL_ROLE_DATA_SAVED "Role data saved successfully. [Dados do papel salvos com sucesso.]"
#define UI_SUCCESSFUL_USER_CREATED "User created successfully [Usuário criado com sucesso]"
#define UI_SUCCESSFUL_USER_DELETED "User deleted successfully [Usuário excluído com sucesso]"
#define UI_SUCCESSFUL_USER_UPDATED "User updated successfully [Usuário editado com sucesso]"
#define UI_SUCCESSFUL_CURRENCY_CREATED "Currency created successfully [Moeda criada com sucesso]"
#define UI_SUCCESSFUL_CURRENCY_DELETED "Currency deleted successfully [Moeda excluída com sucesso]"
#define UI_SUCCESSFUL_CURRENCY_UPDATED "Currency updated successfully [Moeda editada com sucesso]"
#define UI_SUCCESSFUL_RATE_CREATED "Exchange rate created successfully [Taxa de câmbio criada com sucesso]"
#define UI_SUCCESSFUL_RATE_DELETED "Exchange rate deleted successfully [Taxa de câmbio excluída com sucesso]"
#define UI_SUCCESSFUL_RATE_UPDATED "Exchange rate updated successfully [Taxa de câmbio editada com sucesso]"
#define UI_SUCCESSFUL_TRANSACTION_CREATED "Transaction created successfully [Transação criada com sucesso]"
#define UI_SUCCESSFUL_TRANSACTION_DELETED "Transaction deleted successfully [Transação excluída com sucesso]"
#define UI_SUCCESSFUL_TRANSACTION_UPDATED "Transaction updated successfully [Transação editada com sucesso]"
#define UI_SUCCESSFUL_LOGIN "Login successful [Login bem-sucedido]"
#define UI_SUCCESSFUL_LOGOUT "Logout successful [Logout bem-sucedido]"
#define UI_SUCCESSFUL_DATA_LOADED "Data loaded successfully [Dados carregados com sucesso]"
#define UI_SUCCESSFUL_DATA_SAVED "Data saved successfully [Dados salvos com sucesso]"
#define UI_SUCCESSFUL_SESSION_STARTED "Session started successfully [Sessão iniciada com sucesso]"
#define UI_SUCCESSFUL_SESSION_ENDED "Session ended successfully [Sessão encerrada com sucesso]"
#define UI_SUCCESSFUL_DEFAULT_SETUP "Default setup completed successfully [Configuração padrão concluída com sucesso]"

//  *********** ERROR MESSAGES ***********
#define UI_ERROR_LOCALE "Error setting locale [Erro ao definir local]"
#define UI_ERROR_INIT_FAILED "Initialization failed [Inicialização falhou]"
#define UI_ERROR_ROLE_EXISTS "Role already exists [O papel já existe]"
#define UI_ERROR_ROLE_NOT_FOUND "Role not found [Papel não encontrado]"
#define UI_ERROR_USER_NOT_FOUND "User not found [Usuário não encontrado]"
#define UI_ERROR_ENV_FILE_NOT_FOUND "The file .env does not exist.[O arquivo .env não existe]"
#define UI_ERROR_ROLE_FILE_NOT_FOUND "The file roles.txt does not exist.[O arquivo roles.txt não existe.]"
#define UI_ERROR_USER_FILE_NOT_FOUND "The users.txt does not exist.[O arquivo users.txt não existe.]"
#define UI_ERROR_RATE_FILE_NOT_FOUND "The file rates.txt does not exist.[O arquivo rates.txt não existe.]"
#define UI_ERROR_CLOSING_ROLE_FILE "Error closing the file roles.txt.[Erro ao fechar o arquivo roles.txt.]"
#define UI_ERROR_CLOSING_USER_FILE "Error closing the file users.txt.[Erro ao fechar o arquivo users.txt.]"
#define UI_ERROR_CLOSING_RATE_FILE "Error closing the file rates.txt.[Erro ao fechar o arquivo rates.txt.]"
#define UI_ERROR_CLOSING_TRANSACTION_FILE "Error closing the file transactions.txt.[Erro ao fechar o arquivo transactions.txt.]"
#define UI_ERROR_NO_ROLES_FOUND "No roles found [Nenhum papel encontrado]"	
#define UI_ERROR_CLOSING_CURRENCY_FILE "Error closing the file currencies.txt.[Erro ao fechar o arquivo currencies.txt.]"

#define UI_ERROR_TRANSACTION_FILE_NOT_FOUND "The file transactions.txt does not exist.[O arquivo transactions.txt não existe.]"
#define UI_ERROR_USER_EXISTS "User already exists [Usuário já existe]"
#define UI_ERROR_CURRENCY_NOT_FOUND "Currency not found [Moeda não encontrada]"
#define UI_ERROR_CURRENCY_EXISTS "Currency already exists [Moeda já existe]"
#define UI_ERROR_RATE_NOT_FOUND "Exchange rate not found [Taxa de câmbio não encontrada]"
#define UI_ERROR_RATE_EXISTS "Exchange rate already exists [Taxa de câmbio já existe]"
#define UI_ERROR_TRANSACTION_NOT_FOUND "Transaction not found [Transação não encontrada]"
#define UI_ERROR_TRANSACTION_EXISTS "Transaction already exists [Transação já existe]"
#define UI_ERROR_INVALID_INPUT "Invalid input, please try again [Entrada inválida, por favor tente novamente]"
#define UI_ERROR_FILE_NOT_FOUND "File not found [Arquivo não encontrado]"
#define UI_ERROR_FILE_READ "Error reading file [Erro ao ler o arquivo]"
#define UI_ERROR_FILE_WRITE "Error writing to file [Erro ao escrever no arquivo]"
#define UI_ERROR_DATA_NOT_FOUND "System Data not found [Os dados do sistema não foram encontrados]"
#define UI_ERROR_MEMORY_ALLOCATION "Memory allocation error [Erro de alocação de memória]"
#define UI_ERROR_INVALID_CURRENCY "Invalid currency [Moeda inválida]"
#define UI_ERROR_INVALID_RATE "Invalid exchange rate [Taxa de câmbio inválida]"
#define UI_ERROR_CURRENCY_ADD "Error adding currency [Erro ao adicionar moeda]"
#define UI_ERROR_CURRENCY_REMOVE "Error removing currency [Erro ao remover moeda]"
#define UI_ERROR_RATE_UPDATE "Error updating exchange rate [Erro ao atualizar a taxa de câmbio]"
#define UI_ERROR_RATE_VIEW "Error viewing exchange rates [Erro ao visualizar as taxas de câmbio]"
#define UI_ERROR_CURRENCY_VIEW "Error viewing available currencies [Erro ao visualizar as moedas disponíveis]"
#define UI_ERROR_NO_USERS "No users found in the system [Nenhum usuário encontrado no sistema]"
#define UI_ERROR_HASHING_PASSWORD "Error hashing password [Erro ao hashear a senha]"
#define UI_ERROR_INVALID_ROLE "Invalid role [Papel inválido]"
#define UI_ERROR_INVALID_PASSWORD "Invalid password [Senha inválida]"
#define UI_ERROR_INVALID_USERNAME "Invalid username [Nome de usuário inválido]"
#define UI_ERROR_INVALID_CREDENTIALS "Invalid username and password [Nome de usuário e senha inválidos]"
#define UI_ERROR_LOGIN_FAILED "Login failed [Falha no login]"
#define UI_ERROR_SESSION_NOT_STARTED "Session not started [Sessão não iniciada]"
#define UI_ERROR_SESSION_ALREADY_STARTED "Session already started [Sessão já iniciada]"
#define UI_ERROR_SESSION_NOT_ENDED "Session not ended [Sessão não encerrada]"
#define UI_ERROR_SESSION_ALREADY_ENDED "Session already ended [Sessão já encerrada]"
#define UI_ERROR_DEFAULT_SETUP_FAILED "Default setup failed [Configuração padrão falhou]"
#define UI_ERROR_UNAUTHORIZED_ACCESS "Unauthorized access [Acesso não autorizado]"
#define UI_ERROR_UNEXPECTED "An unexpected error occurred [Ocorreu um erro inesperado]"
#define UI_ERROR_OPERATION_CANCELLED "Operation cancelled [Operação cancelada]"
#define UI_ERROR_RANDOM_NUMBER "Error generating random number. Minimum can not be greater than Maximum [Erro ao gerar número aleatório. O mínimo não pode ser maior que o máximo]"
#define UI_ERROR_CREATING_ROLE_FILE "Error creating the file roles.txt. [Erro ao criar o arquivo roles.txt.]"
#define UI_ERROR_CREATING_USER_FILE "Error creating the file users.txt. [Erro ao criar o arquivo users.txt.]"
#define UI_ERROR_CREATING_RATE_FILE "Error creating the file rates.txt. [Erro ao criar o arquivo rates.txt.]"
#define UI_ERROR_CREATING_TRANSACTION_FILE "Error creating the file transactions.txt. [Erro ao criar o arquivo transactions.txt.]"

// *********** CONFIRMATION MESSAGES ***********
#define UI_CONFIRM_EXIT "Are you sure you want to exit? [Você tem certeza de que deseja sair?] (y/n): "
#define UI_CONFIRM_TERMINATE_SESSION "Are you sure you want to terminate the session? [Você tem certeza de que deseja encerrar a sessão?] (y/n): "
#define UI_CONFIRM_ADD_CURRENCY "Are you sure you want to add this currency? [Você tem certeza de que deseja adicionar esta moeda?] (y/n): "
#define UI_CONFIRM_REMOVE_CURRENCY "Are you sure you want to remove this currency? [Você tem certeza de que deseja remover esta moeda?] (y/n): "
#define UI_CONFIRM_UPDATE_RATE "Are you sure you want to update this exchange rate? [Você tem certeza de que deseja atualizar esta taxa de câmbio?] (y/n): "

//  ************ USER INTERFACE MESSAGES ***********
#define UI_TITLE "UNICAMBIO SYSTEM [SISTEMA UNICAMBIO]"
#define UI_TITLE_DESCRIPTION1 "A complete solution for currency exchange and transaction management."
#define UI_TITLE_DESCRIPTION2 "[Uma solução completa para troca de moedas e gestão de transações.]"
#define UI_EXIT "Exiting the system [Saindo do sistema]"
#define UI_WELCOME "Welcome to UNICAMBIO [Bem-vindo ao UNICAMBIO]"
#define UI_MAIN_MENU "MAIN MENU [MENU PRINCIPAL]"
#define UI_LOGIN "LOGIN PAGE [PÁGINA DE LOGIN]"
#define UI_LOGOUT "0. Logout [Sair]"
#define UI_ADMIN_MENU "ADMIN MENU [MENU DO ADMINISTRADOR]"
#define UI_USER_MENU "USER MENU [MENU DO USUÁRIO]"
#define UI_USERNAME "Username [Nome de usuário]: "
#define UI_PASSWORD "Password [Senha]: "
#define UI_EXIT_MESSAGE "Thank you for using UNICAMBIO [Obrigado por usar o UNICAMBIO]"
#define UI_PROMPT "Please select an option [Por favor, selecione uma opção]: "
#define UI_CURRENCY_LIST "CURRENCY LIST [LISTA DE MOEDAS]"
#define UI_VIEW_AVAILABLE_CURRENCIES "AVAILABLE CURRENCIES" ["MOEDAS DISPONÍVEIS]"
#define UI_VIEW_EXCHANGE_RATES "EXCHANGE RATES [TAXAS DE CÂMBIO]"
#define UI_VIEW_TRANSACTIONS "TRANSACTIONS [TRANSAÇÕES]"
#define UI_CREATING_ROLE_FILE "Creating the file with name roles.txt.[Criando o arquivo com o nome roles.txt.]"
#define UI_CREATING_USER_FILE "Creating the file with name users.txt.[Criando o arquivo com o nome users.txt.]"
#define UI_CREATING_RATE_FILE "Creating the file with name rates.txt.[Criando o arquivo com o nome rates.txt.]"
#define UI_CREATING_TRANSACTION_FILE "Creating the file with name transactions.txt.[Criando o arquivo com o nome transactions.txt.]"
#define UI_START_SESSION_MENU_OPT_1 "Type 1 to start a session or 0 to exit.\n\t      [Digite 1 para iniciar uma sessão ou 0 para sair]"
#define UI_ADMIN_MENU_OPT_1 "1. Manage Users [Gerenciar Usuários]"
#define UI_ADMIN_MENU_OPT_2 "2. Manage Roles [Gerenciar Papéis]"
#define UI_ADMIN_MENU_OPT_3 "3. Manage Currencies [Gerenciar Moedas]"
#define UI_ADMIN_MENU_OPT_4 "4. Manage Exchange Rates [Gerenciar Taxas de Câmbio]"
#define UI_ADMIN_MENU_OPT_5 "5. Manage Transactions [Gerenciar Transações]"
#endif // MESSAGES_H
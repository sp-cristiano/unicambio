/**
 * @file messages.h
 * @author Chinedum Odili (https://github.com/sp-cristiano)
 * @brief Defines user interface messages for the application.
 * This file contains macros for all types of system messages including:
 * - Success messages
 * - Error messages
 * - Confirmation prompts
 * - Warning messages
 * - User interface labels and texts
 * [Define mensagens de interface do usuário para a aplicação.]
 * [Este arquivo contém macros para todas as mensagens de interface do sistema incluindo:
 * - Mensagens de sucesso
 * - Mensagens de erro
 * - Prompts de confirmação
 * - Mensagens de aviso
 * - Rótulos e textos da interface do usuário]
 *
 * @version 0.1
 * @date 2025-06-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef MESSAGES_H
#define MESSAGES_H
#include "../include/unicambio.h"

// ====================================================================================================================================================================
// SUCCESS MESSAGES [MENSAGENS DE SUCESSO]
// ====================================================================================================================================================================

/// Initialization Message [Mensagem de inicialização]
#define UI_SUCCESSFUL_INIT "Initialization Successful [Iniciação bem-sucedida]"

/// User Operations [Operações de usuário]
#define UI_SUCCESSFUL_USER_CREATED "User Created Successfully [Usuário criado com sucesso]"
#define UI_SUCCESSFUL_USER_UPDATED "User Updated Successfully [Usuário atualizado com sucesso]"
#define UI_SUCCESSFUL_USER_DELETED "User Deleted Successfully [Usuário excluído com sucesso]"

/// Currency Operations [Operações de moeda]
#define UI_SUCCESSFUL_CURRENCY_CREATED "Currency Created Successfully [Moeda criada com sucesso]"
#define UI_SUCCESSFUL_CURRENCY_UPDATED "Currency Updated Successfully [Moeda atualizada com sucesso]"
#define UI_SUCCESSFUL_CURRENCY_DELETED "Currency Deleted Successfully [Moeda excluída com sucesso]"

/// Exchange rate Operations [Operações de câmbio]
#define UI_SUCCESSFUL_EXCHANGE_RATE_CREATED "Exchange Rate Created Successfully [Câmbio criado com sucesso]"
#define UI_SUCCESSFUL_EXCHANGE_RATE_UPDATED "Exchange Rate Updated Successfully [Câmbio atualizado com sucesso]"
#define UI_SUCCESSFUL_EXCHANGE_RATE_DELETED "Exchange Rate Deleted Successfully [Câmbio excluído com sucesso]"

/// Transaction Operations [Operações de transação]
#define UI_SUCCESSFUL_TRANSACTION_CREATED "Transaction Created Successfully [Transação criada com sucesso]"
#define UI_SUCCESSFUL_TRANSACTION_DELETED "Transaction Deleted Successfully [Transação excluída com sucesso]"

/// Session and authentication [Sessão e autenticação]
#define UI_SUCCESSFUL_LOGIN "Login Successful [Login bem-sucedido]"
#define UI_SUCCESSFUL_LOGOUT "Logout Successful [Logout bem-sucedido]"
#define UI_SUCCESSFUL_SESSION_STARTED "Session Started Successfully [Sessão iniciada com sucesso]"
#define UI_SUCCESSFUL_SESSION_ENDED "Session Ended Successfully [Sessão encerrada com sucesso]"
#define UI_SUCCESSFUL_DATA_LOADED "Data Loaded Successfully [Dados carregados com sucesso]"
#define UI_SUCCESSFUL_DATA_SAVED "Data Saved Successfully [Dados salvos com sucesso]"
#define UI_SUCCESSFUL_DEFAULT_SETUP "Default Setup Completed Successfully [Configuração padrão concluída com sucesso]"

/// File operations [Operações de arquivo]
#define UI_SUCCESSFUL_FILE_CREATED "File Created Successfully [Arquivo criado com sucesso]"
#define UI_SUCCESSFUL_FILE_UPDATED "File Updated Successfully [Arquivo atualizado com sucesso]"
#define UI_SUCCESSFUL_FILE_DELETED "File Deleted Successfully [Arquivo excluído com sucesso]"
#define UI_CREATING_USER_FILE "Creating the file with name users.txt.[Criando o arquivo com o nome users.txt.]"
#define UI_CREATING_CURRENCY_FILE "Creating the file with name currencies.txt.[Criando o arquivo com o nome currencies.txt.]"
#define UI_CREATING_EXCHANGE_RATE_FILE "Creating the file with name exchange_rates.txt.[Criando o arquivo com o nome rates.txt.]"
#define UI_CREATING_TRANSACTION_FILE "Creating the file with name transactions.txt.[Criando o arquivo com o nome transactions.txt.]"
#define UI_CREATING_LOG_FILE "Creating the log file.[Criando o arquivo de log.]"
#define UI_LOG_FILE_MESSAGE "Log File Created Successfully [Arquivo de log criado com sucesso]"

#define UI_SUCCESSFUL_FREEING_MEMORY "Memory Freed Successfully [Memória liberada com sucesso]"

// ====================================================================================================================================================================
// ERROR MESSAGES [MENSAGENS DE ERRO]
// ====================================================================================================================================================================

/// Locale and Initializationn [Idioma e inicialização]
#define UI_ERROR_LOCALE "Locale Not Supported [Idioma não suportado]"
#define UI_ERROR_INIT "Initialization Failed [Iniciação falhou]"
#define UI_ERROR_STRING_IS_NULL "String is Null [A string é nula]"

/// File-related errors [Erros relacionados a arquivos]
#define UI_ERROR_MAX_LOGIN_ATTEMPTS_REACHED "Maximum Login Attempts Reached [Limite de tentativas de login atingido]"
#define UI_ERROR_ENV_FILE_NOT_FOUND "Environment File Not Found [Arquivo de ambiente não encontrado]"
#define UI_ERROR_USER_DATA_FILE_NOT_FOUND "User Data File Not Found [Arquivo de dados de usuário não encontrado]"
#define UI_ERROR_CURRENCY_DATA_FILE_NOT_FOUND "Currency Data File Not Found [Arquivo de dados de moeda não encontrado]"
#define UI_ERROR_EXCHANGE_RATE_DATA_FILE_NOT_FOUND "Exchange Rate Data File Not Found [Arquivo de dados de câmbio não encontrado]"
#define UI_ERROR_TRANSACTION_DATA_FILE_NOT_FOUND "Transaction Data File Not Found [Arquivo de dados de transação não encontrado]"
#define UI_ERROR_CLOSING_USER_DATA_FILE "Error Closing User Data File [Erro ao fechar arquivo de dados de usuário]"
#define UI_ERROR_CLOSING_CURRENCY_DATA_FILE "Error Closing Currency Data File [Erro ao fechar arquivo de dados de moeda]"
#define UI_ERROR_CLOSING_EXCHANGE_RATE_DATA_FILE "Error Closing Exchange Rate Data File [Erro ao fechar arquivo de dados de câmbio]"
#define UI_ERROR_CLOSING_TRANSACTION_DATA_FILE "Error Closing Transaction Data File [Erro ao fechar arquivo de dados de transação]"
#define UI_ERROR_CREATING_USER_DATA_FILE "Error Creating User Data File [Erro ao criar arquivo de dados de usuário]"
#define UI_ERROR_CREATING_CURRENCY_DATA_FILE "Error Creating Currency Data File [Erro ao criar arquivo de dados de moeda]"
#define UI_ERROR_CREATING_EXCHANGE_RATE_DATA_FILE "Error Creating Exchange Rate Data File [Erro ao criar arquivo de dados de câmbio]"
#define UI_ERROR_CREATING_TRANSACTION_DATA_FILE "Error Creating Transaction Data File [Erro ao criar arquivo de dados de transação]"
#define UI_ERROR_READING_USER_DATA_FILE "Error Reading User Data File [Erro ao ler arquivo de dados de usuário]"
#define UI_ERROR_READING_CURRENCY_DATA_FILE "Error Reading Currency Data File [Erro ao ler arquivo de dados de moeda]"
#define UI_ERROR_READING_EXCHANGE_RATE_DATA_FILE "Error Reading Exchange Rate Data File [Erro ao ler arquivo de dados de câmbio]"
#define UI_ERROR_READING_TRANSACTION_DATA_FILE "Error Reading Transaction Data File [Erro ao ler arquivo de dados de transação]"
#define UI_ERROR_WRITING_USER_DATA_FILE "Error Writing User Data File [Erro ao escrever arquivo de dados de usuário]"
#define UI_ERROR_WRITING_CURRENCY_DATA_FILE "Error Writing Currency Data File [Erro ao escrever arquivo de dados de moeda]"
#define UI_ERROR_WRITING_EXCHANGE_RATE_DATA_FILE "Error Writing Exchange Rate Data File [Erro ao escrever arquivo de dados de câmbio]"
#define UI_ERROR_WRITING_TRANSACTION_DATA_FILE "Error Writing Transaction Data File [Erro ao escrever arquivo de dados de transação]"
#define UI_ERROR_READING_LOG_FILE "Error Reading Log File [Erro ao ler arquivo de log]"
#define UI_ERROR_WRITING_LOG_FILE "Error Writing Log File [Erro ao escrever arquivo de log]"
#define UI_ERROR_CLOSING_LOG_FILE "Error Closing Log File [Erro ao fechar arquivo de log]"
#define UI_ERROR_CREATING_LOG_FILE "Error Creating Log File [Erro ao criar arquivo de log]"
#define UI_ERROR_LOG_FILE_NOT_FOUND "Log File Not Found [Arquivo de log não encontrado]"
#define UI_ERROR_APPENDING_TO_LOG_FILE "Error Appending to Log File [Erro ao adicionar ao arquivo de log]"
#define UI_ERROR_CREATING_FILE_DB "Error Creating File Database [Erro ao criar banco de dados de arquivos]"

/// Validation and logic [Validação e lógica]
#define UI_ERROR_INVALID_INPUT "Invalid Input [Entrada inválida]"
#define UI_ERROR_INVALID_CURRENCY_CODE "Invalid Currency Code [Código de moeda inválido]"
#define UI_ERROR_INVALID_TRANSACTION_ID "Invalid Transaction ID [ID de transação inválido]"
#define UI_ERROR_INVALID_USER_ID "Invalid User ID [ID de usuário inválido]"
#define UI_ERROR_INVALID_AMOUNT "Invalid Amount [Quantidade inválida]"
#define UI_ERROR_INVALID_EXCHANGE_RATE "Invalid Exchange Rate [Câmbio inválido]"
#define UI_ERROR_INVALID_TRANSACTION_STATUS "Invalid Transaction Status [Status de transação inválido]"
#define UI_ERROR_INVALID_CURRENCY_STATUS "Invalid Currency Status [Status de moeda inválido]"
#define UI_ERROR_INVALID_EXCHANGE_RATE_STATUS "Invalid Exchange Rate Status [Status de câmbio inválido]"
#define UI_ERROR_INVALID_DATE "Invalid Date [Data inválida]"
#define UI_ERROR_MEMORY_ALLOCATION_FAILED "Memory Allocation Failed [Alocação de memória falhou]"
#define UI_ERROR_USER_MEMORY_ALLOCATION_FAILED "Failed to Allocate Memory for User [Falha ao alocar memória para usuário]"
#define UI_ERROR_CURRENCY_MEMORY_ALLOCATION_FAILED "Failed to Allocate Memory for Currency [Falha ao alocar memória para moeda]"
#define UI_ERROR_EXCHANGE_RATE_MEMORY_ALLOCATION_FAILED "Failed to Allocate Memory for Exchange Rate [Falha ao alocar memória para câmbio]"
#define UI_ERROR_TRANSACTION_MEMORY_ALLOCATION_FAILED "Failed to Allocate Memory for Transaction [Falha ao alocar memória para transação]"
#define UI_ERROR_INVALID_PASSWORD "Invalid Password [Senha inválida]"
#define UI_ERROR_INVALID_USERNAME "Invalid Username [Nome de usuário inválido]"
#define UI_ERROR_INVALID_CREDENTIALS "Invalid Credentials [Credenciais inválidas]"

/// Data existence [Existência de dados]
#define UI_ERROR_USER_NOT_FOUND "User Not Found [Usuário não encontrado]"
#define UI_ERROR_CURRENCY_NOT_FOUND "Currency Not Found [Moeda não encontrada]"
#define UI_ERROR_EXCHANGE_RATE_NOT_FOUND "Exchange Rate Not Found [Câmbio não encontrado]"
#define UI_ERROR_TRANSACTION_NOT_FOUND "Transaction Not Found [Transação não encontrada]"
#define UI_ERROR_USER_EXISTS "User Already Exists [Usuário já existe]"
#define UI_ERROR_CURRENCY_EXISTS "Currency Already Exists [Moeda já existe]"
#define UI_ERROR_EXCHANGE_RATE_EXISTS "Exchange Rate Already Exists [Câmbio já existe]"
#define UI_ERROR_TRANSACTION_EXISTS "Transaction Already Exists [Transação já existe]"

/// Session [Sessão]
#define UI_ERROR_LOGIN_FAILED "Login Failed [Login falhou]"
#define UI_ERROR_LOGOUT_FAILED "Logout Failed [Logout falhou]"
#define UI_ERROR_SESSION_NOT_STARTED "Session Not Started [Sessão não iniciada]"
#define UI_ERROR_SESSION_ALREADY_STARTED "Session Already Started [Sessão já iniciada]"
#define UI_ERROR_SESSION_ALREADY_ENDED "Session Already Ended [Sessão já encerrada]"
#define UI_ERROR_SESSION_NOT_ENDED "Session Not Ended [Sessão não encerrada]"
#define UI_ERROR_DEFAULT_SETUP_FAILED "Default Setup Failed [Configuração padrão falhou]"
#define UI_ERROR_DEFAULT_SETUP_ALREADY_COMPLETED "Default Setup Already Completed [Configuração padrão já concluída]"

/// Operations [Operações]
#define UI_ERROR_CURRENCY_CREATION_FAILED "Currency Creation Failed [Criação de moeda falhou]"
#define UI_ERROR_EXCHANGE_RATE_CREATION_FAILED "Exchange Rate Creation Failed [Criação de câmbio falhou]"
#define UI_ERROR_TRANSACTION_CREATION_FAILED "Transaction Creation Failed [Criação de transação falhou]"
#define UI_ERROR_USER_CREATION_FAILED "User Creation Failed [Criação de usuário falhou]"
#define UI_ERROR_CURRENCY_UPDATE_FAILED "Currency Update Failed [Atualização de moeda falhou]"
#define UI_ERROR_EXCHANGE_RATE_UPDATE_FAILED "Exchange Rate Update Failed [Atualização de câmbio falhou]"
#define UI_ERROR_TRANSACTION_UPDATE_FAILED "Transaction Update Failed [Atualização de transação falhou]"
#define UI_ERROR_USER_UPDATE_FAILED "User Update Failed [Atualização de usuário falhou]"
#define UI_ERROR_CURRENCY_DELETION_FAILED "Currency Deletion Failed [Exclusão de moeda falhou]"
#define UI_ERROR_EXCHANGE_RATE_DELETION_FAILED "Exchange Rate Deletion Failed [Exclusão de câmbio falhou]"
#define UI_ERROR_TRANSACTION_DELETION_FAILED "Transaction Deletion Failed [Exclusão de transação falhou]"
#define UI_ERROR_USER_DELETION_FAILED "User Deletion Failed [Exclusão de usuário falhou]"
#define UI_ERROR_DISPLAY_USER_DATA_FAILED "Display User Data Failed [Exibição de dados de usuário falhou]"
#define UI_ERROR_DISPLAY_CURRENCY_DATA_FAILED "Display Currency Data Failed [Exibição de dados de moeda falhou]"
#define UI_ERROR_DISPLAY_EXCHANGE_RATE_DATA_FAILED "Display Exchange Rate Data Failed [Exibição de dados de câmbio falhou]"
#define UI_ERROR_DISPLAY_TRANSACTION_DATA_FAILED "Display Transaction Data Failed [Exibição de dados de transação falhou]"
#define UI_ERROR_USER_LIMIT_REACHED "User Limit Reached [Limite de usuário alcancado]"

/// Permissions [Permissões]
#define UI_ERROR_USER_NO_PERMISSIONS "User Has No Permissions to perform this operation [Usuário não tem permissões para executar essa operação]"
#define UI_ERROR_GETTING_CURRENT_DATE_TIME "Error getting current date time [Erro ao obter data e hora atual]"
/// Misc [Miscelânea]
#define UI_ERROR_HASHING_PASSWORD "Error hashing password [Erro ao hashear a senha]"
#define UI_ERROR_UNAUTHORIZED_ACCESS "Unauthorized access [Acesso não autorizado]"
#define UI_ERROR_OPERATION_CANCELLED "Operation cancelled [Operação cancelada]"
#define UI_ERROR_RANDOM_NUMBER "Error generating random number. Minimum can not be greater than Maximum [Erro ao gerar número aleatório. O mínimo não pode ser maior que o máximo]"
#define UI_ERROR_UNEXPECTED "An unexpected error occurred [Ocorreu um erro inesperado]"
#define UI_USER_NOT_ACTIVE "User is not active [Usuário não ativo]"
#define UI_REDIRECT_TO_LIMITED_ACCESS "Redirecting to Limited Access [Redirecionando para Acesso Limitado]"

/// System Data [Dados do Sistema]
#define UI_ERROR_SYSTEM_DATA_IS_NULL "System Data is Null [Dados do Sistema é nulo]"
#define UI_INFO_SYSTEM_INITIALIZING "System is initializing [O Sistema está sendo iniciado]"
#define UI_ERROR_SYSTEM_DATA_OR_APP_CONTEXT_IS_NULL "System Data or Application Context is Null [Dados do Sistema ou Contexto da Aplicação é nulo]"
#define UI_ERROR_APP_CONTEXT_IS_NULL "Application Context is Null [Contexto da Aplicação é nulo]"
#define UI_ERROR_CURRENCY_DATA_IS_NULL "Currency Data is Null [Dados de Moeda é nulo]"
#define UI_ERROR_EXCHANGE_RATE_DATA_IS_NULL "Exchange Rate Data is Null [Dados de Caâmbio é nulo]"
#define UI_ERROR_USER_DATA_FILE_READ_ERROR "User Data File Read Error [Erro ao ler o arquivo de dados de usuários]"
#define UI_ERROR_USER_DATA_FILE_FORMAT_ERROR "User Data File Format Error [Erro no formato do arquivo de dados de usuários]"
#define UI_ERROR_CURRENCY_DATA_FILE_FORMAT_ERROR "Currency Data File Format Error [Erro no formato do arquivo de dados de moeda]"
#define UI_ERROR_EXCHANGE_RATE_DATA_FILE_FORMAT_ERROR "Exchange Rate Data File Format Error [Erro no formato do arquivo de dados de caâmbio]"
#define UI_ERROR_TRANSACTION_DATA_FILE_FORMAT_ERROR "Transaction Data File Format Error [Erro no formato do arquivo de dados de transação]"

#define UI_ERROR_CURRENCY_DATA_STATUS_NOT_ACTIVE "Currency Data Status Not Active [Status de Dados de Moeda Não Ativo]"
#define UI_ERROR_EXCHANGE_RATE_DATA_STATUS_NOT_ACTIVE "Exchange Rate Data Status Not Active [Status de Dados de Caâmbio Não Ativo]"
#define UI_ERROR_TRANSACTION_DATA_STATUS_NOT_ACTIVE "Transaction Data Status Not Active [Status de Dados de Transação Não Ativo]"
#define UI_ERROR_USER_DATA_STATUS_NOT_ACTIVE "User Data Status Not Active [Status de Dados de Usuário Não Ativo]"

#define UI_ERROR_USER_DATA_IS_EMPTY "User Data File is Empty [Arquivo de Dados de Usuário é vazio]"
#define UI_ERROR_CURRENCY_DATA_IS_EMPTY "Currency Data File is Empty [Arquivo de Dados de Moeda é vazio]"
#define UI_ERROR_EXCHANGE_RATE_DATA_IS_EMPTY "Exchange Rate Data File is Empty [Arquivo de Dados de Caâmbio é vazio]"
#define UI_ERROR_TRANSACTION_DATA_IS_EMPTY "Transaction Data File is Empty [Arquivo de Dados de Transação é vazio]"
#define UI_ERROR_ADMIN_USER_DATA_NOT_FOUND "Admin User Data Not Found [Dados de Usuário Administrador Não Encontrado]"
#define UI_ERROR_ADMIN_USER_NAME_NOT_FOUND "Admin User Name Not Found [Nome de Usuário Administrador Não Encontrado]"

#define UI_ERROR_SYSTEM_DATA_OR_USERS_IS_NULL "System Data or Users is Null [Dados do Sistema ou Usuários é nulo]"
#define UI_ERROR_USER_CAPACITY_REACHED "User Capacity Reached [Capacidade de Usuário Alcancada]"
#define UI_ERROR_TRANSACTION_DATA_IS_NULL "Transaction Data is Null [Dados de Transação é nulo]"
#define UI_ERROR_ADMIN_USER_USERNAME_NOT_FOUND "Admin User Username Not Found [Nome de Usuário Administrador Não Encontrado]"
#define UI_ERROR_ADMIN_USER_EMAIL_NOT_FOUND "Admin User Email Not Found [E-mail de Usuário Administrador Não Encontrado]"
/// User Data [Dados de Usuário]
#define UI_ERROR_USER_DATA_IS_NULL "User Data is Null [Dados de Usuário é nulo]"
#define UI_ERROR_ADMIN_USER_PASSWORD_NOT_FOUND "Admin User Password Not Found [Senha de Usuário Administrador Não Encontrada]"
#define UI_INFO_SYSTEM_FREEING_MEMORY "System is freeing memory [O Sistema está liberando memória]"
#define UI_SUCCESSFUL_CREATED_FILE_DB "Database created successfully [Banco de dados criado com sucesso]"
#define UI_ERROR_ADMIN_USER_PHONE_NOT_FOUND "Admin User Phone Not Found [Telefone de Usuário Administrador Não Encontrado]"
#define UI_USER_ROLE_NOT_FOUND "User Role Not Found [Cargo de Usuário Não Encontrado]"
#define UI_INCREASING_USER_CAPACITY "Increasing User Capacity [Aumentando Capacidade de Usuário]"
#define UI_DECREASING_USER_CAPACITY "Decreasing User Capacity [Diminuindo Capacidade de Usuário]"

// ===================================================================================================================================================================
// CONFIRMATION PROMPTS [PROMPT DE CONFIRMAÇÃO]
// ====================================================================================================================================================================

/// User
#define UI_CONFIRMATION_DELETE_USER "Are you sure you want to delete this user? [Tem certeza de que deseja excluir esse usuário?]"
// #define UI_CONFIRMATION_LOGOUT "Are you sure you want to logout? [Tem certeza de que deseja sair?]"
#define UI_CONFIRMATION_UPDATE_USER "Are you sure you want to update this user? [Tem certeza de que deseja atualizar esse usuário?]"
#define UI_CONFIRMATION_CREATE_USER "Are you sure you want to create this user? [Tem certeza de que deseja criar esse usuário?]"

/// Currency
#define UI_CONFIRMATION_DELETE_CURRENCY "Are you sure you want to delete this currency? [Tem certeza de que deseja excluir essa moeda?]"
#define UI_CONFIRMATION_UPDATE_CURRENCY "Are you sure you want to update this currency? [Tem certeza de que deseja atualizar essa moeda?]"
#define UI_CONFIRMATION_CREATE_CURRENCY "Are you sure you want to create this currency? [Tem certeza de que deseja criar essa moeda?]"

/// Exchange Rate
#define UI_CONFIRMATION_DELETE_EXCHANGE_RATE "Are you sure you want to delete this exchange rate? [Tem certeza de que deseja excluir esse câmbio?]"
#define UI_CONFIRMATION_UPDATE_EXCHANGE_RATE "Are you sure you want to update this exchange rate? [Tem certeza de que deseja atualizar esse câmbio?]"
#define UI_CONFIRMATION_CREATE_EXCHANGE_RATE "Are you sure you want to create this exchange rate? [Tem certeza de que deseja criar esse câmbio?]"

/// Transaction
#define UI_CONFIRMATION_DELETE_TRANSACTION "Are you sure you want to delete this transaction? [Tem certeza de que deseja excluir essa transação?]"
#define UI_CONFIRMATION_UPDATE_TRANSACTION "Are you sure you want to update this transaction? [Tem certeza de que deseja atualizar essa transação?]"
#define UI_CONFIRMATION_CREATE_TRANSACTION "Are you sure you want to create this transaction? [Tem certeza de que deseja criar essa transação?]"

// Session
#define UI_CONFIRMATION_LOGOUT "Are you sure you want to logout?(y/n) [Tem certeza de que deseja sair?(s/n)]"
// Exit Program
#define UI_CONFIRM_EXIT "Are you sure you want to exit the program?(y/n) [Tem certeza de que deseja sair do programa?(s/n)]"

// ===================================================================================================================================================================
// USER INTERFACE LABELS AND TEXTS [RÓTULOS E TEXTO DA INTERFACE DO USUARIO]
// ====================================================================================================================================================================
#define UI_LABEL_TITLE "UNICAMBIO SYSTEM [SISTEMA UNICAMBIO]"
#define UI_LABEL_TITLE_DESCRIPTION1 "A complete solution for currency exchange and transaction management."
#define UI_LABEL_TITLE_DESCRIPTION2 "[Uma solução completa para troca de moedas e gestão de transações.]"
#define UI_LABEL_EXIT "Exiting the system [Saindo do sistema]"
#define UI_LABEL_WELCOME "Welcome to UNICAMBIO [Bem-vindo ao UNICAMBIO]"
#define UI_LABEL_EXIT_MESSAGE "Thank you for using UNICAMBIO [Obrigado por usar o UNICAMBIO]"
#define UI_LABEL_PROMPT "Please select an option [Por favor, selecione uma opção]: "

/// Menus
#define UI_LABEL_MAIN_MENU "MAIN MENU [MENU PRINCIPAL]"
#define UI_LABEL_USER_MENU "USER MENU [MENU DE USUARIO]"
#define UI_LABEL_ADMIN_USER_MENU "ADMIN USER MENU [MENU DE USUARIO ADMINISTRADOR]"
#define UI_LABEL_CURRENCY_MENU "CURRENCY MENU [MENU DE MOEDA]"
#define UI_LABEL_EXCHANGE_RATE_MENU "EXCHANGE RATE MENU [MENU DE CÂMBIO]"
#define UI_LABEL_TRANSACTION_MENU "TRANSACTION MENU [MENU DE TRANSACAO]"
#define UI_LABEL_LOGIN_PAGE "LOGIN PAGE [PAGINA DE LOGIN]"
#define UI_HOME_PAGE "HOME PAGE [PAGINA INICIAL]"
#define UI_LABEL_LOGOUT "0. Logout [Sair]"
#define UI_LABEL_GO_BACK "0. Go Back [Retornar]"
#define UI_USERNAME "Username: "
#define UI_PASSWORD "Password: "

/// Menu options
#define UI_START_SESSION_MENU_OPT_1 "Type 1 to start a session or 0 to exit."
#define UI_START_SESSION_MENU_OPT_1_PT "[Digite 1 para iniciar uma sessão ou 0 para sair]"
#define UI_ADMIN_MENU_OPT_1 "1. Manage Users [Gerenciar Usuários]"
#define UI_ADMIN_MENU_OPT_2 "2. Manage Roles [Gerenciar Papéis]"
#define UI_ADMIN_MENU_OPT_3 "3. Manage Currencies [Gerenciar Moedas]"
#define UI_ADMIN_MENU_OPT_4 "4. Manage Exchange Rates [Gerenciar Taxas de Câmbio]"
#define UI_ADMIN_MENU_OPT_5 "5. Manage Transactions [Gerenciar Transações]"

/// Information displays
#define UI_CURRENCY_LIST "CURRENCY LIST [LISTA DE MOEDAS]"
#define UI_VIEW_AVAILABLE_CURRENCIES "AVAILABLE CURRENCIES [MOEDAS DISPONÍVEIS]"
#define UI_VIEW_EXCHANGE_RATES "EXCHANGE RATES [TAXAS DE CÂMBIO]"
#define UI_VIEW_TRANSACTIONS "TRANSACTIONS [TRANSAÇÕES]"

#endif // MESSAGES_H
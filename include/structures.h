/**
 * @file structures.h
 * @author Chinedum Odili (https://github.com/ChinedumOdili)
 * @brief A header file for the unicambio project [Arquivo de cabeçalho para o projeto unicambio]
 * This file contains all data structures used in the system
 * [Este arquivo contém todas as estruturas utilizadas no sistema.]
 * @version 1.0
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H
/*
==================================================================================================================
																			Enum Structure
																			[Estrutura de Enumeração]
==================================================================================================================
*/
typedef enum
{
	active = 1,
	inActive = 0
} StatusInfo;

typedef enum
{
	false = 0,
	true = 1
} BoolInfo;

/*
==================================================================================================================
																			Role Structure
																			[Estrutura de Papel]
==================================================================================================================
*/
typedef struct
{
	int role_id;			 // Unique identifier for the role [Identificador único para o papel]
	char *role_name;	 // Pointer to the name of the role [Apontador para o nome do papel]
	char *description; // Pointer to the description of the role [Apontador para a descrição do papel]
	time_t created_at_date;
	time_t created_at_time;
	time_t updated_at_date;
	time_t updated_at_time;
	time_t deleted_at_date;
	time_t deleted_at_time;
} RoleInfo;

/*
==================================================================================================================
																			User Structure
																			[Estrutura de Usuário]
==================================================================================================================
*/
typedef struct
{
	int user_id;					// Unique identifier for the user [Identificador único para o usuário]
	char *name;						// Pointer to the user's name [Apontador para o nome do usuário]
	char *username;				// Pointer to the user's username [Apontador para o nome de usuário do usuário]
	char *email;					// Pointer to the user's email [Apontador para o email do usuário]
	char *password;				// Pointer to the user's password [Apontador para a senha do usuário]
	char *phone;					// Pointer to the user's phone number [Apontador para o número de telefone do usuário]
	RoleInfo *user_role;	// Pointer to the user's role information [Apontador para as informações do papel do usuário]
	StatusInfo is_active; // Flag indicating if the user is active (1) or inactive (0) [Indicador se o usuário está ativo (1) ou inativo (0)]

	// int is_active;			 // Flag indicating if the user is active (1) or inactive (0) [Indicador se o usuário está ativo (1) ou inativo (0)]
	time_t created_at_date;
	time_t created_at_time;
	time_t updated_at_date;
	time_t updated_at_time;
	time_t deleted_at_date;
	time_t deleted_at_time;
} UserInfo;

/*
==================================================================================================================
																			Currency Structure
																			[Estrutura de Moeda]
==================================================================================================================
*/
typedef struct
{
	const int currency_id; // Unique identifier for the currency [Identificador único para a moeda]
	char *name;						 // Pointer to the name of the currency [Apontador para o nome da moeda]
	char *code;						 // Pointer to the code of the currency [Apontador para o código da moeda]
	char *abbreviation;		 // Pointer to the abbreviation of the currency [Apontador para a abreviação da moeda]
	char *country;				 // Pointer to the country where the currency is used [Apontador para o país onde a moeda é usada]
	time_t created_at_date;
	time_t created_at_time;
	time_t updated_at_date;
	time_t updated_at_time;
	time_t deleted_at_date;
	time_t deleted_at_time;
} CurrencyInfo;

/*
==================================================================================================================
																			Exchange Rate Structure
																			[Estrutura de Taxa de Câmbio]
==================================================================================================================
*/
typedef struct
{
	int rate_id;								 // Unique identifier for the exchange rate [Identificador único para a taxa de câmbio]
	CurrencyInfo *from_currency; // Pointer to the currency from which the exchange rate is applied [Apontador para a moeda da qual a taxa de câmbio é aplicada]
	CurrencyInfo *to_currency;	 // Pointer to the currency to which the exchange rate is applied [Apontador para a moeda para a qual a taxa de câmbio é aplicada]
	float rate;									 // The exchange rate value [O valor da taxa de câmbio]
	time_t created_at_date;
	time_t created_at_time;
	time_t updated_at_date;
	time_t updated_at_time;
	time_t deleted_at_date;
	time_t deleted_at_time;
} ExchangeRateInfo;

/*
==================================================================================================================
																			Transaction Structure
																			[Estrutura de Transação]
==================================================================================================================
*/
typedef struct
{
	int transaction_id;							 // Unique identifier for the transaction [Identificador único para a transação]
	UserInfo *user;									 // Pointer to the user who made the transaction [Apontador para o usuário que fez a transação]
	CurrencyInfo *from_currency;		 // Pointer to the currency from which the transaction is made [Apontador para a moeda da qual a transação é feita]
	CurrencyInfo *to_currency;			 // Pointer to the currency to which the transaction is made [Apontador para a moeda para a qual a transação é feita]
	ExchangeRateInfo *exchange_rate; // Pointer to the exchange rate applied to the transaction [Apontador para a taxa de câmbio aplicada à transação]
	float amount;										 // The amount of the transaction [O valor da transação]
	time_t created_at_date;
	time_t created_at_time;
	time_t updated_at_date;
	time_t updated_at_time;
	time_t deleted_at_date;
	time_t deleted_at_time;
} TransactionInfo;

/*
==================================================================================================================
																			System Data Structure
																			[Estrutura de Dados do Sistema]
==================================================================================================================
*/
typedef struct
{

	// linking the userinfo to the system structure
	// [Vinculando as informações do usuário à estrutura do sistema]
	UserInfo *users;		 // Pointer to the array of users in the system [Apontador para o array de usuários no sistema]
	size_t userCapacity; // Capacity of the user array [Capacidade do array de usuários]
	size_t userCount;		 // Current number of users in the system [Número atual de usuários no sistema]
	size_t userLimit;		 // Limit of users in the system [Limite de usuários no sistema]

	// linking the roleinfo to the system structure
	// [Vinculando as informações do papel à estrutura do sistema]
	RoleInfo *roles;		 // Pointer to the array of roles in the system [Apontador para o array de papéis no sistema]
	size_t roleCapacity; // Capacity of the role array [Capacidade do array de papéis]
	size_t roleCount;		 // Current number of roles in the system [Número atual de papéis no sistema]
	size_t roleLimit;		 // Limit of roles in the system [Limite de papéis no sistema]

	// linking the currencyinfo to the system structure
	// [Vinculando as informações da moeda à estrutura do sistema]
	CurrencyInfo *currencies; // Pointer to the array of currencies in the system [Apontador para o array de moedas no sistema]
	size_t currencyCapacity;	// Capacity of the currency array [Capacidade do array de moedas]
	size_t currencyCount;			// Current number of currencies in the system [Número atual de moedas no sistema]
	size_t currencyLimit;			// Limit of currencies in the system [Limite de moedas no sistema]

	// linking the exchangerateinfo to the system structure
	// [Vinculando as informações da taxa de câmbio à estrutura do sistema]
	ExchangeRateInfo *rates; // Pointer to the array of exchange rates in the system [Apontador para o array de taxas de câmbio no sistema]
	size_t rateCapacity;		 // Capacity of the exchange rate array [Capacidade do array de taxas de câmbio]
	size_t rateCount;				 // Current number of exchange rates in the system [Número atual de taxas de câmbio no sistema]
	size_t rateLimit;				 // Limit of exchange rates in the system [Limite de taxas de câmbio no sistema]

	// linking the transactioninfo to the system structure
	// [Vinculando as informações da transação à estrutura do sistema]
	TransactionInfo *transactions; // Pointer to the array of transactions in the system [Apontador para o array de transações no sistema]
	size_t transactionCapacity;		 // Capacity of the transaction array [Capacidade do array de transações]
	size_t transactionCount;			 // Current number of transactions in the system [Número atual de transações no sistema]
	size_t transactionLimit;			 // Limit of transactions in the system [Limite de transações no sistema]

	// linking the statusinfo to the system structure
	StatusInfo activationStatus;

	// Linking the Boolean Info to the system structure
	BoolInfo bool;

} SystemData;

#endif // STRUCTURES_H

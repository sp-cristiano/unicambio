/**
 * @file structures.h
 * @author Chinedum Odili (https://github.com/ChinedumOdili)
 * @brief A header file for the unicambio project [Arquivo de cabeçalho para o projeto unicambio]
 * This file contains all the structures.
 * [Este arquivo contém todas as estruturas.]
 * @version 1.0
 */
/*
*****************************************************************************************
This file is the header file for the unicambio project.
[Este arquivo é o arquivo de cabeçalho para o projeto unicambio.]
*****************************************************************************************
*/
#ifndef STRUCTURES_H
#define STRUCTURES_H
/*
******************************************************************************************
User defined Structure.
[Estrutura definida pelo usuário.]
******************************************************************************************
*/
// This structure defines the role information in the system.
// [Esta estrutura define as informações do papel no sistema.]
typedef struct
{
	int role_id;			 // Unique identifier for the role [Identificador único para o papel]
	char *role_name;	 // Pointer to the name of the role [Apontador para o nome do papel]
	char *description; // Pointer to the description of the role [Apontador para a descrição do papel]
	char *created_at;	 // Pointer to the date and time when the role was created [Apontador para a data e hora em que o papel foi criado]
	char *updated_at;	 // Pointer to the date and time when the role was last updated [Apontador para a data e hora em que o papel foi atualizado pela última vez]
	char *deleted_at;	 // Pointer to the date and time when the role was deleted [Apontador para a data e hora em que o papel foi deletado]
} RoleInfo;

// This structure defines the user information in the system.
// [Esta estrutura define as informações do usuário no sistema.]

typedef struct
{
	int user_id;				 // Unique identifier for the user [Identificador único para o usuário]
	char *name;					 // Pointer to the user's name [Apontador para o nome do usuário]
	char *username;			 // Pointer to the user's username [Apontador para o nome de usuário do usuário]
	char *email;				 // Pointer to the user's email [Apontador para o email do usuário]
	char *password;			 // Pointer to the user's password [Apontador para a senha do usuário]
	char *phone;				 // Pointer to the user's phone number [Apontador para o número de telefone do usuário]
	RoleInfo *user_role; // Pointer to the user's role information [Apontador para as informações do papel do usuário]
	int is_active;			 // Flag indicating if the user is active (1) or inactive (0) [Indicador se o usuário está ativo (1) ou inativo (0)]
	char *created_at;		 // Pointer to the date and time when the user was created [Apontador para a data e hora em que o usuário foi criado]
	char *last_seen;		 // Pointer to the date and time when the user was last logged in [Apontador para a data e hora em que o usuário foi visto pela última vez]
	char *deleted_at;		 // Pointer to the date and time when the user was deleted [Apontador para a data e hora em que o usuário foi deletado]
} UserInfo;

// This structure defines the currency information in the system.
// [Esta estrutura define as informações da moeda no sistema.]
typedef struct
{
	int currency_id;		// Unique identifier for the currency [Identificador único para a moeda]
	char *name;					// Pointer to the name of the currency [Apontador para o nome da moeda]
	char *code;					// Pointer to the code of the currency [Apontador para o código da moeda]
	char *abbreviation; // Pointer to the abbreviation of the currency [Apontador para a abreviação da moeda]
	char *country;			// Pointer to the country where the currency is used [Apontador para o país onde a moeda é usada]
	char *created_at;		// Pointer to the date and time when the currency was created [Apontador para a data e hora em que a moeda foi criada]
	char *updated_at;		// Pointer to the date and time when the currency was last updated [Apontador para a data e hora em que a moeda foi atualizada pela última vez]
	char *deleted_at;		// Pointer to the date and time when the currency was deleted [Apontador para a data e hora em que a moeda foi deletada]
} CurrencyInfo;

// This structure defines the exchange rate information in the system.
typedef struct
{
	int rate_id;								 // Unique identifier for the exchange rate [Identificador único para a taxa de câmbio]
	CurrencyInfo *from_currency; // Pointer to the currency from which the exchange rate is applied [Apontador para a moeda da qual a taxa de câmbio é aplicada]
	CurrencyInfo *to_currency;	 // Pointer to the currency to which the exchange rate is applied [Apontador para a moeda para a qual a taxa de câmbio é aplicada]
	float rate;									 // The exchange rate value [O valor da taxa de câmbio]
	char *created_at;						 // Pointer to the date and time when the exchange rate was created [Apontador para a data e hora em que a taxa de câmbio foi criada]
	char *updated_at;						 // Pointer to the date and time when the exchange rate was last updated [Apontador para a data e hora em que a taxa de câmbio foi atualizada pela última vez]
	char *deleted_at;						 // Pointer to the date and time when the exchange rate was deleted [Apontador para a data e hora em que a taxa de câmbio foi deletada]
} ExchangeRateInfo;

// This structure defines the transaction information in the system.
// [Esta estrutura define as informações da transação no sistema.]
typedef struct
{
	int transaction_id;					 // Unique identifier for the transaction [Identificador único para a transação]
	UserInfo *user;							 // Pointer to the user who made the transaction [Apontador para o usuário que fez a transação]
	CurrencyInfo *from_currency; // Pointer to the currency from which the transaction is made [Apontador para a moeda da qual a transação é feita]
	CurrencyInfo *to_currency;	 // Pointer to the currency to which the transaction is made [Apontador para a moeda para a qual a transação é feita]
	float amount;								 // The amount of the transaction [O valor da transação]
	char *transaction_date;			 // Pointer to the date and time when the transaction was made [Apontador para a data e hora em que a transação foi feita]
	char *transaction_time;			 // Pointer to the time when the transaction was made [Apontador para a hora em que a transação foi feita]
	char *created_at;						 // Pointer to the date and time when the transaction was created [Apontador para a data e hora em que a transação foi criada]
	char *updated_at;						 // Pointer to the date and time when the transaction was last updated [Apontador para a data e hora em que a transação foi atualizada pela última vez]
	char *deleted_at;						 // Pointer to the date and time when the transaction was deleted [Apontador para a data e hora em que a transação foi deletada]
} TransactionInfo;

// This structure defines the system data configuration in the system.
// [Esta estrutura define a configuração dos dados do sistema no sistema.]
typedef struct
{
	// linking the userinfo to the system structure
	// [Vinculando as informações do usuário à estrutura do sistema]
	UserInfo *users;	// Pointer to the array of users in the system [Apontador para o array de usuários no sistema]
	int userCapacity; // Capacity of the user array [Capacidade do array de usuários]
	int userCount;		// Current number of users in the system [Número atual de usuários no sistema]
	int userLimit;		// Limit of users in the system [Limite de usuários no sistema]

	// linking the roleinfo to the system structure
	// [Vinculando as informações do papel à estrutura do sistema]
	RoleInfo *roles;	// Pointer to the array of roles in the system [Apontador para o array de papéis no sistema]
	int roleCapacity; // Capacity of the role array [Capacidade do array de papéis]
	int roleCount;		// Current number of roles in the system [Número atual de papéis no sistema]
	int roleLimit;		// Limit of roles in the system [Limite de papéis no sistema]

	// linking the currencyinfo to the system structure
	// [Vinculando as informações da moeda à estrutura do sistema]
	CurrencyInfo *currencies; // Pointer to the array of currencies in the system [Apontador para o array de moedas no sistema]
	int currencyCapacity;			// Capacity of the currency array [Capacidade do array de moedas]
	int currencyCount;				// Current number of currencies in the system [Número atual de moedas no sistema]
	int currencyLimit;				// Limit of currencies in the system [Limite de moedas no sistema]

	// linking the exchangerateinfo to the system structure
	// [Vinculando as informações da taxa de câmbio à estrutura do sistema]
	ExchangeRateInfo *rates; // Pointer to the array of exchange rates in the system [Apontador para o array de taxas de câmbio no sistema]
	int rateCapacity;				 // Capacity of the exchange rate array [Capacidade do array de taxas de câmbio]
	int rateCount;					 // Current number of exchange rates in the system [Número atual de taxas de câmbio no sistema]
	int rateLimit;					 // Limit of exchange rates in the system [Limite de taxas de câmbio no sistema]

	// linking the transactioninfo to the system structure
	// [Vinculando as informações da transação à estrutura do sistema]
	TransactionInfo *transactions; // Pointer to the array of transactions in the system [Apontador para o array de transações no sistema]
	int transactionCapacity;			 // Capacity of the transaction array [Capacidade do array de transações]
	int transactionCount;					 // Current number of transactions in the system [Número atual de transações no sistema]
	int transactionLimit;					 // Limit of transactions in the system [Limite de transações no sistema]
} SystemData;

#endif // STRUCTURES_H

/**
 * @file structures.h
 * @author Chinedum Odili (https://github.com/sp-cristiano)
 * @brief This file contains all data structures used in this project.
 * [Este arquivo contém todas as estruturas de dados usadas neste projeto.]
 * @version 0.1
 * @date 2025-06-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "../include/unicambio.h"

/**
 * @brief Log level enumeration
 * [Enumeração de nível de log]
 */
typedef enum
{
	LOG_ERROR,
	LOG_INFO,
	LOG_WARNING,
	LOG_DEBUG
} LogLevel;

/**
 * @brief Status enumeration for active/inactive state
 * [Enumeração de status para estado ativo/inativo]
 */
typedef enum
{
	failed = -2,
	deleted = -1,
	successful = 0,
	active = 1,
	pending = 2,
	inActive = 3,
	available = 4
} StatusInfo;

/**
 * @brief Date and Time enumeration to select if to show date, time or both. [
 * Enumeração de data e hora para selecionar se mostrar data, hora ou ambos.]
 *
 *
 */
typedef enum
{
	TYPE_DATE = 0,
	TYPE_TIME = 1,
	TYPE_DATE_TIME = 2
} DateTimeInfo;

/**
 * @brief Boolean type alternative (true/false)
 * [Tipo alternativo de booleano (verdadeiro/falso)]
 */
typedef enum
{
	false = 0,
	true = 1
} BoolInfo;

/**
 * @brief Represents user roles in the system
 * [Representa os perfis de usuário no sistema]
 */
typedef enum
{
	ROLE_ADMIN = 1,
	ROLE_USER = 2
} RoleInfo;

/**
 * @brief Runtime context information for the application session
 * [Informações de contexto de execução para a sessão da aplicação]
 * Stores current user, session state, system metadata, and adminstrative credentials.active
 * [Armazena o usuário atual, o estado da sessão, metadados do sistema e credenciais administrativas ativas]
 */
typedef struct
{
	// char currentDate[MAX_DATE_LENGTH]; ///< Current system date as string [Data atual do sistema como string]
	// char currentTime[MAX_DATE_LENGTH]; ///< Current system time as string [Hora atual do sistema como string]

	char *currentDate;				 ///< Current system date as string [Data atual do sistema como string]
	char *currentTime;				 ///< Current system time as string [Hora atual do sistema como string]
	char *currentUserName;		 ///< Current user logged in [Usuário atual logado]
	char *ADMIN_USER_PASSWORD; ///< Default admin password [Senha padrão do administrador]
	char *ADMIN_USER_EMAIL;		 ///< Default admin email [Email padrão do administrador]
	char *ADMIN_USER_PHONE;		 ///< Default admin phone number [Número de telefone padrão do administrador]
	int exitFlag;							 ///< Application exit flag [Flag de saída da aplicação]
	int isAuthenticated;			 ///< Authentication status [Status de autenticação]
	int loginAttempts;				 ///< Number of login attempts [Número de tentativas de login]
	int session;							 ///< Session state [Estado da sessão]
	int goBack;								 ///< Go back flag [Flag de retorno]
	int currentUserID;				 ///< Current user ID [ID do usuário atual]
	int currentUserRoleID;		 ///< Current user role ID [ID do papel do usuário atual]
} AppContextInfo;

/**
 * @brief Represents a system user with personal and access details.
 * [Representa um usuário do sistema com detalhes pessoais e de acesso.]
 */
typedef struct
{
	int userID;			///< User ID [ID do usuário]
	char *name;			///< User name [Nome do usuário]
	char *userName; ///< User name [Nome do usuário]
	char *email;		///< User email [Email do usuário]
	char *password; ///< User password [Senha do usuário]
	char *phone;		///< User phone number [Número de telefone do usuário]
	int roleID;			///< User role ID [ID do papel do usuário]
	int userStatus; ///< User status [Status do usuário]
	char *createAt; ///< User creation date [Data de criação do usuário]
	char *lastSeen; ///< User last seen date [Última vez que o usuário foi visto]
	char *deleteAt; ///< User deletion date [Data de exclusão do usuário]
} UserInfo;

/**
 * @brief Contains metadata about a specific currency.
 * [Contém metadados sobre uma moeda específica.]
 */
typedef struct
{
	int currencyID;			///< Unique currency ID [ID exclusivo da moeda]
	char *name;					///< Name of the currency [Nome da moeda]
	char *abbreviation; ///< Currency abbreviation [Abreviação da moeda]
	char *code;					///< Currency code [Código da moeda]
	char *symbol;				///< Currency symbol [Símbolo da moeda]
	char *country;			///< Country of origin [País de origem]
	int currencyStatus; ///< Currency status [Status da moeda]
	double rateToOneKz;
	char *createdAt; ///< Date of currency creation [Data de criação da moeda]
	char *updatedAt; ///< Date of last currency update [Data da última atualização da moeda]
	char *deletedAt; ///< Date of currency deletion [Data de exclusão da moeda]
} CurrencyInfo;

/**
 * @brief Represents exchange rate information between two currencies.
 * [Representa informações de câmbio entre duas moedas.]
 */
typedef struct
{
	int exchangeRateID;									///< Unique exchange rate ID [ID exclusivo de câmbio]
	int fromCurrencyID;									///< Currency being exchanged from [Moeda sendo trocada de]
	double fromCurrencyAmountToConvert; ///< Amount to be converted [Quantidade a ser convertida]
	double fromCurrencyRateToKz;				///< Exchange rate value [Valor do câmbio]
	int toCurrencyID;										///< Currency being exchanged to [Moeda sendo trocada para]
	int exchangeRateStatus;							///< Exchange rate status [Status do câmbio]
	double toCurrencyAmountConvertedTo; ///< Converted amount [Quantidade convertida]
	double toCurrencyRateToKz;					///< Exchange rate value [Valor do câmbio]
	char *createdAt;										///< Date of exchange rate creation [Data de criação do câmbio]
	char *updatedAt;										///< Date of last exchange rate update [Data da última atualização do câmbio]
	char *deletedAt;										///< Date of exchange rate deletion [Data de exclusão do câmbio]
} ExchangeRateInfo;

/**
 * @brief Represents a transaction between two currencies.
 * [Representa uma transação entre duas moedas.]
 */
typedef struct
{
	int transactionID; ///< Unique transaction ID [ID exclusivo da transação]
	int exchangeRateID;	///< Exchange rate associated with the transaction [Câmbio associado à transação]
	int userID;					///< User associated with the transaction [Usuário associado à transação]
	int fromCurrencyID; ///< Currency being exchanged from [Moeda sendo trocada de]
	double fromCurrencyAmount;
	int toCurrencyID; ///< Currency being exchanged to [Moeda sendo trocada para]
	double toCurrencyAmount;
	double exchangeRate; ///< Exchange rate information [Informações de câmbio]
	// double amount;										///< Amount of currency being exchanged [Quantidade de moeda sendo trocada]
	int transactionStatus; ///< Transaction status [Status da transação]
	char *createdAt;			 ///< Date of transaction creation [Data de criação da transação]
	char *updatedAt;			 ///< Date of last transaction update [Data da última atualização da transação]
	char *deletedAt;			 ///< Date of transaction deletion [Data de exclusão da transação]
} TransactionInfo;

/**
 * @brief Master structure containing all system data entities
 * [Estrutura mestre contendo todas as entidades de dados do sistema]
 * This act like a pseudo-database in memory: Holds all data entities along with tracking capacities.
 * [Isso parece ser uma pseudo-banco de dados em memória: Armazena todas as entidades de dados junto com capacidades de rastreamento.]
 */
typedef struct
{
	// Users
	UserInfo *users;		 ///< Array of users [Array de usuários]
	size_t userCapacity; ///< Maximum number of users [Número máximo de usuários]
	size_t userCount;		 ///< Current number of users [Número atual de usuários]
	size_t userLimit;		 ///< Maximum number of users allowed [Número máximo de usuários permitidos]

	// Currencies
	CurrencyInfo *currencies; ///< Array of currencies [Array de moedas]
	size_t currencyCapacity;	///< Maximum number of currencies [Número máximo de moedas]
	size_t currencyCount;			///< Current number of currencies [Número atual de moedas]
	size_t currencyLimit;			///< Maximum number of currencies allowed [Número máximo de moedas permitidas]

	// Exchange Rates
	ExchangeRateInfo *exchangeRates; ///< Array of exchange rates [Array de câmbios]
	size_t exchangeRateCapacity;		 ///< Maximum number of exchange rates [Número máximo de câmbios]
	size_t exchangeRateCount;				 ///< Current number of exchange rates [Número atual de câmbios]
	size_t exchangeRateLimit;				 ///< Maximum number of exchange rates allowed [Número máximo de câmbios permitidos]

	// Transactions
	TransactionInfo *transactions; ///< Array of transactions [Array de transações]
	size_t transactionCapacity;		 ///< Maximum number of transactions [Número máximo de transações]
	size_t transactionCount;			 ///< Current number of transactions [Número atual de transações]
	size_t transactionLimit;			 ///< Maximum number of transactions allowed [Número máximo de transações permitidas]

	// App Runtime Context
	AppContextInfo *appContext; ///< Application context information [Informações de contexto da aplicação]
	size_t appContextCount;
	size_t appContextCapacity;
	size_t appContextLimit;

	// System control
	size_t systemStatus;
	size_t systemCount;
	size_t systemCapacity;
	size_t systemLimit;
} SystemData;
#endif // STRUCTURES_H
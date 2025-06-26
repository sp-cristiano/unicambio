#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "../include/unicambio.h"
typedef struct
{
	char *currentUserName;
	char *adminUserPassword;
	char *adminUserEmail;
	char *adminUserPhone;
	int exitFlag;
	int isAuthenticated;
	int loginAttempts;
	int session;
	int goBack;
	int currentUserID;
	int currentUserRoleID;

} AppContextInfo;

typedef struct
{
	int userID;
	char *name;
	char *username;
	char *email;
	char *password;
	char *phone;
	int roleID;
	int userStatus;
	char *dateCreated;
	char *lastUpdated;
	char *lastLogin;
	char *dateDeleted;
} UserInfo;

typedef struct
{
	int currencyID;
	char *name;
	char *code;
	char *symbol;
	char *country;
	int currencyStatus;
	double rate;
	char *dateCreated;
	char *lastUpdated;
	char *dateDeleted;
} CurrencyInfo;
typedef struct
{
	// app context
	AppContextInfo *appContext;
	size_t appContextCapacity;
	size_t appContextCount;
	size_t appContextLimit;

	// users
	UserInfo *users;
	size_t userCapacity;
	size_t userCount;
	size_t userLimit;

	// currencies
	CurrencyInfo *currencies;
	size_t currencyCapacity;
	size_t currencyCount;
	size_t currencyLimit;
	//
} SystemData;

#endif // STRUCTURES_H
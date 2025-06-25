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

	//
} SystemData;

#endif // STRUCTURES_H
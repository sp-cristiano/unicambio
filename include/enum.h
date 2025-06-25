#ifndef ENUM_H
#define ENUM_H

typedef enum
{
	LOG_ERROR,
	LOG_INFO,
	LOG_DEBUG,
	LOG_WARNING,
	LOG_SUCCESS
} LogLevel;

typedef enum
{
	deleted = -2,
	failed = -1,
	successful = 0,
	active = 1,
	available = 2
} StatusInfo;

typedef enum
{
	TYPE_DATE = 0,
	TYPE_TIME = 1,
	TYPE_DATETIME = 2
} DateTimeInfo;

typedef enum
{
	false = 0,
	true = 1
} BoolInfo;

typedef enum
{
	ROLE_ADMIN = 1,
	ROLE_USER = 2
} RoleInfo;

typedef enum
{
	yes = 1,
	no = 0
} yesOrNoInfo;

#endif // ENUM_H

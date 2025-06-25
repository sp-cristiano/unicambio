#include "../include/structures.h"
#include "../include/userFunction.h"
#include "../include/enum.h"
#include "../include/saveSystemData.h"
#include "../include/utilities.h"
#include "../include/logger.h"

StatusInfo saveSystemData(SystemData *sysData)
{
	StatusInfo status;
	if (saveUserData(sysData) != successful)
	{
		status = failed;
		return status;
	}
	status = successful;
	return status;
}

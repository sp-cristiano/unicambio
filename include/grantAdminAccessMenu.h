#ifndef GRANT_ADMIN_ACCESS_MENU_H
#define GRANT_ADMIN_ACCESS_MENU_H

#include "../include/structures.h"
#include "../include/enum.h"

StatusInfo grantAdminAccessMenu(SystemData *sysData);
StatusInfo performCurrencyOperationsMenu(SystemData *sysData);
StatusInfo performUserOperationsMenu(SystemData *sysData);
StatusInfo performExchangeRateOperationsMenu(SystemData *sysData);
StatusInfo performTransactionOperationsMenu(SystemData *sysData);

#endif // GRANT_ADMIN_ACCESS_MENU_H
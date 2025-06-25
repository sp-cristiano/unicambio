#ifndef GRANT_USER_ACCESS_MENU_H
#define GRANT_USER_ACCESS_MENU_H

#include "../include/structures.h"
#include "../include/enum.h"

StatusInfo grantUserAccessMenu(SystemData *sysData);
StatusInfo viewAvailableCurrenciesMenu(SystemData *sysData);
StatusInfo verifyExchangeRatesMenu(SystemData *sysData);
StatusInfo createTransactionMenu(SystemData *sysData);
StatusInfo viewTransactionHistoryMenu(SystemData *sysData);

#endif // GRANT_USER_ACCESS_MENU_H
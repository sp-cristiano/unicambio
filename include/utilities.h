#ifndef UTILITIES_H
#define UTILITIES_H

#include "../include/structures.h"
#include "../include/enum.h"

void centerStrings(char *string);
void alignTextRight(char *string);
void printSymbols(int quantity, char symbol);
void displayBanner(SystemData *sysData);
void clearScreen();
StatusInfo setLocation();
char *getCurrentDateTime(int type);
int randomNumber(int min, int max);
void exitProgram(SystemData *sysData);
void processing();
int getUserIndexByID(SystemData *sysData, int userID);
void logoutUser(SystemData *sysData);
void clearInputBuffer();
int getUserIDByMultipleSearch(SystemData *sysData, char *multiSearch);
StatusInfo viewSingleUser(SystemData *sysData, size_t userIndex);
void selectOptionToUpdateUserByAdmin(SystemData *sysData, size_t userIndex);
double convertRateToOneKz(double rate);
double convertRateFromOneKz(double rateToOneKz);
double getCurrencyRateToOneKz(SystemData *sysData, int currencyID);

#endif // UTILITIES_H
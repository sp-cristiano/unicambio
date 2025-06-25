#ifndef UTILITIES_H
#define UTILITIES_H

#include "../include/structures.h"
#include "../include/enum.h"

void centerStrings(char *string);
void alignTextRight(char *string);
void printSymbols(int quantity, char symbol);
void displayBanner();
void clearScreen();
StatusInfo setLocation();
char *getCurrentDateTime(int type);
int randomNumber(int min, int max);
void exitProgram(SystemData *sysData);
void processing();
int getUserIndexByID(SystemData *sysData, int userID);
void logoutUser(SystemData *sysData);

#endif // UTILITIES_H
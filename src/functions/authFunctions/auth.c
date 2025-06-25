#include "../include/unicambio.h"
#include "../include/auth.h"
#include "../include/utilities.h"
#include "../include/logger.h"
#include "../include/structures.h"
#include "../include/enum.h"

char *hashPassword(const char *password)
{
	char *hashStr = malloc(crypto_pwhash_STRBYTES);

	if (!hashStr)
	{
		logPrintMessage(LOG_ERROR, "Failed to allocate memory for hash string [ Falha ao alocar memória para a string de hash ]", yes);
		return NULL;
	}
	if (crypto_pwhash_str(hashStr, password, strlen(password), crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0)
	{
		logPrintMessage(LOG_ERROR, "Failed to hash password [ Falha ao hashar a senha ]", yes);
		free(hashStr);
		return NULL;
	}
	else
	{
		return hashStr;
	}
}

int verifyPassword(const char *password, const char *hash)
{
	if (crypto_pwhash_str_verify(hash, password, strlen(password)) == 0)
	{
		return true;
	}
	return false;
}
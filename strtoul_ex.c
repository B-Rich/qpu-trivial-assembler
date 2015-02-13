#define _BSD_SOURCE

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include "error.h"

unsigned long int strtoul_ex(const char *nptr)
{
	int i, base = 0;
	char str[32 + 1];
	unsigned long int num;

	i = 0;
	while (*nptr++) {
		if (i >= 32) {
			error("specified number is too big");
			exit(EXIT_FAILURE);
		} else if ((!isdigit(*nptr)) && (!isxdigit(*nptr)) && (!isspace(*nptr)) && *nptr != 'x' && *nptr != '\0') {
			error("invalid character: %c (%d)\n", *nptr, *nptr);
			exit(EXIT_FAILURE);
		}
		if(!isspace(*nptr))
			str[i ++] = *nptr;
	}
	str[i] = '\0';

	if (!strcmp(nptr, "0b")) {
		base = 2;
		nptr += 2;
	}

	errno = 0;
	num = strtoul(str, NULL, base);

	if ((errno == ERANGE && num == ULONG_MAX) || (errno != 0 && num == 0)) {
		error("strtoul: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	return num;
}

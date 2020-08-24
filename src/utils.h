//
// Created by alexander on 8/24/2020.
//

#ifndef C_UTILS_H
#define C_UTILS_H

#include <stdlib.h>
#include <string.h>

int split(char*** found, char* str, const char* delimiter)
{
	*found = malloc(0);

	char* nextToken;
	char* token = strtok_s(str, delimiter, &nextToken);
	int currentSize = 0;

	while (token)
	{
		*found = realloc(*found, sizeof(char*) * (currentSize + 1));
		(*found)[currentSize] = token;

		token = strtok_s(NULL, delimiter, &nextToken);
		currentSize++;
	}

	return currentSize;
}

#endif //C_UTILS_H

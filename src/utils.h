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

// check if a char pointer/string exists in an array/pointer to a pointer of chars
int str_exists(const char** arr, const arrsize, const char* match)
{
	int result = 0;
	for (int i = 0; i < arrsize; i++)
	{
		if ((*arr) + i == match)
		{
			result = 1;
			break;
		}
	}

	return result;
}

#endif //C_UTILS_H

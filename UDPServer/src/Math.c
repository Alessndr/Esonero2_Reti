#include "Math.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

bool parseStringOperation(const char* string, Integers* integers) {
	char copy[SIZE];
	strcpy(copy, string);

	// Parsing process
	char* token = strtok(copy, " ");
	if (token == NULL)
		return false; // ParsingException: token not found

	if (token[0] != '+' && token[0] != '-' && token[0] != '/' && token[0] != 'x')
		return false; // ParsingException: Invalid operator


	integers->operation = token[0];

	token = strtok(NULL, " ");
	if (token == NULL)
		return false; // ParsingException: integers missing


	if (!isdigit(token[0]))
		return false; // ParsingException: Invalid integer format

	integers->x = atoi(token);

	token = strtok(NULL, " ");
	if (token == NULL)
		return false; // ParsingException: integers missing


	if (!isdigit(token[0]))
		return false; // ParsingException: Invalid integer format

	integers->y = atoi(token);

	token = strtok(NULL, " ");
	if (token != NULL)
		return false; // ParsingException: Too many tokens


	return true; // Parsing: success
}



void add(Integers_h integers){
	sprintf(integers->result, "%d + %d = %d", integers->x, integers->y, integers->x + integers->y);
}

void sub(Integers_h integers){
	sprintf(integers->result, "%d - %d = %d", integers->x, integers->y, integers->x - integers->y);
}
/*
 * Throws ArithmeticException into result.
 */

void division(Integers_h integers){
	if(integers->y == 0 || (integers->x == 0 && integers->y == 0))
		strcpy(integers->result, "ArithmeticException: dividing by zero is not allowed");
	else
		sprintf(integers->result, "%d / %d = %d", integers->x, integers->y, integers->x / integers->y);
}


void multi(Integers_h integers){
	sprintf(integers->result, "%d x %d = %d", integers->x, integers->y, integers->x * integers->y);
}


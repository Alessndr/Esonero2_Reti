#ifndef Math_h
#define Math_h
#include <stdbool.h>
#define SIZE 1024

/*
 * Useful struct to save operands, operation, and result.
 * Result is used to save possible Exceptions to send to the Client, such as ParsingException,
 * and ArithmeticException.
 */

typedef struct{
	int x;
	int y;
	char result[SIZE];
	char operation;
} Integers, *Integers_h;


/*
 * Parses the string received from the client using strtok.
 * @return true if parsing is successful. Integers' field will be correctly allocated.
 * @return false if parsing is unsuccessful.
 */
bool parseStringOperation(const char* string, Integers_h integers);

/*
 * Mathematical operations.
 */

void add(Integers_h);

void sub(Integers_h);

void division(Integers_h);

void multi(Integers_h);


#endif /* Math_h */


#ifndef Socket_Utils_h
#define Socket_Utils_h
#include "Constants.h"

/*
 * Free allocated resources for the Windows Operating System.
 */

void clearWinsock(void);

/*
 * Prints a message error to stdout.
 */
void errorHandler(char *);


#endif /* Socket_Utils_h */

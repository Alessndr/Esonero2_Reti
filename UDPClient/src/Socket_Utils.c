#include "Socket_Utils.h"

/*
 *
 *Sends an error message on stdout
 *
 */

void errorHandler(char *errorMessage) {
	printf("%s", errorMessage);
}

void clearWinsock(void){
#if defined WIN32
	WSACleanup();
#endif
}





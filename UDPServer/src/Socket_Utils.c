#include "Socket_Utils.h"


void errorHandler(char *errorMessage) {
	printf("%s", errorMessage);
}


void clearWinsock(void){
#if defined WIN32
	WSACleanup();
#endif
}

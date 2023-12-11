/*
 * This file encapsulates all common libraries that are used throughout the execution,
 * including optional libraries that are included based on the OS.
 */

#ifndef Constants_h
#define Constants_h

#if defined WIN32
#include <winsock.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#define closesocket close
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 * Creating aliases for readability.
 */

typedef struct sockaddr_in* socketAddress_h;

typedef struct sockaddr_in socketAddress;

typedef struct sockaddr* genericSocketAddress;



#endif /* Constants_h */

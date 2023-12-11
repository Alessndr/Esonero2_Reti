#include "Protocol.h"
#include "Socket_Utils.h"
#include "Constants.h"

#define DEFAULT_SERVER "localhost"

int main(int argc, const char * argv[]) {
#if defined WIN32
	// Initialize Winsock
	WSADATA wsa_data;
	int result = WSAStartup(MAKEWORD(2,2), &wsa_data);
	if (result != 0) {
		printf("Error at WSAStartup()\n");
		return 0;
	}
#endif

	const char *server; //server name
	int port;			//server port

	if (argc == 2) { /* command line argument format sample: server.di.uniba.it:56700 */
		server = strtok((char *)argv[1], ":");
		char *portStr = strtok(NULL, ":");
		if (portStr != NULL) {
			port = atoi(portStr);
		}else{
			fprintf(stderr, "Invalid port\n");
			return EXIT_FAILURE;
		}
	} else if(argc > 2){
		fprintf(stderr, "Too many arguments: %d\n", argc);
		return EXIT_FAILURE;
	}else{	/* argc == 1: default server and port are used */
		server = DEFAULT_SERVER;	//localhost
		port = PROTO_PORT;			//protocol port in "Protocol.h"
	}


	struct hostent *host = gethostbyname(server);
	if (host == NULL){
		errorHandler("Error getting host\n");
		clearWinsock();
		return EXIT_FAILURE;
	}

	printf("Server name: %s (IP: %s, port: %d)\n", server,
			inet_ntoa(*(struct in_addr *)host->h_addr),
			PROTO_PORT);

	socketAddress serverAddress;
	unsigned int serverAddress_len = sizeof(serverAddress);
	long messageRcvSize;

	/* create a UDP socket */

	int UDPSocket;

	if ((UDPSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		errorHandler("Error creating socket");
		clearWinsock();
		return EXIT_FAILURE;
	}

	/* set the server address */
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr = *((struct in_addr *)host->h_addr);

	char buffer[BUFFER_SIZE];

	while(1){
		printf("\n%s",
				"You can do 4 operations with two integers:"
				"\n1. + to add"
				"\n2. - to subtract"
				"\n3. / to divide"
				"\n4. x to multiply"
				"\n5. = to end\n\n");

		/*
		 * Resetting buffer to correctly put information inside.
		 */

		memset(buffer, 0, BUFFER_SIZE);

		printf("Enter the string (e.g. + 24 32): ");
		if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
			char *newline = strchr(buffer, '\n');
			if (newline != NULL) {
				*newline = '\0';
			}
		}

		/* checking if client wants to stop sending messages to server */

		if(buffer[0] == '='  && strlen(buffer) == 1)
			break;

		/*
		 * Sending string to server
		 */

		if (sendto(UDPSocket, buffer, strlen(buffer), 0,
				(struct sockaddr *)&serverAddress,
				sizeof(serverAddress))
				!= strlen(buffer)){
			errorHandler("sendto() sent a different number of bytes than expected");
			closesocket(UDPSocket);
			clearWinsock();
			return EXIT_FAILURE;
		}

		/*
		 * Resetting buffer to correctly put information inside.
		 */

		memset(buffer, 0, BUFFER_SIZE);

		/* Receiving response from server */

		if ((messageRcvSize = recvfrom(UDPSocket, buffer, BUFFER_SIZE, 0,
				(genericSocketAddress)&serverAddress,
				&serverAddress_len))
				< 0){
			errorHandler("recvfrom() failed");
			closesocket(UDPSocket);
			clearWinsock();
			return EXIT_FAILURE;
		}

		/* print the received message */
		printf("\nReceived result from server %s, IP: %s: %s\n\n",
				server,	//server name
				inet_ntoa(*(struct in_addr *)host->h_addr), //server address
				buffer); //response
	}
		printf("\n= means goodbye!\n");
		closesocket(UDPSocket);
		clearWinsock();
		return 0;
}

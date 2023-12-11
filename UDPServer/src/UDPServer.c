#include "Protocol.h"
#include "Socket_Utils.h"
#include "Math.h"

#define DEFAULT_ADDRESS "127.0.0.1"

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

	/* create a UDP socket */
	int UDPSocket;

	if ((UDPSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		errorHandler("Error creating socket");
		clearWinsock();
		return EXIT_FAILURE;
	}

	/* prepare client address */

	socketAddress clientAddress;
	unsigned int clientAddress_len = sizeof(clientAddress);


	/* set server address */
	socketAddress serverAddress;
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PROTO_PORT);
	serverAddress.sin_addr.s_addr = inet_addr(DEFAULT_ADDRESS);


	/* binding process */
	if ((bind(UDPSocket, (genericSocketAddress)&serverAddress,
			  sizeof(serverAddress))) < 0){
		errorHandler("bind() failed");
		closesocket(UDPSocket);
		clearWinsock();
		return EXIT_FAILURE;
	}

	char buffer[BUFFER_SIZE];
	long messageRcvSize;


	while (1){
		/* successful bind: server starts listening*/

		puts("\nServer listening...");
		/* clean buffer */
		memset(buffer, 0, BUFFER_SIZE);



		/* receive message from client */
		if ((messageRcvSize = recvfrom(UDPSocket, buffer, BUFFER_SIZE, 0,
									   (genericSocketAddress)&clientAddress, &clientAddress_len)) < 0){
			errorHandler("recvfrom() failed");
			closesocket(UDPSocket);
			clearWinsock();
			return EXIT_FAILURE;
		}


		struct hostent *client_host = gethostbyaddr((char *)&clientAddress.sin_addr.s_addr,
													sizeof(clientAddress.sin_addr), AF_INET);

		if (client_host == NULL){
			perror("Error resolving client's IP address");
			exit(EXIT_FAILURE);
		}

		printf("Requested operation: '%s' from client %s, IP %s\n",
			   buffer,
			   (client_host->h_name != NULL) ? client_host->h_name
					   	   	   	   	   	   	   : "Unknown host name",
			   inet_ntoa(clientAddress.sin_addr));

		Integers integers;
		/* clean structure */
		memset(&integers, 0, sizeof(Integers));
		/*
		 * Starting parsing process.
		 * See Math.h/Math.c
		 */
		bool parseSuccess = parseStringOperation(buffer,&integers);

		/*
		 * Resetting buffer to correctly put information inside.
		 */

		memset(buffer, 0, BUFFER_SIZE);
		if(parseSuccess){
			switch(integers.operation){
				case '+':
					add(&integers);
					break;
				case '/':
					division(&integers);
					break;
				case 'x':
					multi(&integers);
					break;
				case '-':
					sub(&integers);
					break;
			}

			strcpy(buffer, integers.result);
		}else
		/*
		 * Handling ParsingException: this message will be sent to the Client
		 */
			strcpy(buffer, "ParsingException: string format not recognized!");


		if (sendto(UDPSocket, buffer, strlen(buffer), 0,
				   (struct sockaddr *)&clientAddress, sizeof(clientAddress))
					!= strlen(buffer)){
			errorHandler("sendto() sent a different number of bytes than expected");
			closesocket(UDPSocket);
			clearWinsock();
			return EXIT_FAILURE;
		}
	}
	/*
	 * Under normal circumstances, this block of code will not be executed, because
	 * the Server will keep listening endlessly unless shutdown directly from an
	 * Administrator.
	 */

	closesocket(UDPSocket);
	clearWinsock();
	return 0;
}

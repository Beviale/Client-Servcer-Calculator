/*
 * tcp.c
 *
 *  Created on: 20 nov 2022
 *  Author: Alessandro Bevilacqua
 */


#include "tcp.h"

// Prints error message.
void errorhandler(const char *error_message)
{
    printf("%s", error_message);
}


void clearwinsock()
{
    #if defined WIN32
    WSACleanup();
    #endif
}

// Connects client to server. Accepts the client socket descriptor and Server IP address.
bool connect_to_server(int socket, const char* indirizzo)
{
	   struct sockaddr_in sad;
	   memset(&sad, 0, sizeof(sad));
	   sad.sin_family=AF_INET;
	   sad.sin_addr.s_addr = inet_addr(indirizzo); // Server IP address.
	   sad.sin_port = htons(PROTOPORT); // Server port number.
	   if(connect(socket, (struct sockaddr *)&sad, sizeof(sad))<0)
	   {
		   errorhandler("\nFailed to connect.\n");
		   closesocket(socket);
		   clearwinsock();
	       return 0;
	   }
	   return 1;
}


// Sends data from one host to another. Accepts the socket descriptor and the string.
void send_data(int socket, char *data)
{
	if(send(socket, data, (strlen(data)+1)*sizeof(char), 0)!=(strlen(data)+1)*sizeof(char))
	{
		errorhandler("\nSend() sent a different number of bytes than expected");
		closesocket(socket);
		clearwinsock();
		return;
	}
	return;
}





bool wsadata()
{
    #if defined WIN32
    WSADATA wsa_data;
    int result = WSAStartup(MAKEWORD(2,2), &wsa_data);
    if(result!=0)
    {
        printf("\nError at WSAStartup\n");
        return 0;
    }
    #endif
    return 1;
}



// Assigns IP address and port number to the welcome socket.
bool assign_address_wsocket(int socket, const char* address)
{
	struct sockaddr_in sad;
	memset(&sad, 0, sizeof(sad)); // Ensures that extra byte contain 0.
	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = inet_addr(address);
	sad.sin_port = htons(PROTOPORT); /* Converts values between the host and
		network byte order. Specifically, htons() converts 16-bit quantities
		from host byte order to network byte order. */
	if(bind(socket, (struct sockaddr*)&sad, sizeof(sad))<0)
	{
		errorhandler("\nBind() failed.\n");
		closesocket(socket);
		clearwinsock();
		return 0;
	}
	return 1;
}


// Sets the server to the listening state.
bool set_listen(int socket)
{
	if(listen(socket, QLEN)<0)
	{
		errorhandler("\nListen() failed.\n");
		closesocket(socket);
		clearwinsock();
		return 0;
	}
	return 1;
}


float divi(float first, float second)
{
	return first/second;
}


float add(float first, float second)
{
	return first+second;
}

float sub(float first, float second)
{
	return first-second;
}

float mul(float first, float second)
{
	return first*second;
}

// Sends operands and operator from the client to the server.
void send_operation(int socket, float op1, float op2, char operator)
{
	char number1[BUFFERSIZE]; // String containing the first operand.
	char number2[BUFFERSIZE]; // String containing the second operand
	char convert_operator[2]; // String containing the operator and '\0'.
	snprintf(number1, BUFFERSIZE-1, "%.2f", op1); // Converts from float to string.
	printf("\nThe first number you entered is: %s", number1);
	send_data(socket, number1);
	snprintf(number2, BUFFERSIZE-1, "%.2f", op2); // Converts from float to string.
	printf("\nThe second number you entered is: %s", number2);
	send_data(socket, number2);
	convert_operator[0]=operator; // Defines a character as a string.
	convert_operator[1]='\0';
	send_data(socket, convert_operator);
}





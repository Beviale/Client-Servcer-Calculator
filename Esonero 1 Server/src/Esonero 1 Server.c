#include "../../Librerie TCP/src/tcp.h"


int main()
{
	if(wsadata()==0)
	{
		system("pause");
		return -1;
	}
	int welcome_socket; // Welcome socket descriptor.
	welcome_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // Welcome socket initialization.
	if(welcome_socket<0)
    {
		errorhandler("\nSocket creation failed.\n");
		clearwinsock();
		system("pause");
		return -1;
	}
	if(assign_address_wsocket(welcome_socket, "127.0.0.1")==0)
	{
		system("pause");
		return -1;
	}
	if(set_listen(welcome_socket)==0) // The server is listening.
	{
		system("pause");
		return -1;
	}
	// Accept connections
	struct sockaddr_in cad; // Structure for the client address.
	int client_socket; // Socket descriptor for the client.
	int client_len; // The size of the client address.
	printf("\nWaiting for a client to connect...");
	while(1)
	{
		client_len=sizeof(cad); // Sets the size of the client address;
		if((client_socket = accept(welcome_socket,(struct sockaddr*)&cad, &client_len)) < 0)
		{
			errorhandler("\nAccept() failed");
			closesocket(client_socket);
			clearwinsock();
			system("pause");
			break;
		}
		printf("\nConnection established with %s:%d\n", inet_ntoa(cad.sin_addr), ntohs(cad.sin_port)); // Prints IP address and port number of the client.
		char received_string[BUFFERSIZE]; // String received from the client.
	    memset(received_string, 0, BUFFERSIZE);
		float op1=0; // First operand.
		float op2=0; // Second operand.
		char operator; // OPperator.
		char *error="\nMissing or incorrect data!"; // Error message for incorrect operator or division by zero.
		char result[BUFFERSIZE]; // Operation result.
		int i=1; // Counter to print the results.
		while(1)
		{
			if(recv(client_socket, received_string, BUFFERSIZE-1, 0)>0)
			{
				op1=atof(received_string); // Converts the string of the first operand to a float value.
				if(recv(client_socket, received_string, BUFFERSIZE-1, 0)>0)
				{
					op2=atof(received_string); // Converts the string of the second operand to a float value.
					if(recv(client_socket, received_string, BUFFERSIZE-1, 0)>0)
					{
						operator=received_string[0]; // received_string[0] is the operator while received_string[1] is '\0'.
						switch (operator)
						{
							case '+':
							   snprintf(result, BUFFERSIZE-1, "%.2f", add(op1, op2)); // Converts float to string for addition.
							   printf("\n%u^ result=%s", i++, result); // Prints the operation result.
							   send_data(client_socket, result); // Sends the operation result for addition.
							   break;
							case 'x' : case 'X':
								snprintf(result, BUFFERSIZE-1, "%.2f", mul(op1, op2)); // Converts float to string for multiplication.
								printf("\n%u^ result=%s", i++, result); // Prints the operation result.
							    send_data(client_socket, result); // Sends the operation result for multiplication.
							   break;
							case '-':
								snprintf(result, BUFFERSIZE-1, "%.2f", sub(op1, op2)); // Converts float to string for subtraction.
								printf("\n%u^ result=%s", i++, result);  // Prints the operation result.
							    send_data(client_socket, result); // Sends the operation result for subtraction.
							   break;
							case '/':
							   if(op2==0)
							   {
								   send_data(client_socket, error); // Sends error if the second operand of the division is zero.
								   break;
							   }
							   snprintf(result, BUFFERSIZE-1, "%.2f", divi(op1, op2)); // Converts float to string for division.
							   printf("\n%u^ result=%s", i++, result); // Prints the operation result.
							   send_data(client_socket, result); // Sends the operation result for division.
							   break;
							default:
								send_data(client_socket, error); // Sends error if the operator is incorrect.
							break;
						}// end switch.
					} // end if operator.

				} // end if number2.

			}//end if number1.

		} // end while: receive data from the client.

	} // end while: accept connections.
} // end main.

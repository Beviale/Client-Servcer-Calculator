#include "../../Librerie TCP/src/tcp.h"


int main()
{
	if(wsadata()==0)
	{
		system("pause");
		return -1;
	}
	int c_socket; // Socket descriptor.
	c_socket= socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // Socket initialization.
	if(c_socket<0)
	{
		errorhandler("\nSocket creation failed.\n");
		clearwinsock();
		system("pause");
		return -1;
	}
	if(connect_to_server(c_socket, "127.0.0.1")==0)
	{
		system("pause");
		return -1;
	}
	printf("\nConnected to the server!");
	float op1=0; // First operand.
	float op2=0; // Second operand.
	char operator; // Operator.
	while(1) // loop
	{
		printf("\nEnter operator and operands in the format OperatorspaceOperand1spaceOperand2: ");
		fflush(stdin);
		if(scanf("%c %f %f", &operator, &op1, &op2)!=3) // The scanf() function returns the number of fields that were successfully converted and assigned.
		{
			printf("\nScanf() Error!");
			system("pause");
			continue;
		}
		if(operator=='=')
		{
			printf("\nYou chose to exit.");
			system("pause");
			return 0;
		}
		send_operation(c_socket, op1, op2, operator); // Sends operands and operator to the server.
		char received_result[BUFFERSIZE]; // Operation result.
		if(recv(c_socket, received_result, BUFFERSIZE-1, 0)>0)
		{
			printf("\nThe result of operation is: %s", received_result);
		}
	}
}




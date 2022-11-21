/*
 * tcp.h
 *
 *  Created on: 20 nov 2022
 *  Author: Alessandro Bevilacqua
 */

#ifndef TCP_H_
#define TCP_H_

#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 512
#define PROTOPORT 57015 // Default port number.
#define QLEN 5 // Size of request queue.



// For Client and Server
void errorhandler(const char *error_message);
void clearwinsock();
bool wsadata();
void send_data(int, char*);


// For Client
bool connect_to_server(int, const char *);
void send_operation(int, float, float, char);

// For Server
bool assign_address_wsocket(int, const char*);
bool set_listen(int);


// Available operations
float add(float, float);
float divi(float, float);
float sub(float, float);
float mul(float, float);





#endif /* TCP_H_ */

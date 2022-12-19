# Client-Server-Calculator
<b>Development and implementation of a TCP client/server application written in c language, where the server is a basic remote calculator that responds to client requests. </b>

<i>This is a university project of the computer networks course.</i>

To run the server follow the path below:"Esonero 1 Server/Debug/Esonero1server.exe".
To run the client follow the path below:"Esonero 1 Client/Debug/Esonero1Client.exe".

1) Once started, the client automatically establishes the connection to the server (on the default port and address). <br>
2) Once the connection is received, the server displays the client's address and port number on the standard output, writing "Connection established with xxx.xxx.xxx.xxx:yyyyy". <br>
3) Once the connection has been established, the client reads the operation to be performed (using the characters +, x, -, /, respectively for Addition, Multiplication, Subtraction and Division) and two integers from the standard input (e.g. + 23 45) and sends to the server what is read from the keyboard. <br>
4) The server reads what is sent by the client, performs the requested operation and sends the result to the client (e.g. 68). <br>
5) The client reads the response sent by the server and displays it on the standard output. <br>
6) The client reads the next operation to be performed from the standard input. <br>
7) If the character = is entered instead of an operation, the client closes the connection with the server and terminates its process here; otherwise, go back to step 3. <br>
8) The server never terminates its process and must be able to accept a maximum queue of 5 clients (parameter qlen).

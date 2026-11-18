int ReceiveSocketData(int socket, char* buffer)
{
 int bytesRecvd = 0;

 bytesRecvd = recv(socket, buffer, 1023, 0);

 return bytesRecvd;
}
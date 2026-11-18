int write_sock(int sockhandle, char *buf, int length)
{
 int byte_send;
 byte_send = write(sockhandle, buf, length);
 return (length - byte_send);
}
int sendline(int sock, char *buffer, int size)
{
 write(sock, buffer, size);
 return size;
}
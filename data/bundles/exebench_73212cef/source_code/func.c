
int sendline(int port, unsigned char *data, int len)
{

 write(port, data, len);


 return len;
}

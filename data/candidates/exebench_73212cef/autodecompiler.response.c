int sendline(int port, char *buf, int len)
{
 write(port, buf, len);
 return len;
}
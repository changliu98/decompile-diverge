int serial_write(int port, char *buf, int len)
{
 write(port, buf, len);
 return len;
}
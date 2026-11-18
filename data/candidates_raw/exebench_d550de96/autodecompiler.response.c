int serial_send(int fd, char *buf, int len)
{
 write(fd, buf, len);
 return 0;
}
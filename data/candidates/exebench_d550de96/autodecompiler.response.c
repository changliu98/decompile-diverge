int sendbytes(int fd, char *buf, int len)
{
 write(fd, buf, len);
 return 0;
}
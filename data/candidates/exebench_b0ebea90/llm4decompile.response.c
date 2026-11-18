int sendcw(int fd, unsigned char *buff)
{
 if (send(fd, buff, 18, 0) == -1) {
  syslog(3, "ca.so: Send cw failed %d", *__errno_location());
  return 0;
 }
 return 1;
}
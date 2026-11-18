int serial_write(int fd, int len, char *buf)
{
 int ret = 0;
 int bytes = 0;

 ret = write(fd, buf, len);
 if ((ret == -1) || (ret != len))
 {
  bytes = -1;
 }
 else
 {
  bytes = ret;
 }

 return bytes;
}
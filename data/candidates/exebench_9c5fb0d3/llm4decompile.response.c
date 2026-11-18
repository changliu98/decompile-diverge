int write_data(int fd, char *buf, int size)
{
 int cur = 0;
 int ret;
 while (cur != size) {
  ret = write(fd, buf + cur, size - cur);
  if (ret <= 0)
   return -1;
  cur += ret;
 }
 return 0;
}
int read_data(int fd, void *buf, int size)
{
 int ret;
 int cur = 0;
 while (cur != size) {
  ret = read(fd, (char *)buf + cur, size - cur);
  if (ret <= 0)
   return -1;
  cur += ret;
 }
 return 0;
}
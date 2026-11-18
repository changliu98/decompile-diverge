int read_data(int fd, char *buf, int size)
{
 int ret;
 int len = 0;

 while (1) {
  if (len == size)
   break;

  ret = read(fd, buf + len, size - len);

  if (ret <= 0) {
   ret = -1;
   goto out;
  }

  len += ret;
 }

out:
 return ret;
}
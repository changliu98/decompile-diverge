int read_data(int fd, char *buf, int buf_len)
{
 int size;
 int left_len;
 char *p;

 p = buf;
 left_len = buf_len;

 if (fd < 0)
  return -1;

 while (left_len) {
  size = read(fd, p, left_len);
  if (size <= 0)
   return -1;

  p += size;
  left_len -= size;
 }

 return buf_len;
}
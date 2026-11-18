int write_buff(int fd, unsigned char *data, ssize_t size)
{
 char *ptr = data;
 ssize_t n;
 ssize_t sz = size;

 while (sz > 0) {
  n = write(fd, ptr, sz);
  if (n < 0)
   return -1;
  sz -= n;
  ptr += n;
 }
 return size;
}
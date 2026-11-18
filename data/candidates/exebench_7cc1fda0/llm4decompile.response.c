int write_buff(int fd, char *data, ssize_t size)
{
 ssize_t ret;
 ssize_t sz = size;
 char *ptr = data;

 while (sz > 0) {
  ret = write(fd, ptr, sz);
  if (ret < 0)
   return -1;
  sz -= ret;
  ptr += ret;
 }

 return size;
}
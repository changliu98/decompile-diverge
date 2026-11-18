int write_buff(int fd, char *buf, size_t len)
{
 ssize_t ret;
 ssize_t todo = len;
 char *ptr = buf;

 while (1) {
  if (todo > 0) {
   ret = write(fd, ptr, todo);
   if (ret < 0) {
    ret = -1;
    break;
   }
   todo -= ret;
   ptr += ret;
  } else {
   ret = len;
   break;
  }
 }

 return ret;
}
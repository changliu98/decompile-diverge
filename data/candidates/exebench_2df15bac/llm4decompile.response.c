int force_write(int fd, char *buf, int sz)
{
 int got = 0;
 int ret;

 while (sz > 0) {
  ret = write(fd, buf, sz);
  if (ret <= 0)
   break;
  got += ret;
  buf += ret;
  sz -= ret;
 }

 return got;
}
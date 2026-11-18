int read_all(int fd, char *buf, int count)
{
 int got;

 do {
  got = read(fd, buf, count);
  if (got > 0) {
   buf += got;
   count -= got;
  }
 } while (got > 0 && count > 0);

 return got;
}
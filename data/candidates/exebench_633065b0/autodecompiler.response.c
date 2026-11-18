int read_data(int sock, char * buffer, int length)
{
 char * p = buffer;
 unsigned left = length;
 int ret;

 if (sock < 0) {
  ret = -1;
  goto out;
 }

 while (left > 0) {
  ret = read(sock, p, left);
  if (ret <= 0) {
   ret = -1;
   goto out;
  }
  p += ret;
  left -= ret;
 }

 ret = length - left;
out:
 return ret;
}
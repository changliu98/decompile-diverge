int read_socket(int sock, char * buffer, int len)
{
 int bytes_read = -1;
 int tries = 0;
 int left = len;
 char * ptr = buffer;
 do {
  bytes_read = read(sock, ptr, left);
  if(bytes_read > 0) {
   ptr += bytes_read;
   left -= bytes_read;
  }
  tries++;
  if(tries > 10000) {
   ret = -1;
   goto out;
  }
 } while(left > 0);
 ret = left;
out:
 return ret;
}
int
read_sock (int sockhandle, unsigned char *buf, int length)
{
  int byte_read = -1;
  unsigned char *ptbuf =buf;
  int mlength = length;
  int i = 0;
  do {
  byte_read = read (sockhandle, ptbuf,mlength);
  if (byte_read > 0){
   ptbuf = ptbuf+byte_read;
   mlength = mlength-byte_read;

  }

 i++;

 if(i > 10000) return -1;
  } while (mlength > 0);
  return (mlength);
}
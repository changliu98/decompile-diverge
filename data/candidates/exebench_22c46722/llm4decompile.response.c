int read_sock(int sockhandle,char *buf,int length)
{
  int byte_read;
  int length_local;
  char *buf_local;
  int sockhandle_local;
  int count=0;

  sockhandle_local = sockhandle;
  buf_local = buf;
  length_local = length;

  while(1) {

    byte_read = read(sockhandle_local,buf_local,length_local);

    if (byte_read > 0) {
      buf_local += byte_read;
      length_local -= byte_read;
    }

    count++;
    if (count > 10000) {
      return -1;
    }

    if (length_local <= 0) {
      break;
    }

  }

  return length_local;

}
int read_all(int sockhandle, char *buf, int length)
{
  int bytes_read = 0;
  int i = 0;
  do
  {
    bytes_read = read(sockhandle, buf, length);
    if (bytes_read > 0)
    {
      buf += bytes_read;
      length -= bytes_read;
    }
    i++;
    if (i > 10000)
      return -1;
  } while (length > 0);
  return length;
}
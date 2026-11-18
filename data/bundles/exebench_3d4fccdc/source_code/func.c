
int
write_sock (int sockhandle, unsigned char *buf, int length)
{
  int byte_send = -1;
  byte_send = write (sockhandle, buf, length);
  return (length - byte_send);
}

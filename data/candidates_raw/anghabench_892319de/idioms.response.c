char *get_header(char *buf)
{
  int i = 0;
  buf[i++] = 0x81;
  buf[i++] = 0x6a;
  buf[i++] = 0x00;
  buf[i++] = 0x00;
  buf[i++] = 0x00;
  buf[i++] = 0x01;
  buf[i++] = 0x00;
  buf[i++] = 0x00;
  buf[i++] = 0x00;
  return (char *) (buf + i);
}
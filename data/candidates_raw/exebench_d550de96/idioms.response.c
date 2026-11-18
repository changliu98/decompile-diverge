int i2c_write(int port, unsigned char *data, int len)
{
  write(port, data, len);
  return 0;
}
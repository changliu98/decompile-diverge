int write_to_port(int port, void *data, int len)
{
  write(port,data,len);
  return len;
}
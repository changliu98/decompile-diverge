int sendline(int port, void *data, int len)
{
  write(port,data,len);
  return len;
}
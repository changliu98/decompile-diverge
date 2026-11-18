int _socket_close_(int *fd)
{
  int temp = *fd;
  *fd = -1;
  return close(temp);
}
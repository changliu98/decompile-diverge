int close_connection(int *fd)
{
  int temp = *fd;
  *fd = -1;
  return close(temp);
}
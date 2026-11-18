void close_fd(int *fd)
{
  if (*fd >= 0)
    close(*fd);
  *fd = -1;
}
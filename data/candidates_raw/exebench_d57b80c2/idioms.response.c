int write_to_fd(int fd, int num, void *ptr)
{
  int ret = write(fd, ptr, num);
  if (ret == -1 || ret != num)
    return -1;
  return ret;
}
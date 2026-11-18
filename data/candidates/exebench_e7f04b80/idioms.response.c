int deo_pipe(int *r, int *w)
{
  int fd[2];
  if (pipe(fd))
    return (*__errno_location ());
  *r = fd[0];
  *w = fd[1];
  return (0);
}
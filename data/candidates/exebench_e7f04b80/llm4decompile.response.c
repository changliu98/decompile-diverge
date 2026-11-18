int deo_pipe(int *rend, int *wend)
{
  int fds[2];
  int err;

  err = pipe(fds);
  if (err) {
    return *__errno_location();
  }

  *rend = fds[0];
  *wend = fds[1];

  return 0;
}
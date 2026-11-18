int __cdecl deo_pipe(int *rend, int *wend)
{
  int pipefd[2];

  if (pipe(pipefd) != 0)
    return *__errno_location();

  *rend = pipefd[0]; // Read end of the pipe
  *wend = pipefd[1]; // Write end of the pipe

  return 0;
}
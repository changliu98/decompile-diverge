void __cdecl fork_child(int *fd_pipe, int *fd_in, int *i)
{
  close(fd_pipe[1]);
  *fd_in = *fd_pipe;
  ++*i;
}
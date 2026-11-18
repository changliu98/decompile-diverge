void fork_child(int *fd_pipe,int *fd_in,int *i)

{
  int *i_local;
  int *fd_in_local;
  int *fd_pipe_local;
  
  close(fd_pipe[1]);
  *fd_in = *fd_pipe;
  *i = *i + 1;
  return;
}
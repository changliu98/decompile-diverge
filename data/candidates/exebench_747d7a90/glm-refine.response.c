void __cdecl fork_child(int *fd_pipe, int *fd_in, int *i)
{
  // Close the write end of the pipe in the child process, 
  // as it only needs to read from it.
  close(fd_pipe[1]);

  // Assign the read end of the pipe to the input file descriptor
  *fd_in = fd_pipe[0];

  // Increment the execution counter/state index
  (*i)++;
}
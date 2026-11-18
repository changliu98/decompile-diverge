void fork_child(int pipe_fd[2], int *child_fd, int *child_count) {
  close(pipe_fd[1]);
  *child_fd = pipe_fd[0];
  (*child_count)++;
}
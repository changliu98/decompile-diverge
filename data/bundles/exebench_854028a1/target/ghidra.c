void closep(int *fd)

{
  int *fd_local;
  
  if (-1 < *fd) {
    close(*fd);
  }
  *fd = -1;
  return;
}
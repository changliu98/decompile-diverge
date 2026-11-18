int dupfd(int fd_src, int *fd_dst)
{
 int ret;

 if (fd_src == -1) {
  *fd_dst = -1;
  ret = 1;
 } else {
  *fd_dst = dup(fd_src);
  ret = (*fd_dst != -1) ? 0 : 1;
 }

 return ret;
}
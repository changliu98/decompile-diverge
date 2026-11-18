void ddelete_c(char *path, int *iostat)
{
  int ret;
  if (unlink(path) == 0)
    ret = 0;
  else
    ret = (*__errno_location ());
  *iostat = ret;
}
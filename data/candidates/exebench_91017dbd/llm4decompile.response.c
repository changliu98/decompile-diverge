void ddelete_c(char *path, int *iostat)
{
  int iostat_local;

  iostat_local = unlink(path);
  if (iostat_local != 0) {
    iostat_local = *__errno_location();
  }
  *iostat = iostat_local;
}
void __cdecl ddelete_c(char *path, int *iostat)
{
  *iostat = unlink(path) ? *__errno_location() : 0;
}
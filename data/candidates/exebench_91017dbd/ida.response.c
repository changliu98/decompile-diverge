void __cdecl ddelete_c(char *path, int *iostat)
{
  int v2; // [rsp+Ch] [rbp-14h]

  if ( unlink(path) )
    v2 = *__errno_location();
  else
    v2 = 0;
  *iostat = v2;
}
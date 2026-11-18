void __cdecl basename_discriminant(const char *filename, long *h, long *len)
{
  const char *v3; // rax
  char *stt; // [rsp+0h] [rbp-20h]
  const char *stta; // [rsp+0h] [rbp-20h]

  stt = strrchr(filename, 47);
  if ( stt )
    stta = stt + 1;
  else
    stta = filename;
  *len = 0LL;
  *h = 0LL;
  while ( *stta )
  {
    *h *= 33LL;
    v3 = stta++;
    *h += *v3;
    ++*len;
  }
}
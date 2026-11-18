int __cdecl replace(char *rps, char whatc, char toc)
{
  char *p1; // [rsp+8h] [rbp-18h]

  for ( p1 = strchr(rps, whatc); p1; p1 = strchr(p1 + 1, whatc) )
    *p1 = toc;
  return 0;
}
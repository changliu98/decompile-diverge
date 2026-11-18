char __cdecl last_char(char *ptr)
{
  char c; // [rsp+1h] [rbp-11h]
  char *ptra; // [rsp+2h] [rbp-10h]
  char *ptrb; // [rsp+2h] [rbp-10h]

  ptra = ptr;
  if ( !ptr || !*ptr )
    return 0;
  while ( *ptra )
    ++ptra;
  ptrb = ptra - 1;
  c = *ptrb;
  *ptrb = 0;
  return c;
}
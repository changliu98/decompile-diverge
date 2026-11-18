void __cdecl ck_encrypt(char *s)
{
  while ( *s )
  {
    if ( *s != 112 && *s != 92 && *s != 83 )
      *s ^= 0xFu;
    ++s;
  }
}
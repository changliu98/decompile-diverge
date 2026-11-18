void __cdecl insert_dle(unsigned __int8 *dest, unsigned __int8 *src, int count)
{
  unsigned __int8 *v4; // rax
  unsigned __int8 *v5; // rax
  unsigned __int8 *v6; // rax

  while ( count-- )
  {
    v4 = dest++;
    *v4 = *src;
    v5 = src++;
    if ( *v5 == DLE )
    {
      v6 = dest++;
      *v6 = DLE;
    }
  }
}
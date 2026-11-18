void __cdecl itoa_dec(unsigned int val, char *buf)
{
  unsigned int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 0xA; ++i )
  {
    if ( !val && i )
      buf[9 - i] = 32;
    else
      buf[9 - i] = itoa_dec_dectab[val % 0xA];
    val /= 0xAu;
  }
}
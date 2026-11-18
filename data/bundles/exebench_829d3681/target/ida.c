void __cdecl word2string(unsigned int value, char *buffer)
{
  int c; // [rsp+0h] [rbp-1Ch]
  char *p; // [rsp+4h] [rbp-18h]
  unsigned int valuea; // [rsp+18h] [rbp-4h]

  valuea = value;
  p = buffer;
  if ( value )
  {
    for ( c = 0; c < 5; ++c )
    {
      if ( &p[valuea / word2string__smth[c]] != buffer )
      {
        *p++ = valuea / word2string__smth[c] + 48;
        valuea %= word2string__smth[c];
      }
    }
    *(_WORD *)p = 32;
  }
  else
  {
    *(_DWORD *)buffer = 8240;
  }
}
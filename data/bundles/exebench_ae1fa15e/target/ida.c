unsigned int __cdecl render_uint32(unsigned int n, char *buff)
{
  unsigned int v2; // ecx
  unsigned int len; // [rsp+0h] [rbp-14h]
  unsigned int na; // [rsp+Ch] [rbp-8h]

  na = n;
  if ( n )
  {
    len = 0;
    while ( na )
    {
      v2 = len++;
      buff[v2] = a0123456789abcd[na & 0xF];
      na >>= 4;
    }
    return len;
  }
  else
  {
    *buff = 48;
    return 1;
  }
}
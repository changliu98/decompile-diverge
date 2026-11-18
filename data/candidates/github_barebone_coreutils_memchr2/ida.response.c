void *__cdecl memchr2(const void *s, int c1_in, int c2_in, size_t n)
{
  bool v5; // [rsp+Fh] [rbp-71h]
  const unsigned __int8 *char_ptr_0; // [rsp+10h] [rbp-70h]
  memchr2::longword repeated_c2a; // [rsp+28h] [rbp-58h]
  memchr2::longword repeated_c2; // [rsp+28h] [rbp-58h]
  unsigned __int64 repeated_c1a; // [rsp+30h] [rbp-50h]
  memchr2::longword repeated_c1; // [rsp+30h] [rbp-50h]
  const memchr2::longword *longword_ptr; // [rsp+40h] [rbp-40h]
  unsigned __int8 *void_ptr; // [rsp+50h] [rbp-30h]
  size_t na; // [rsp+60h] [rbp-20h]

  na = n;
  if ( (unsigned __int8)c1_in == (unsigned __int8)c2_in )
    return memchr(s, (unsigned __int8)c1_in, n);
  for ( void_ptr = (unsigned __int8 *)s; ; ++void_ptr )
  {
    v5 = 0;
    if ( na )
      v5 = ((unsigned __int8)void_ptr & 7) != 0LL;
    if ( !v5 )
      break;
    if ( *void_ptr == (unsigned __int8)c1_in || *void_ptr == (unsigned __int8)c2_in )
      return void_ptr;
    --na;
  }
  longword_ptr = (const memchr2::longword *)void_ptr;
  repeated_c2a = ((unsigned __int8)c2_in << 8) | (unsigned int)(unsigned __int8)c2_in;
  repeated_c1a = ((unsigned __int8)c1_in << 8) | (unsigned int)(unsigned __int8)c1_in | (unsigned __int64)((__int64)(((unsigned __int8)c1_in << 8) | (unsigned int)(unsigned __int8)c1_in) << 16);
  repeated_c1 = repeated_c1a | (repeated_c1a << 32);
  repeated_c2 = repeated_c2a | (repeated_c2a << 16) | ((repeated_c2a | (repeated_c2a << 16)) << 32);
  while ( na >= 8
       && ((~(repeated_c2 ^ *longword_ptr) & ((repeated_c2 ^ *longword_ptr) - 0x101010101010101LL) | ~(repeated_c1 ^ *longword_ptr) & ((repeated_c1 ^ *longword_ptr) - 0x101010101010101LL)) & 0x8080808080808080LL) == 0 )
  {
    ++longword_ptr;
    na -= 8LL;
  }
  char_ptr_0 = (const unsigned __int8 *)longword_ptr;
  while ( na )
  {
    if ( *char_ptr_0 == (unsigned __int8)c1_in || *char_ptr_0 == (unsigned __int8)c2_in )
      return (void *)char_ptr_0;
    --na;
    ++char_ptr_0;
  }
  return 0LL;
}
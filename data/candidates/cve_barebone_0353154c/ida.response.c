void __cdecl bit_write_UMC(Bit_Chain *dat, BITCODE_UMC val)
{
  BITCODE_UMC mask; // [rsp+10h] [rbp-30h]
  unsigned __int8 byte[5]; // [rsp+1Fh] [rbp-21h]
  int j; // [rsp+28h] [rbp-18h]
  int i; // [rsp+2Ch] [rbp-14h]
  BITCODE_UMC vala; // [rsp+30h] [rbp-10h]
  Bit_Chain *data; // [rsp+38h] [rbp-8h]

  data = dat;
  vala = val;
  mask = 127LL;
  i = 4;
  j = 0;
  while ( i >= 0 )
  {
    byte[i] = (mask & val) >> j;
    byte[i] |= 0x80u;
    mask <<= 7;
    --i;
    j += 7;
  }
  for ( i = 0; i < 4 && (byte[i] & 0x7F) == 0; ++i )
    ;
  if ( (byte[i] & 0x40) != 0 )
    --i;
  byte[i] &= ~0x80u;
  for ( j = 4; j >= i; --j )
    bit_write_RC(data, byte[j]);
}
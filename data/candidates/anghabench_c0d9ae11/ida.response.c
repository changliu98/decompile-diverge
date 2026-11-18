int __cdecl check_crc_flex(unsigned __int8 *cp, int size)
{
  unsigned __int8 *v3; // rsi
  unsigned __int16 crc; // [rsp+0h] [rbp-16h]
  int sizea; // [rsp+2h] [rbp-14h]

  sizea = size;
  crc = -1;
  if ( size < 3 )
    return -1;
  while ( sizea-- )
  {
    v3 = cp++;
    crc = *(_WORD *)(crc_flex_table + 2LL * (unsigned __int8)(*v3 ^ HIBYTE(crc))) ^ (crc << 8);
  }
  if ( crc == 28784 )
    return 0;
  else
    return -1;
}
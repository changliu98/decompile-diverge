uint16_t __cdecl crc_16(const unsigned __int8 *input_str, size_t num_bytes)
{
  const unsigned __int8 *v2; // rdx
  size_t a; // [rsp+8h] [rbp-28h]
  const unsigned __int8 *ptr; // [rsp+10h] [rbp-20h]
  uint16_t crc; // [rsp+1Eh] [rbp-12h]

  if ( (crc_tab16_init & 1) == 0 )
    init_crc16_tab();
  crc = 0;
  ptr = input_str;
  if ( input_str )
  {
    for ( a = 0LL; a < num_bytes; ++a )
    {
      v2 = ptr++;
      crc = crc_tab16[(unsigned __int8)(*v2 ^ crc)] ^ ((int)crc >> 8);
    }
  }
  return crc;
}
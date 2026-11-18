uint16_t __cdecl crc_sick(const unsigned __int8 *input_str, size_t num_bytes)
{
  size_t a; // [rsp+0h] [rbp-30h]
  const unsigned __int8 *ptr; // [rsp+8h] [rbp-28h]
  uint16_t short_p; // [rsp+16h] [rbp-1Ah]
  uint16_t short_c; // [rsp+18h] [rbp-18h]
  uint16_t crc; // [rsp+1Eh] [rbp-12h]
  uint16_t crca; // [rsp+1Eh] [rbp-12h]

  crc = 0;
  ptr = input_str;
  short_p = 0;
  if ( input_str )
  {
    for ( a = 0LL; a < num_bytes; ++a )
    {
      short_c = *ptr;
      if ( (crc & 0x8000) != 0 )
        crca = (2 * crc) ^ 0x8005;
      else
        crca = 2 * crc;
      crc = (short_p | short_c) ^ crca;
      short_p = short_c << 8;
      ++ptr;
    }
  }
  return ((unsigned __int8)crc << 8) | ((crc & 0xFF00) >> 8);
}
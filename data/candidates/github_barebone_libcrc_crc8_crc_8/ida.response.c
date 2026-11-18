uint8_t __cdecl crc_8(const unsigned __int8 *input_str, size_t num_bytes)
{
  const unsigned __int8 *v2; // rax
  const unsigned __int8 *ptr; // [rsp+0h] [rbp-28h]
  uint8_t crc; // [rsp+Fh] [rbp-19h]
  size_t a; // [rsp+10h] [rbp-18h]

  crc = 0;
  ptr = input_str;
  if ( input_str )
  {
    for ( a = 0LL; a < num_bytes; ++a )
    {
      v2 = ptr++;
      crc = sht75_crc_table[crc ^ *v2];
    }
  }
  return crc;
}
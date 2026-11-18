void __cdecl init_crcccitt_tab()
{
  uint16_t c; // [rsp+0h] [rbp-8h]
  uint16_t crc; // [rsp+2h] [rbp-6h]
  uint16_t j; // [rsp+4h] [rbp-4h]
  uint16_t i; // [rsp+6h] [rbp-2h]

  for ( i = 0; i < 0x100u; ++i )
  {
    crc = 0;
    c = i << 8;
    for ( j = 0; j < 8u; ++j )
    {
      if ( ((c ^ crc) & 0x8000) != 0 )
        crc = (2 * crc) ^ 0x1021;
      else
        crc *= 2;
      c *= 2;
    }
    crc_tabccitt[i] = crc;
  }
  crc_tabccitt_init = 1;
}
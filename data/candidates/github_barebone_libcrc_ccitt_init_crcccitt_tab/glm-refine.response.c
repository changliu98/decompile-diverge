void __cdecl init_crcccitt_tab()
{
  uint16_t i;
  uint16_t j;

  for ( i = 0; i < 0x100; ++i )
  {
    // Initialize CRC with the current index shifted to the high byte
    uint16_t crc = i << 8;

    for ( j = 0; j < 8; ++j )
    {
      // If the MSB is set, shift left and XOR with the CCITT polynomial
      if ( crc & 0x8000 )
        crc = (crc << 1) ^ 0x1021;
      else
        crc <<= 1;
    }
    crc_tabccitt[i] = crc;
  }
  crc_tabccitt_init = 1;
}
void init_crcccitt_tab()
{
  unsigned short i; unsigned short j;
  unsigned short c; unsigned short crc;
  for (i = 0; i < 256; i++)
  {
    crc = 0;
    c = i << 8;
    for (j = 0; j < 8; j++)
    {
      if ((crc ^ c) & 0x8000)
        crc = (crc << 1) ^ 0x1021;
      else
        crc = (crc << 1);
      c = c << 1;
    }
    crc_tabccitt[i] = crc;
  }
  crc_tabccitt_init = 1;
}
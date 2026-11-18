uint16_t crc_16(uchar *input_str,size_t num_bytes)

{
  size_t a;
  uchar *ptr;
  uint16_t crc;
  size_t num_bytes_local;
  uchar *input_str_local;
  
  if (!crc_tab16_init) {
    init_crc16_tab();
  }
  crc = 0;
  if (input_str != (uchar *)0x0) {
    ptr = input_str;
    for (a = 0; a < num_bytes; a = a + 1) {
      crc = crc >> 8 ^ crc_tab16[(int)((ushort)(crc ^ *ptr) & 0xff)];
      ptr = ptr + 1;
    }
  }
  return crc;
}
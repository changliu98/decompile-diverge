uint16_t crc_kermit(uchar *input_str,size_t num_bytes)

{
  size_t a;
  uchar *ptr;
  uint16_t high_byte;
  uint16_t low_byte;
  uint16_t crc;
  size_t num_bytes_local;
  uchar *input_str_local;
  
  if (!crc_tab_init) {
    init_crc_tab();
  }
  crc = 0;
  if (input_str != (uchar *)0x0) {
    ptr = input_str;
    for (a = 0; a < num_bytes; a = a + 1) {
      crc = crc >> 8 ^ crc_tab[(int)((ushort)(crc ^ *ptr) & 0xff)];
      ptr = ptr + 1;
    }
  }
  return crc >> 8 | crc << 8;
}
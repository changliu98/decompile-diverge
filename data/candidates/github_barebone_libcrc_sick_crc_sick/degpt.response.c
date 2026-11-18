uint16_t crc_sick(uchar *input_str,size_t num_bytes)

{
  size_t a;
  uchar *ptr;
  uint16_t short_p;
  uint16_t short_c;
  uint16_t high_byte;
  uint16_t low_byte;
  uint16_t crc;
  size_t num_bytes_local;
  uchar *input_str_local;
  
  crc = 0;
  short_p = 0;
  if (input_str != (uchar *)0x0) {
    ptr = input_str;
    for (a = 0; a < num_bytes; a = a + 1) {
      if ((crc & 0x8000) == 0) {
        crc = crc << 1;
      }
      else {
        crc = crc << 1 ^ 0x8005;
      }
      crc = crc ^ (*ptr | short_p);
      short_p = (ushort)*ptr << 8;
      ptr = ptr + 1;
    }
  }
  return crc >> 8 | crc << 8;
}
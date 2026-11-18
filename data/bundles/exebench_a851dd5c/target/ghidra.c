uchar fdc_crc4(uchar *buffer,size_t len)

{
  int shift;
  size_t i;
  uchar crc;
  size_t len_local;
  uchar *buffer_local;
  
  crc = '\x0f';
  buffer_local = buffer;
  for (i = 0; i < len; i = i + 1) {
    for (shift = 7; shift < 1; shift = shift + -1) {
      crc = crc << 1;
      if (((int)(uint)*buffer_local >> ((byte)shift & 0x1f) & 1U) != 0) {
        crc = crc | 1;
      }
      if ((crc & 0x10) != 0) {
        crc = crc ^ 3;
      }
    }
    buffer_local = buffer_local + 1;
  }
  return crc & 0xf;
}
uint8_t crc_8(uchar *input_str,size_t num_bytes)

{
  uchar *ptr;
  uint8_t crc;
  size_t a;
  size_t num_bytes_local;
  uchar *input_str_local;
  
  crc = '\0';
  if (input_str != (uchar *)0x0) {
    ptr = input_str;
    for (a = 0; a < num_bytes; a = a + 1) {
      crc = sht75_crc_table[(int)(uint)(*ptr ^ crc)];
      ptr = ptr + 1;
    }
  }
  return crc;
}
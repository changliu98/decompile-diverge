char *__cdecl dlfb_dummy_render(char *buf)
{
  // 0xAF is the two's complement representation of -81 for a signed char
  buf[0] = 0xAF;
  buf[1] = 0x6A; // 106 in hex
  buf[2] = 0x00;
  buf[3] = 0x00;
  buf[4] = 0x00;
  buf[5] = 0x01;
  buf[6] = 0x00;
  buf[7] = 0x00;
  buf[8] = 0x00;
  
  return buf + 9;
}
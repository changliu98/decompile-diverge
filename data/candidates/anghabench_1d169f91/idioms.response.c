int dv_write_ssyb_id(unsigned char syb_num, unsigned char fr, unsigned char *buf)
{
  if (syb_num == 0 || syb_num == 6)
    buf[0] = (fr << 7) | 0x0f;
  else if (syb_num == 11)
    buf[0] = (fr << 7) | 0x7f;
  else
    buf[0] = (fr << 7) | 0x0f;
  buf[1] = (syb_num & 0x0f) | 0xf0;
  buf[2] = 0xff;
  return 3;
}
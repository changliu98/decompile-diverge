int dv_write_ssyb_id(uint8_t syb_num, uint8_t fr, uint8_t *buf)
{
 if (syb_num == 0 || syb_num == 6)
  buf[0] = 0x0f | (fr << 7);
 else if (syb_num == 11)
  buf[0] = 0x7f | (fr << 7);
 else
  buf[0] = 0x0f | (fr << 7);

 buf[1] = 0xf0 | (syb_num & 0x0f);
 buf[2] = 0xff;

 return 3;
}
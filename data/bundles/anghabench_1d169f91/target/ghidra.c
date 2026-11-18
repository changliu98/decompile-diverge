int dv_write_ssyb_id(uint8_t syb_num,uint8_t fr,uint8_t *buf)

{
  uint8_t *buf_local;
  uint8_t fr_local;
  uint8_t syb_num_local;
  
  if ((syb_num == '\0') || (syb_num == '\x06')) {
    *buf = fr << 7 | 0xf;
  }
  else if (syb_num == '\v') {
    *buf = fr << 7 | 0x7f;
  }
  else {
    *buf = fr << 7 | 0xf;
  }
  buf[1] = syb_num & 0xf | 0xf0;
  buf[2] = 0xff;
  return 3;
}
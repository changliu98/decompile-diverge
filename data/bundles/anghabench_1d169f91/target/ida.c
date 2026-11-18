int __cdecl dv_write_ssyb_id(uint8_t syb_num, uint8_t fr, uint8_t *buf)
{
  uint8_t v3; // cl

  if ( syb_num && syb_num != 6 )
  {
    if ( syb_num == 11 )
      v3 = (fr << 7) | 0x7F;
    else
      v3 = (fr << 7) | 0xF;
    *buf = v3;
  }
  else
  {
    *buf = (fr << 7) | 0xF;
  }
  buf[1] = syb_num & 0xF | 0xF0;
  buf[2] = -1;
  return 3;
}
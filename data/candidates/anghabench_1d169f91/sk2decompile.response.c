int dv_write_ssyb_id(unsigned char id, unsigned char type,
                     unsigned char* buf) {
  if (id == 0 || id == 6)
    buf[0] = 0x0f | (type << 7);
  else if (id == 11)
    buf[0] = 0x7f | (type << 7);
  else
    buf[0] = 0x0f | (type << 7);
  buf[1] = 0xf0 | (id & 0x0f);
  buf[2] = 0xff;
  return 3;
}
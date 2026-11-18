char * dlfb_dummy_render(char *buf)

{
  char *buf_local;
  
  *buf = -0x51;
  buf[1] = 'j';
  buf[2] = '\0';
  buf[3] = '\0';
  buf[4] = '\0';
  buf[5] = '\x01';
  buf[6] = '\0';
  buf[7] = '\0';
  buf[8] = '\0';
  return buf + 9;
}
char *__cdecl dlfb_dummy_render(char *buf)
{
  *buf = -81;
  buf[1] = 106;
  buf[2] = 0;
  buf[3] = 0;
  buf[4] = 0;
  buf[5] = 1;
  buf[6] = 0;
  buf[7] = 0;
  buf[8] = 0;
  return buf + 9;
}
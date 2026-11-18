static char locateSOFMarker()
{
  char c;
  char ret;
  ret = get_key_init();
  if (ret != 0)
    return (ret);
  ret = get_key_char(&c);
  if (ret != 0)
    return (ret);
  switch (c) {
  case 0xc0:
    ret = get_key_ext();
    if (ret == 0)
      ret = 0;
    else
      c = ret;
    break;
  case 0xc2:
    c = 0x25;
    break;
  case 0xc9:
    c = 0x11;
    break;
  default:
    c = 0x14;
    break;
  }
  return (c);
}
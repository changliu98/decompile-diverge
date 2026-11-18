int utf8_decode(int *ch, char *str)
{
  if ( (str[0] & 0x80) == 0 ) {
    *ch = (str[0] & 0xff);
    return 1;
  }
  if ( (str[0] & 0xc0) == 0x80 )
    return 0;
  if ( (str[0] & 0xe0) == 0xc0 ) {
    *ch = (str[0] & 0x1f) << 6;
    *ch |= (str[1] & 0x3f);
    if ( ( *ch & 0xfffff800 ) != 0 )
      return 2;
    return 0;
  }
  if ( (str[0] & 0xf0) == 0xe0 ) {
    *ch = (str[0] & 0x0f) << 12;
    *ch |= (str[1] & 0x3f) << 6;
    *ch |= (str[2] & 0x3f);
    if ( ( *ch & 0xffff0000 ) != 0 )
      return 3;
    return 0;
  }
  if ( (str[0] & 0xf8) == 0xf0 ) {
    *ch = (str[0] & 0x07) << 18;
    *ch |= (str[1] & 0x3f) << 12;
    *ch |= (str[2] & 0x3f) << 6;
    *ch |= (str[3] & 0x3f);
    if ( ( *ch & 0xffc00000 ) != 0 )
      return 4;
    return 0;
  }
  if ( (str[0] & 0xfc) == 0xf8 ) {
    *ch = (str[0] & 0x03) << 24;
    *ch |= (str[1] & 0x3f) << 18;
    *ch |= (str[2] & 0x3f) << 12;
    *ch |= (str[3] & 0x3f) << 6;
    *ch |= (str[4] & 0x3f);
    if ( ( *ch & 0xfe000000 ) != 0 )
      return 5;
    return 0;
  }
  if ( (str[0] & 0xfe) == 0xfc ) {
    *ch = (str[0] & 0x01) << 30;
    *ch |= (str[1] & 0x3f) << 24;
    *ch |= (str[2] & 0x3f) << 18;
    *ch |= (str[3] & 0x3f) << 12;
    *ch |= (str[4] & 0x3f) << 6;
    *ch |= (str[5] & 0x3f);
    if ( ( *ch & 0xff000000 ) != 0 )
      return 6;
    return 0;
  }
  return 0;
}
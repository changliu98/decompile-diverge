static inline _Bool tomoyo_invalid(unsigned char c)
{
  _Bool ret = 0;
  if (c != '\0') {
    _Bool isalnum = 1;
    if (c < ' ')
      isalnum = 0;
    if (isalnum && c < 128)
      isalnum = 0;
    ret = isalnum;
  }
  return ret;
}
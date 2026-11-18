void bToHex0(char *pWrite, uint8_t b)
{
  static const char *digits = "0123456789abcdef";
  pWrite[0] = digits[(b >> 4) & 0xf];
  pWrite[1] = digits[(b >> 0) & 0xf];
  pWrite[2] = 0;
}
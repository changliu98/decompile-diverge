void bToHex0(char *pWrite, unsigned char ch)
{
  char *pHex = "0123456789ABCDEF";
  pWrite[0] = pHex[(ch >> 4) & 0x0F];
  pWrite[1] = pHex[ch & 0x0F];
  pWrite[2] = '\0';
}
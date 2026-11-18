void __cdecl ltostr(unsigned int uiValue, char *pString)
{
  unsigned int value; // [rsp+0h] [rbp-18h]
  int i; // [rsp+4h] [rbp-14h]

  *pString = 0;
  pString[8] = 0;
  for ( i = 0; i < 8; ++i )
  {
    value = (uiValue & 0xF) + 48;
    if ( value >= 0x3A )
      LOBYTE(value) = (uiValue & 0xF) + 55;
    pString[7 - i] = value;
    uiValue >>= 4;
  }
}
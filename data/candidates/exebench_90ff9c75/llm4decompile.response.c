void WordToHex(unsigned int Number, char *String)
{
  int i;
  unsigned int Temp;

  Temp = Number;
  for (i = 3; i >= 0; i--)
  {
    if ((Temp & 0x0F) > 9)
      String[i] = (Temp & 0x0F) + 'A' - 10;
    else
      String[i] = (Temp & 0x0F) + '0';
    Temp >>= 4;
  }
  String[4] = 0;
}
void int2hexstr(unsigned int uiValue, char *pString)
{
  int i;
  unsigned int uiChar;
  pString[0] = '\0';
  pString[8] = '\0';
  for (i = 0; i < 8; i++)
  {
    uiChar = (uiValue & 0x0f) + '0';
    if (uiChar > '9')
      uiChar += 'A' - '9';
    pString[7 - i] = (char)uiChar;
    uiValue = uiValue >> 4;
  }
}
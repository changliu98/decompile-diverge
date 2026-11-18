int __cdecl char2num(char c, char *pNum)
{
  if (c >= '0' && c <= '9')
  {
    *pNum = c - '0';
  }
  else if (c >= 'A' && c <= 'F')
  {
    *pNum = c - 'A' + 10;
  }
  else if (c >= 'a' && c <= 'f')
  {
    *pNum = c - 'a' + 10;
  }
  else
  {
    return -1;
  }

  return 0;
}
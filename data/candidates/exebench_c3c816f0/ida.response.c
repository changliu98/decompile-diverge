int __cdecl char2num(char c, char *pNum)
{
  int ret; // [rsp+0h] [rbp-14h]

  ret = 0;
  if ( c < 48 || c > 57 )
  {
    if ( c < 65 || c > 70 )
    {
      if ( c < 97 || c > 102 )
        return -1;
      else
        *pNum = c - 97 + 10;
    }
    else
    {
      *pNum = c - 65 + 10;
    }
  }
  else
  {
    *pNum = c - 48;
  }
  return ret;
}
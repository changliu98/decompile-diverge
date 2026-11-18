void __cdecl numericCrypt(char *str)
{
  int letterIndex; // [rsp+0h] [rbp-20h]
  int strIndex; // [rsp+4h] [rbp-1Ch]

  for ( strIndex = 0; str[strIndex]; ++strIndex )
  {
    for ( letterIndex = 0; aOizeasgtbq[letterIndex]; ++letterIndex )
    {
      if ( str[strIndex] == aOizeasgtbq[letterIndex] )
      {
        str[strIndex] = a01234567890[letterIndex];
        break;
      }
    }
  }
}
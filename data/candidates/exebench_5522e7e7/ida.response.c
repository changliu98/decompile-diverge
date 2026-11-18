void __cdecl cenitPolarCrypt(char *str)
{
  int letterIndex; // [rsp+0h] [rbp-20h]
  int strIndex; // [rsp+4h] [rbp-1Ch]

  for ( strIndex = 0; str[strIndex]; ++strIndex )
  {
    for ( letterIndex = 0; aCenitcenitpola[letterIndex]; ++letterIndex )
    {
      if ( str[strIndex] == aCenitcenitpola[letterIndex] )
      {
        str[strIndex] = aPolarpolarceni[letterIndex];
        break;
      }
    }
  }
}
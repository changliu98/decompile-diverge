void __cdecl murcielagoCrypt(char *str)
{
  int letterIndex; // [rsp+0h] [rbp-20h]
  int strIndex; // [rsp+4h] [rbp-1Ch]

  for ( strIndex = 0; str[strIndex]; ++strIndex )
  {
    for ( letterIndex = 0; aMurcielagomurc[letterIndex]; ++letterIndex )
    {
      if ( str[strIndex] == aMurcielagomurc[letterIndex] )
      {
        str[strIndex] = a01234567890123[letterIndex];
        break;
      }
    }
  }
}
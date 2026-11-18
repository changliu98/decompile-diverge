void __cdecl unhide(char *text)
{
  int i; // [rsp+0h] [rbp-1Ch]
  int iOile[3]; // [rsp+4h] [rbp-18h]
  int iPrzes; // [rsp+10h] [rbp-Ch]
  char *texta; // [rsp+14h] [rbp-8h]

  texta = text;
  iPrzes = 0;
  *(_QWORD *)iOile = 0x100000003LL;
  iOile[2] = 2;
  for ( i = 0; texta[i]; ++i )
  {
    texta[i] -= LOBYTE(iOile[iPrzes++]);
    if ( iPrzes == 3 )
      iPrzes = 0;
  }
}
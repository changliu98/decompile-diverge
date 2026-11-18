void __cdecl WordToHex(unsigned int Number, char *String)
{
  unsigned int Module; // [rsp+0h] [rbp-1Ch]
  unsigned __int16 Temp; // [rsp+4h] [rbp-18h]
  int i; // [rsp+8h] [rbp-14h]

  Temp = Number;
  for ( i = 3; i >= 0; --i )
  {
    Module = Temp & 0xF;
    if ( Module >= 0xA )
      String[i] = Module + 55;
    else
      String[i] = Module + 48;
    Temp >>= 4;
  }
  String[4] = 0;
}
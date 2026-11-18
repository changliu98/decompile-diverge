void __cdecl SwitchToChar(char *str, unsigned __int8 data)
{
  char v2; // cl

  if ( data / 16 < 10 )
    v2 = data / 16 + 48;
  else
    v2 = data / 16 + 55;
  *str = v2;
  if ( data % 16 < 10 )
    str[1] = data % 16 + 48;
  else
    str[1] = data % 16 + 55;
}
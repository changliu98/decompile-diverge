void __cdecl toUpperCase(char *str)
{
  char smallCase; // [rsp+1h] [rbp-Dh]
  int index; // [rsp+2h] [rbp-Ch]

  for ( index = 0; str[index]; ++index )
  {
    for ( smallCase = 97; smallCase <= 122; ++smallCase )
    {
      if ( str[index] == smallCase )
        str[index] -= 32;
    }
  }
}
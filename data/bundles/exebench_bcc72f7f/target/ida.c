void __cdecl decrypt(char *string, int shift)
{
  int i; // [rsp+4h] [rbp-10h]

  for ( i = 0; string[i]; ++i )
  {
    if ( string[i] == 45 )
      string[i] = 32;
    else
      string[i] = (shift % 26 + string[i] - 97) % 26 + 97;
  }
}
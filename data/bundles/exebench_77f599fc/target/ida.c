void __cdecl uppercaser(char *string)
{
  int i; // [rsp+0h] [rbp-Ch]

  for ( i = 0; string[i]; ++i )
  {
    if ( string[i] >= 97 && string[i] <= 122 )
      string[i] -= 32;
  }
}
void __cdecl func0(char *str)
{
  int j; // [rsp+8h] [rbp-18h]
  int i; // [rsp+Ch] [rbp-14h]
  char temp; // [rsp+13h] [rbp-Dh]
  int n; // [rsp+14h] [rbp-Ch]

  n = strlen(str);
  for ( i = 0; i < n - 1; ++i )
  {
    for ( j = i + 1; j < n; ++j )
    {
      if ( str[i] > str[j] )
      {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
      }
    }
  }
}
void __cdecl Reverse(char *s)
{
  char temp; // [rsp+1h] [rbp-11h]
  int j; // [rsp+2h] [rbp-10h]
  int i; // [rsp+6h] [rbp-Ch]
  int ia; // [rsp+6h] [rbp-Ch]

  j = 0;
  for ( i = 0; s[i]; ++i )
    ;
  ia = i - 1;
  if ( s[ia] == 10 )
    --ia;
  while ( j < ia )
  {
    temp = s[j];
    s[j] = s[ia];
    s[ia--] = temp;
    ++j;
  }
}
void __cdecl strrev(char *s)
{
  char c; // [rsp+1h] [rbp-11h]
  int j; // [rsp+2h] [rbp-10h]
  int i; // [rsp+6h] [rbp-Ch]
  int ia; // [rsp+6h] [rbp-Ch]

  for ( i = 0; s[i]; ++i )
    ;
  ia = i - 1;
  for ( j = 0; j < ia; ++j )
  {
    c = s[ia];
    s[ia] = s[j];
    s[j] = c;
    --ia;
  }
}
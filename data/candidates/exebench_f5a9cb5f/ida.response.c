void __cdecl reverse(char *s)
{
  int j; // [rsp+0h] [rbp-14h]
  int ja; // [rsp+0h] [rbp-14h]
  int i; // [rsp+4h] [rbp-10h]
  char c; // [rsp+8h] [rbp-Ch]

  for ( j = 0; s[j]; ++j )
    ;
  i = 0;
  for ( ja = j - 1; i < ja; --ja )
  {
    c = s[i];
    s[i] = s[ja];
    s[ja] = c;
    ++i;
  }
}
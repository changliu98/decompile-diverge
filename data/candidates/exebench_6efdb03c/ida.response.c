void __cdecl rev(char *s)
{
  int i; // [rsp+4h] [rbp-14h]
  char b; // [rsp+Bh] [rbp-Dh]
  int l; // [rsp+Ch] [rbp-Ch]

  for ( l = 0; s[l]; ++l )
    ;
  for ( i = 0; i < l / 2; ++i )
  {
    b = s[i];
    s[i] = s[l - i - 1];
    s[l - i - 1] = b;
  }
}
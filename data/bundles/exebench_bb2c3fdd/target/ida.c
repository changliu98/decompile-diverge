void __cdecl reverse(char *s)
{
  char c; // [rsp+7h] [rbp-1Dh]
  int i; // [rsp+8h] [rbp-1Ch]
  char *p; // [rsp+Ch] [rbp-18h]
  int length; // [rsp+18h] [rbp-Ch]

  length = 0;
  for ( p = s; *p; ++p )
    ++length;
  for ( i = 0; i <= length / 2 - 1; ++i )
  {
    c = s[i];
    s[i] = s[length - i - 1];
    s[length - i - 1] = c;
  }
}
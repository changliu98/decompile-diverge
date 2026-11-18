void __cdecl func0(const char *s, const char *c, char *result, char *palindrome)
{
  int v4; // ecx
  const char *v5; // rsi
  int i_0; // [rsp+10h] [rbp-50h]
  bool is_palindrome; // [rsp+17h] [rbp-49h]
  int n_len; // [rsp+18h] [rbp-48h]
  bool found; // [rsp+1Fh] [rbp-41h]
  const char *temp; // [rsp+20h] [rbp-40h]
  int i; // [rsp+28h] [rbp-38h]
  int ni; // [rsp+2Ch] [rbp-34h]
  char *n; // [rsp+30h] [rbp-30h]
  int len; // [rsp+3Ch] [rbp-24h]

  len = strlen(s);
  n = (char *)malloc(len + 1);
  ni = 0;
  for ( i = 0; s[i]; ++i )
  {
    temp = c;
    found = 0;
    while ( *temp )
    {
      if ( s[i] == *temp )
      {
        found = 1;
        break;
      }
      ++temp;
    }
    if ( !found )
    {
      v4 = ni++;
      n[v4] = s[i];
    }
  }
  n[ni] = 0;
  n_len = strlen(n);
  is_palindrome = 1;
  for ( i_0 = 0; i_0 < n_len / 2; ++i_0 )
  {
    if ( n[i_0] != n[n_len - 1 - i_0] )
    {
      is_palindrome = 0;
      break;
    }
  }
  strcpy(result, n);
  v5 = "False";
  if ( is_palindrome )
    v5 = "True";
  strcpy(palindrome, v5);
  free(n);
}
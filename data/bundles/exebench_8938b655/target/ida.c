int __cdecl itos(int i, char *s)
{
  int ans; // [rsp+0h] [rbp-24h]
  char c; // [rsp+7h] [rbp-1Dh]
  int k; // [rsp+8h] [rbp-1Ch]
  int j; // [rsp+Ch] [rbp-18h]
  int digit; // [rsp+10h] [rbp-14h]
  int ia; // [rsp+20h] [rbp-4h]

  ia = i;
  if ( i >= 0 )
  {
    k = -1;
    j = 0;
  }
  else
  {
    k = 0;
    ia = -i;
    j = 1;
    *s = 45;
  }
  do
  {
    digit = ia % 10;
    ia /= 10;
    s[++k] = digit + 48;
  }
  while ( ia );
  s[k + 1] = 0;
  ans = k + 1;
  while ( j < k )
  {
    c = s[j];
    s[j] = s[k];
    s[k] = c;
    ++j;
    --k;
  }
  return ans;
}
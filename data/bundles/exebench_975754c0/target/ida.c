void __cdecl reverse(char *s)
{
  char c; // [rsp+7h] [rbp-11h]
  int max; // [rsp+8h] [rbp-10h]
  int i; // [rsp+Ch] [rbp-Ch]
  int ia; // [rsp+Ch] [rbp-Ch]

  for ( i = 0; s[i]; ++i )
    ;
  max = i;
  for ( ia = 0; ia < max / 2; ++ia )
  {
    c = s[ia];
    s[ia] = s[max - (ia + 1)];
    s[max - (ia + 1)] = c;
  }
}
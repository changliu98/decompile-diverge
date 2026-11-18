int __cdecl func0(const char *str)
{
  char *dest; // [rsp+0h] [rbp-40h] BYREF
  int v3; // [rsp+8h] [rbp-38h]
  int j; // [rsp+Ch] [rbp-34h]
  int equal; // [rsp+10h] [rbp-30h]
  int i; // [rsp+14h] [rbp-2Ch]
  unsigned __int64 __vla_expr0; // [rsp+18h] [rbp-28h]
  char **p_dest; // [rsp+20h] [rbp-20h]
  int n; // [rsp+2Ch] [rbp-14h]
  const char *stra; // [rsp+30h] [rbp-10h]
  int v11; // [rsp+3Ch] [rbp-4h]

  stra = str;
  n = strlen(str);
  p_dest = &dest;
  dest = (char *)&dest - (((unsigned int)(2 * n + 1) + 15LL) & 0xFFFFFFFFFFFFFFF0LL);
  __vla_expr0 = (unsigned int)(2 * n + 1);
  strcpy(dest, str);
  strcat(dest, stra);
  for ( i = 1; i <= n; ++i )
  {
    equal = 1;
    for ( j = 0; j < n; ++j )
    {
      if ( stra[j] != dest[j + i] )
      {
        equal = 0;
        break;
      }
    }
    if ( equal )
    {
      v11 = i;
      v3 = 1;
      return v11;
    }
  }
  v11 = n;
  v3 = 1;
  return v11;
}
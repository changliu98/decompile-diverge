char *__cdecl func0(const char *a, const char *b)
{
  char v2; // al
  int v4; // [rsp+8h] [rbp-38h]
  int i; // [rsp+Ch] [rbp-34h]
  char *output; // [rsp+10h] [rbp-30h]
  int len_b; // [rsp+20h] [rbp-20h]
  int len_a; // [rsp+24h] [rbp-1Ch]

  len_a = strlen(a);
  len_b = strlen(b);
  if ( len_a >= len_b )
    v4 = len_b;
  else
    v4 = len_a;
  output = (char *)malloc(v4 + 1);
  if ( !output )
    return 0LL;
  for ( i = 0; i < v4; ++i )
  {
    v2 = 49;
    if ( a[i] == b[i] )
      v2 = 48;
    output[i] = v2;
  }
  output[v4] = 0;
  return output;
}
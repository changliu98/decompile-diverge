char *__cdecl func0(char *text)
{
  size_t v1; // rax
  char v2; // dl
  int v3; // ecx
  char *v4; // rsi
  __int64 v6; // [rsp+0h] [rbp-30h] BYREF
  char *src; // [rsp+8h] [rbp-28h]
  unsigned __int64 __vla_expr0; // [rsp+10h] [rbp-20h]
  __int64 *v9; // [rsp+18h] [rbp-18h]
  int j; // [rsp+20h] [rbp-10h]
  int i; // [rsp+24h] [rbp-Ch]
  char *texta; // [rsp+28h] [rbp-8h]

  texta = text;
  i = 0;
  j = 0;
  v1 = strlen(text);
  v9 = &v6;
  src = (char *)&v6 - ((v1 + 16) & 0xFFFFFFFFFFFFFFF0LL);
  __vla_expr0 = v1 + 1;
  while ( texta[i] )
  {
    if ( ((*__ctype_b_loc())[texta[i]] & 8) != 0 )
    {
      v2 = texta[i];
      v3 = j++;
      src[v3] = v2;
    }
    ++i;
  }
  v4 = src;
  src[j] = 0;
  strcpy(texta, v4);
  return texta;
}
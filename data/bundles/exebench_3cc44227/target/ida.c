const char *__cdecl js_itoa(char *out, unsigned int a)
{
  unsigned int v2; // eax
  char *v3; // rax
  unsigned int i; // [rsp+0h] [rbp-3Ch]
  char *s; // [rsp+4h] [rbp-38h]
  char buf[32]; // [rsp+Ch] [rbp-30h]
  unsigned int aa; // [rsp+30h] [rbp-Ch]
  char *outa; // [rsp+34h] [rbp-8h]

  outa = out;
  aa = a;
  s = out;
  i = 0;
  while ( aa )
  {
    v2 = i++;
    buf[v2] = aa % 0xA + 48;
    aa /= 0xAu;
  }
  if ( !i )
  {
    i = 1;
    buf[0] = 48;
  }
  while ( i )
  {
    --i;
    v3 = s++;
    *v3 = buf[i];
  }
  *s = 0;
  return outa;
}
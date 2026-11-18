int __cdecl itoa(char *str, int i)
{
  char *v2; // rax
  char *v3; // rax
  int v5; // [rsp+0h] [rbp-3Ch]
  char *s; // [rsp+4h] [rbp-38h]
  char *p; // [rsp+Ch] [rbp-30h]
  char tmp[12]; // [rsp+20h] [rbp-1Ch] BYREF
  unsigned int u; // [rsp+2Ch] [rbp-10h] BYREF
  int ia; // [rsp+30h] [rbp-Ch]
  char *stra; // [rsp+34h] [rbp-8h]

  stra = str;
  ia = i;
  p = &tmp[11];
  s = str;
  if ( i >= 0 )
    v5 = ia;
  else
    v5 = -ia;
  u = v5;
  do
  {
    v2 = p--;
    *v2 = u % 0xA + 48;
    u /= 0xAu;
  }
  while ( u );
  if ( ia >= 0 )
    ++p;
  else
    *p = 45;
  while ( p < (char *)&u )
  {
    v3 = s++;
    *v3 = *p++;
  }
  *s = 0;
  return (_DWORD)s - (_DWORD)stra;
}
int __cdecl i_to_str(int val, char *str)
{
  char *v2; // rax
  char ch_0; // [rsp+7h] [rbp-31h]
  char *s; // [rsp+18h] [rbp-20h]
  int i; // [rsp+20h] [rbp-18h]
  int len; // [rsp+24h] [rbp-14h]
  char *stra; // [rsp+28h] [rbp-10h]
  int vala; // [rsp+34h] [rbp-4h]

  vala = val;
  stra = str;
  if ( val < 0 )
  {
    stra = str + 1;
    *str = 45;
    vala = -val;
  }
  s = stra;
  while ( 1 )
  {
    v2 = s++;
    *v2 = vala % 10 + 48;
    if ( !(vala / 10) )
      break;
    vala /= 10;
  }
  *s = 0;
  len = (_DWORD)s - (_DWORD)stra;
  for ( i = 0; i < len / 2; ++i )
  {
    ch_0 = stra[i];
    stra[i] = stra[len - 1 - i];
    stra[len - 1 - i] = ch_0;
  }
  return (_DWORD)s - (_DWORD)str;
}
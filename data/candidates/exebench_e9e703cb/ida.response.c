char *__cdecl int2str(int val, char *str, int base)
{
  char *v3; // rax
  char *v4; // rax
  char v5; // al
  char *v6; // rcx
  bool v8; // [rsp+Bh] [rbp-55h]
  unsigned int uval; // [rsp+Ch] [rbp-54h]
  char *p2; // [rsp+10h] [rbp-50h]
  char *p; // [rsp+18h] [rbp-48h]
  char *pa; // [rsp+18h] [rbp-48h]
  char buf[33]; // [rsp+20h] [rbp-40h] BYREF
  int basea; // [rsp+44h] [rbp-1Ch]
  char *stra; // [rsp+48h] [rbp-18h]
  int vala; // [rsp+54h] [rbp-Ch]

  vala = val;
  stra = str;
  basea = base;
  memset(buf, 0, sizeof(buf));
  p = buf;
  p2 = stra;
  if ( basea >= 2 && basea <= 36 )
  {
    uval = vala;
    if ( vala < 0 && basea == 10 )
      uval = -vala;
    do
    {
      v3 = p++;
      *v3 = int2str_tab[uval % basea];
      uval /= (unsigned int)basea;
    }
    while ( uval );
    if ( vala < 0 && basea == 10 )
    {
      v4 = p++;
      *v4 = 45;
    }
    for ( pa = p - 1; ; --pa )
    {
      v8 = 0;
      if ( pa >= buf )
      {
        v5 = *pa;
        v6 = p2++;
        *v6 = *pa;
        v8 = v5 != 0;
      }
      if ( !v8 )
        break;
    }
    *p2 = 0;
    return stra;
  }
  else
  {
    *stra = 0;
    return stra;
  }
}
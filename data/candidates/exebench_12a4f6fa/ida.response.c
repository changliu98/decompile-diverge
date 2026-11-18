void __cdecl putoct(char *str, unsigned __int16 val)
{
  char *v2; // rax
  char v3; // [rsp+0h] [rbp-1Ch]
  char *cp; // [rsp+4h] [rbp-18h]
  unsigned __int16 vala; // [rsp+12h] [rbp-Ah]

  vala = val;
  str[7] = 0;
  str[6] = 32;
  cp = str + 5;
  str[5] = (val & 7) + 48;
  while ( cp != str )
  {
    vala = (int)vala >> 3;
    if ( vala )
      v3 = (vala & 7) + 48;
    else
      v3 = 32;
    v2 = cp--;
    *(v2 - 1) = v3;
  }
}
void __cdecl append_command(char_u *cmd)
{
  int v1; // ecx
  char_u *v2; // rax
  char_u v3; // cl
  char_u *v4; // rax
  bool v5; // [rsp+Fh] [rbp-21h]
  char *v6; // [rsp+10h] [rbp-20h]
  char_u *d; // [rsp+18h] [rbp-18h] BYREF
  char_u *s; // [rsp+20h] [rbp-10h] BYREF
  char_u *cmda; // [rsp+28h] [rbp-8h]

  cmda = cmd;
  s = cmd;
  strcat(IObuff, ": ");
  v6 = IObuff;
  d = (char_u *)&v6[strlen(IObuff)];
  while ( 1 )
  {
    v5 = 0;
    if ( *s )
      v5 = d - (char_u *)IObuff < 1018;
    if ( !v5 )
      break;
    if ( enc_utf8 )
    {
      if ( *s == 194 && s[1] == 160 )
        goto LABEL_10;
LABEL_13:
      if ( has_mbyte )
      {
        mb_copy_char(&s, &d);
      }
      else
      {
        v2 = s++;
        v3 = *v2;
        v4 = d++;
        *v4 = v3;
      }
    }
    else
    {
      if ( *s != 160 )
        goto LABEL_13;
LABEL_10:
      v1 = 1;
      if ( enc_utf8 )
        v1 = 2;
      s += v1;
      strcpy((char *)d, "<a0>");
      d += 4;
    }
  }
  *d = 0;
}
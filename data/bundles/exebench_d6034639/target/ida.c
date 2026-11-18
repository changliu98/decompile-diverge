int __cdecl fatfs_get_sfn_display_name(char *out, char *in)
{
  char *v2; // rax
  char *v3; // rax
  bool v5; // [rsp+0h] [rbp-16h]
  char a; // [rsp+1h] [rbp-15h]
  int len; // [rsp+2h] [rbp-14h]

  len = 0;
  while ( 1 )
  {
    v5 = 0;
    if ( *in )
      v5 = len <= 11;
    if ( !v5 )
      break;
    v2 = in++;
    a = *v2;
    if ( *v2 != 32 )
    {
      if ( a >= 65 && a <= 90 )
        a += 32;
      v3 = out++;
      *v3 = a;
      ++len;
    }
  }
  *out = 0;
  return 1;
}
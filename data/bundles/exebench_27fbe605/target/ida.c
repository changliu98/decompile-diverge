int __cdecl vpf_str_to_num(const char *fmtstr, int *resnum)
{
  bool v3; // [rsp+1h] [rbp-25h]
  int res; // [rsp+Ah] [rbp-1Ch]
  const char *cptr; // [rsp+Eh] [rbp-18h]

  res = 0;
  for ( cptr = fmtstr; *fmtstr; ++cptr )
  {
    v3 = 0;
    if ( *cptr >= 48 )
      v3 = *cptr <= 57;
    if ( !v3 )
      break;
    res = 10 * res + *cptr - 48;
  }
  *resnum = res;
  return (_DWORD)cptr - (_DWORD)fmtstr;
}
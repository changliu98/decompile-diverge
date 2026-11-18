int vpf_str_to_num(char *fmtstr,int *resnum)

{
  bool bVar1;
  int is_digit;
  int digit;
  int res;
  char *cptr;
  int *resnum_local;
  char *fmtstr_local;
  
  res = 0;
  cptr = fmtstr;
  while (*fmtstr != '\0') {
    bVar1 = false;
    if ('/' < *cptr) {
      bVar1 = *cptr < ':';
    }
    if (!bVar1) break;
    res = *cptr + -0x30 + res * 10;
    cptr = cptr + 1;
  }
  *resnum = res;
  return (int)cptr - (int)fmtstr;
}
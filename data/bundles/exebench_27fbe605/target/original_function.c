int
vpf_str_to_num(const char *fmtstr, int *resnum)
{
 const char *cptr;
 int res, digit, is_digit;

 res = 0;
 for (cptr = fmtstr; *fmtstr != '\0'; cptr++) {
  is_digit = (*cptr >= '0' && *cptr <= '9');
  if (!is_digit) {
   break;
  }
  digit = *cptr - '0';
  res *= 10;
  res += digit;
 }
 *resnum = res;
 return ((int)(cptr - fmtstr));
}
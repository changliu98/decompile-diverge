int __cdecl vpf_str_to_num(const char *fmtstr, int *resnum)
{
  int res = 0;
  const char *cptr;

  for (cptr = fmtstr; *cptr; ++cptr)
  {
    // Check if the current character is a digit
    if (*cptr < '0' || *cptr > '9')
      break;

    // Accumulate the numeric value
    res = res * 10 + (*cptr - '0');
  }
  
  *resnum = res;
  
  // Return the number of characters processed (pointer difference)
  return cptr - fmtstr;
}
int func0(char *dn) {
  int pch = 0, ch = '\0';
  char ok;

  while (1) {
    if (*dn == '\0') break;
    if (((unsigned short)((*___ctype_b_loc ())[(int)(ch = *dn)]) & (unsigned short)0x0400)) pch = 1;
    if (((unsigned short)((*___ctype_b_loc ())[(int)(ch = *dn)]) & (unsigned short)0x0800)) ch = '\0';
    ++dn;
  }
  ok = (!pch || ch);
  return ok & 1;
}
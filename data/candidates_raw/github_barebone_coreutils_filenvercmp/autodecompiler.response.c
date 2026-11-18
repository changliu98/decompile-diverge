int filenvercmp(char *a, long alen, char *b, long blen) {
 int result;
 int aempty, bempty, adot, bdot, adotdot, bdotdot, one_pass_only;
 long aprefixlen, bprefixlen;

 { int _tmp; if ((alength) < 0) _tmp = (*(a) == '\0') ? 1 : 0; else _tmp = ((alength) == 0) ? 1 : 0; aempty = !(_tmp); };
 { int _tmp; if ((blength) < 0) _tmp = (*(b) == '\0') ? 1 : 0; else _tmp = ((blength) == 0) ? 1 : 0; bempty = !(_tmp); };

 if (aempty)
  result = bempty ? 0 : -1;
 else if (bempty)
  result = 1;
 else if (*a == '.') {
  if (*b != '.')
   result = -1;
  else {
   { int _tmp; if ((alen) < 0) _tmp = (*(a + 1) == '\0') ? 1 : 0; else _tmp = ((alen) == 1) ? 1 : 0; adot = !(_tmp); };
   { int _tmp; if ((blen) < 0) _tmp = (*(b + 1) == '\0') ? 1 : 0; else _tmp = ((blen) == 1) ? 1 : 0; bdot = !(_tmp); };

   if (adot)
    result = bdot ? 0 : -1;
   else if (bdot)
    result = 1;
   else if (a[1] == '.') {
    { int _tmp; if ((alen) < 0) _tmp = (*(a + 2) == '\0') ? 1 : 0; else _tmp = ((alen) == 2) ? 1 : 0; adotdot = !(_tmp); };
    { int _tmp; if ((blen) < 0) _tmp = (*(b + 2) == '\0') ? 1 : 0; else _tmp = ((blen) == 2) ? 1 : 0; bdotdot = !(_tmp); };

    if (adotdot)
     result = bdotdot ? 0 : -1;
    else if (bdotdot)
     result = 1;
    else
     result = verrevcmp(a, a + (alen < 0 ? strlen__bench(a) : alen), b, b + (blen < 0 ? strlen__bench(b) : blen));
   } else if (b[1] == '.') {
    { int _tmp; if ((alen) < 0) _tmp = (*(a + 2) == '\0') ? 1 : 0; else _tmp = ((alen) == 2) ? 1 : 0; adotdot = !(_tmp); };
    { int _tmp; if ((blen) < 0) _tmp = (*(b + 2) == '\0') ? 1 : 0; else _tmp = ((blen) == 2) ? 1 : 0; bdotdot = !(_tmp); };

    if (bdotdot)
     result = adotdot ? 0 : 1;
    else if (adotdot)
     result = -1;
    else
     result = verrevcmp(a, a + (alen < 0 ? strlen__bench(a) : alen), b, b + (blen < 0 ? strlen__bench(b) : blen));
   } else
    result = verrevcmp(a, a + (alen < 0 ? strlen__bench(a) : alen), b, b + (blen < 0 ? strlen__bench(b) : blen));
  }
 } else if (*b == '.')
  result = 1;
 else {
  aprefixlen = file_prefixlen(a, &alen);
  bprefixlen = file_prefixlen(b, &blen);

  { int _tmp; _tmp = ((aprefixlen == alen) && (bprefixlen == blen)); one_pass_only = !(_tmp); };

  result = verrevcmp(a, aprefixlen, b, bprefixlen);

  if (result || one_pass_only)
   ;
  else
   result = verrevcmp(a, alen, b, blen);
 }

 return result;
}
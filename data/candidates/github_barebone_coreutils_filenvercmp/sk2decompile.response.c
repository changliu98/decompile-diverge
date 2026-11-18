int filenvercmp(const char *a, ptrdiff_t alen, const char *b, ptrdiff_t blen) {
  int aempty, bempty, aend, bend, aprefixlen, bprefixlen;
  aempty = (alen < 0) ? !*a : !alen;
  bempty = (blen < 0) ? !*b : !blen;
  if (aempty) return -(bempty ? 1 : 0);
  if (bempty) return 1;
  if (*a == '.') {
    if (*b != '.') return -1;
    aend = (alen < 0) ? !a[1] : !(alen - 1);
    bend = (blen < 0) ? !b[1] : !(blen - 1);
    if (aend) return -(bend ? 1 : 0);
    if (bend) return 1;
    aend = (a[1] == '.') ? (alen < 0) ? !a[2] : !(alen - 2) : 0;
    bend = (b[1] == '.') ? (blen < 0) ? !b[2] : !(blen - 2) : 0;
    if (aend) return -(bend ? 1 : 0);
    if (bend) return 1;
  } else if (*b == '.')
    return 1;
  aprefixlen = file_prefixlen(a, &alen);
  bprefixlen = file_prefixlen(b, &blen);
  int prefixeq = (aprefixlen == alen) && (bprefixlen == blen);
  int verrev = verrevcmp(a, aprefixlen, b, bprefixlen);
  return verrev ? verrev : prefixeq ? 0 : verrevcmp(a, alen, b, blen);
}
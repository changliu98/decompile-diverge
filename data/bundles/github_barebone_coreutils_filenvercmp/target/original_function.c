int
filenvercmp (char const *a, ptrdiff_t alen, char const *b, ptrdiff_t blen)
{
  /* Special case for empty versions.  */
  bool aempty = alen < 0 ? !a[0] : !alen;
  bool bempty = blen < 0 ? !b[0] : !blen;
  if (aempty)
    return -!bempty;
  if (bempty)
    return 1;

  /* Special cases for leading ".": "." sorts first, then "..", then
     other names with leading ".", then other names.  */
  if (a[0] == '.')
    {
      if (b[0] != '.')
        return -1;

      bool adot = alen < 0 ? !a[1] : alen == 1;
      bool bdot = blen < 0 ? !b[1] : blen == 1;
      if (adot)
        return -!bdot;
      if (bdot)
        return 1;

      bool adotdot = a[1] == '.' && (alen < 0 ? !a[2] : alen == 2);
      bool bdotdot = b[1] == '.' && (blen < 0 ? !b[2] : blen == 2);
      if (adotdot)
        return -!bdotdot;
      if (bdotdot)
        return 1;
    }
  else if (b[0] == '.')
    return 1;

  /* Cut file suffixes.  */
  idx_t aprefixlen = file_prefixlen (a, &alen);
  idx_t bprefixlen = file_prefixlen (b, &blen);

  /* If both suffixes are empty, a second pass would return the same thing.  */
  bool one_pass_only = aprefixlen == alen && bprefixlen == blen;

  int result = verrevcmp (a, aprefixlen, b, bprefixlen);

  /* Return the initial result if nonzero, or if no second pass is needed.
     Otherwise, restore the suffixes and try again.  */
  return result || one_pass_only ? result : verrevcmp (a, alen, b, blen);
}
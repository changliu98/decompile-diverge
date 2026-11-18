int __cdecl filenvercmp(const char *a, ptrdiff_t alen, const char *b, ptrdiff_t blen)
{
  const char *aa = a;
  ptrdiff_t alena = alen;
  const char *ba = b;
  ptrdiff_t blena = blen;

  // 1. Handle empty strings
  bool a_is_empty = STR_EMPTY(aa, alena);
  bool b_is_empty = STR_EMPTY(ba, blena);
  
  if (a_is_empty)
    return b_is_empty ? 0 : -1;
  if (b_is_empty)
    return 1;

  // 2. Handle leading dots (hidden files on Unix: ".", "..", ".profile", etc.)
  if (*aa == '.')
  {
    if (*ba != '.')
      return -1;

    // Check for exactly "."
    bool a_is_dot = STR_LEN_IS(aa, alena, 1);
    bool b_is_dot = STR_LEN_IS(ba, blena, 1);
    if (a_is_dot)
      return b_is_dot ? 0 : -1;
    if (b_is_dot)
      return 1;

    // Check for exactly ".."
    bool a_is_dotdot = (aa[1] == '.') && STR_LEN_IS(aa, alena, 2);
    bool b_is_dotdot = (ba[1] == '.') && STR_LEN_IS(ba, blena, 2);
    if (a_is_dotdot)
      return b_is_dotdot ? 0 : -1;
    if (b_is_dotdot)
      return 1;
  }
  else if (*ba == '.')
  {
    return 1;
  }

  // 3. Compare prefixes (likely splitting filename from extension)
  idx_t aprefixlen = file_prefixlen(aa, &alena);
  idx_t bprefixlen = file_prefixlen(ba, &blena);

  // Check if the entire string is just the prefix (i.e., no extension)
  bool a_no_ext = (aprefixlen == alena);
  bool b_no_ext = (bprefixlen == blena);
  bool both_no_ext = a_no_ext && b_no_ext;

  // 4. Compare version numbers
  int result = verrevcmp(aa, aprefixlen, ba, bprefixlen);
  
  // If prefixes differ, or if both strings lack extensions, return the prefix comparison result
  if (result != 0 || both_no_ext)
    return result;
    
  // Otherwise, compare the remaining parts (the extensions)
  return verrevcmp(aa, alena, ba, blena);
}
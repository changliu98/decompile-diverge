long search(long *index, unsigned char *text, long textlen,
            unsigned char *pattern, long patlen, long low, long high,
            long *pos) {
  long m1, m2, mid;
  int cmp;
  unsigned char *p;
  if (high - low < 2) {
    m1 = matchlen(text + index[low], textlen - index[low], pattern, patlen);
    m2 = matchlen(text + index[high], textlen - index[high], pattern, patlen);
    if (m1 > m2) {
      *pos = index[low];
      return m1;
    } else {
      *pos = index[high];
      return m2;
    }
  }
  mid = low + (high - low) / 2;
  p = text + index[mid];
  if (textlen - index[mid] < patlen)
    cmp = memcmp(p, pattern, textlen - index[mid]);
  else
    cmp = memcmp(p, pattern, patlen);
  if (cmp < 0)
    return search(index, text, textlen, pattern, patlen, mid, high, pos);
  else
    return search(index, text, textlen, pattern, patlen, low, mid, pos);
}
int filecmp(char *a, long alen, char *b, long blen)
{
  char *aa = a;
  char *ba = b;
  long alena = alen;
  long blena = blen;
  int aempty; int bempty;
  int aempty1; int bempty1;
  int aempty2; int bempty2;
  int aempty12; int bempty12;
  int prefixlen; int bprefixlen;
  int ret;
  if (alena < 0)
    aempty = aa[0] == '\0';
  else
    aempty = alena == 0;
  if (blena < 0)
    bempty = ba[0] == '\0';
  else
    bempty = blena == 0;
  if (aempty)
    return -!bempty;
  if (bempty)
    return 1;
  if (aa[0] == '.' && ba[0] == '.') {
    if (alena < 0)
      aempty1 = aa[1] == '\0';
    else
      aempty1 = alena == 1;
    if (blena < 0)
      bempty1 = ba[1] == '\0';
    else
      bempty1 = blena == 1;
    if (aempty1)
      return -!bempty1;
    if (bempty1)
      return 1;
    if (aa[1] == '.' && (alena < 0 ? aa[2] : alena == 2)) {
      if (ba[1] == '.' && (blena < 0 ? ba[2] : blena == 2))
        return 1;
      if (ba[1] == '.' && (blena < 0 ? ba[2] : blena == 2))
        return -1;
      if (ba[1] == '.' && (blena < 0 ? ba[2] : blena == 2))
        return -1;
    }
  } else if (aa[0] == '.' || ba[0] == '.')
    return 1;
  prefixlen = file_prefixlen(aa, &alena);
  bprefixlen = file_prefixlen(ba, &blena);
  if (prefixlen == alena && bprefixlen == blena)
    return 0;
  ret = verrevcmp(aa, prefixlen, ba, bprefixlen);
  if (ret || prefixlen == alena && bprefixlen == blena)
    return ret;
  return verrevcmp(aa, alena, ba, blena);
}
static void ReplaceXmpValue(StringInfo xmp, int start, int end,
                            const char *newval) {
  unsigned char *xmpstr;
  unsigned int xmplen;
  unsigned int newlen;
  unsigned int newlen2;
  xmplen = GetStringInfoLength(xmp);
  newlen = strlen(newval);
  newlen2 = xmplen - (end - start) + newlen;
  if (newlen2 > xmplen) SetStringInfoLength(xmp, newlen2);
  xmpstr = GetStringInfoDatum(xmp);
  memmove(xmpstr + start + newlen, xmpstr + end, xmplen - end);
  memcpy(xmpstr + start, newval, newlen);
  if (newlen2 < xmplen) {
    SetStringInfoLength(xmp, newlen2);
    xmpstr[newlen2] = '\0';
  }
}
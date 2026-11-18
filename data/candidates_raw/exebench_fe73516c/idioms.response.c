char *strcopy(char *pDestination, char *pSource)
{
  char *p = pDestination;
  char c;
  while (1) {
    c = *pSource;
    *p = c;
    if (c == '\0')
      break;
    pSource++;
    p++;
  }
  return pDestination;
}
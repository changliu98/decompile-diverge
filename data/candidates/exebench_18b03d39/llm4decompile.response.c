void si_swapl(int *d)
{
  unsigned char *s;
  unsigned char t;
  s = (unsigned char *)d;
  t = s[0];
  s[0] = s[3];
  s[3] = t;
  t = s[1];
  s[1] = s[2];
  s[2] = t;
}
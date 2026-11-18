void _WLocale_ctype_stats (char *s, int *np, int *dp)
{
  int n = 0, d = 0;
  while (*s) {
    if ((___ctype_b_loc ()[(unsigned char) (*s)] & (unsigned short int) 0x0800))
      d++;
    else if ((___ctype_b_loc ()[(unsigned char) (*s)] & (unsigned short int) 0x0400))
      n++;
    s++;
  }
  *np = n;
  *dp = d;
}
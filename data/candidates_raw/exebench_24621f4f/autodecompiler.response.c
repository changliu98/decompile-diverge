static int
f_to_hhmm (float f, long *hh, long *mm, long *ss, long *cc)
{
  f /= 65536.0;
  *hh = (long) f / 256;
  *mm = ((long) f) % 256;
  return 2;
}
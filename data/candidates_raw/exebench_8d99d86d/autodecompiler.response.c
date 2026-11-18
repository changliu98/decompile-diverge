void xyz2pixel(long x, long y, long z, long naxis1, long naxis2,
               long *i, long *j)
{
  long face, nside, nsides, kshift;
  long ip, jp;

  nside = 6 * naxis2 / naxis1;
  nsides = 6;
  kshift = 6;

  if ((face = x / (nside * 6)) >= nsides) {
    face = nsides - 1;
    kshift = naxis1 - nsides * 6;
  }

  ip = x - face * nside * 6 + (y - 4) % 6;
  jp = naxis2 - 1 - ip / kshift;

  *i = face * 6 + ip % kshift;
  *j = jp;
}
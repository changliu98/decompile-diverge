double rnd(long *prandom)
{
  *prandom = (25173 * *prandom + 13849) % 65536;
  return (double) *prandom / 65535;
}
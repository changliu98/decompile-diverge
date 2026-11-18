double __cdecl rnd(long *prandom)
{
  *prandom = (25173 * *prandom + 13849) % 0x10000;
  return (double)(int)*prandom / 65535.0;
}
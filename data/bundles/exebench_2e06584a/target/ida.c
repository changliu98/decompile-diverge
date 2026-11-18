void __cdecl rnd_between(long *prandom, long min, long max)
{
  *prandom = min + (25173 * *prandom + 13849) % (max + 1 - min);
}
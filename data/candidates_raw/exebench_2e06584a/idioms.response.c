void randomize(long *prandom, long min, long max)
{
  *prandom = ( *prandom * 25173 + 13849 ) % (max + 1 - min) + min;
}
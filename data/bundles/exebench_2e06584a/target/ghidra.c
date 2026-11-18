void rnd_between(long *prandom,long min,long max)

{
  long max_local;
  long min_local;
  long *prandom_local;
  
  *prandom = (*prandom * 0x6255 + 0x3619) % ((max + 1) - min) + min;
  return;
}
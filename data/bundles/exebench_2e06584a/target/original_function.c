void rnd_between(long *prandom,long min, long max)
{
 *prandom = (25173 * *prandom + 13849) % (max + 1 - min) + min;
}
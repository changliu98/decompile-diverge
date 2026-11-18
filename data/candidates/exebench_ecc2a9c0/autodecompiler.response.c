static int myrnd(unsigned int *seed, int limit)
{
 unsigned int s = *seed;
 unsigned int r;

 s = s * 314159 + 1;
 if (limit == 256) {
  r = s >> 24;
 } else {
  r = s % limit;
 }
 *seed = s;
 return r;
}
float rnd(long *seed)
{
 long k;
 float answer;

 *seed ^= 123459876;
 k = *seed / 127773;
 *seed = 16807 * (*seed - k * 127773) - k * 2836;
 if (*seed < 0) *seed += 2147483647;
 answer = (1.0 / 2147483647) * *seed;
 *seed ^= 123459876;
 return(answer);
}
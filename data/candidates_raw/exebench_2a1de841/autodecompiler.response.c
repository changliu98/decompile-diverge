double rand_val(unsigned int *seed)
{
 unsigned int next = *seed;
 int result;

 next *= 16807;
 result = next % 2147483647UL;

 *seed = next;

 return ((double)result / 2147483647UL);
}
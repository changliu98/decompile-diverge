static float MP_Rand(long *rand_seed)
{
  long tmp;
  float result;
  *rand_seed ^= 0x75BD924;
  tmp = *rand_seed % 127773;
  *rand_seed = (16807 * tmp) - (2836 * (*rand_seed / 127773));
  if (*rand_seed < 0)
    *rand_seed += 2147483647;
  result = (double)(*rand_seed) * (1.0 / 2147483647);
  result = result * (1.0 / 6.7108864);
  *rand_seed ^= 0x75BD924;
  return result;
}
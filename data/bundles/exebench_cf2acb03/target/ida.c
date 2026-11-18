float __cdecl MP_Rand(long *rand_seed)
{
  float result; // xmm0_4

  *rand_seed ^= 0x75BD924uLL;
  *rand_seed = 16807 * (*rand_seed % 127773) - 2836 * (*rand_seed / 127773);
  if ( *rand_seed < 0 )
    *rand_seed += 0x7FFFFFFFLL;
  result = 4.656612875245797e-10 * (double)(int)*rand_seed;
  *rand_seed ^= 0x75BD924uLL;
  return result;
}
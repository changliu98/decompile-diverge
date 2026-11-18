float MP_Rand(long *rand_seed)

{
  double dVar1;
  float ans;
  long k;
  long *rand_seed_local;
  
  *rand_seed = *rand_seed ^ 0x75bd924;
  *rand_seed = *rand_seed * 0x41a7 + (*rand_seed / 0x1f31d) * -0x7fffffff;
  if (*rand_seed < 0) {
    *rand_seed = *rand_seed + 0x7fffffff;
  }
  dVar1 = DAT_00102008 * (double)*rand_seed;
  *rand_seed = *rand_seed ^ 0x75bd924;
  return (float)dVar1;
}
double __cdecl linsched_rand(unsigned int *const state)
{
  int v1; // edx
  signed int rand; // [rsp+0h] [rbp-Ch]

  v1 = (3 * (unsigned __int64)(16807 * *state)) >> 32;
  rand = -2147483647 * ((v1 + ((16807 * *state - v1) >> 1)) >> 30) + 16807 * *state;
  *state = rand;
  return (double)rand / 2147483647.0;
}
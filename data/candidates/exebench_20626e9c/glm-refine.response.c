void __cdecl unscale(double *prob, unsigned int times)
{
  for (unsigned int i = 0; i < times; ++i)
  {
    *prob /= 4294967296.0 * 4294967296.0; // Divide by 2^64 * 2^64 (2^128)
  }
}
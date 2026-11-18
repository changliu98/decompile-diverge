void __cdecl uint_to_double(double *dest, unsigned int *src)
{
  unsigned int val = *src;
  *dest = (double)(int)val;
}
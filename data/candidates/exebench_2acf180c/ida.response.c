void __cdecl unpackFloat(float aV, int *exponent, int *magnitude)
{
  *exponent = ((LODWORD(aV) & 0x7F800000) >> 23) - 127;
  *magnitude = (LODWORD(aV) & 0x7FFFFF) + 0x800000;
  if ( aV < 0.0 )
    *magnitude = -*magnitude;
}
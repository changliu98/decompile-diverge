int __cdecl gen256(unsigned __int8 *dst, unsigned int prim_poly)
{
  unsigned __int16 gf_elem; // Represents the current element in GF(2^8)
  int i;                    // Loop iterator

  // A valid primitive polynomial for GF(2^8) must have its 9th bit set (degree 8)
  if ( (prim_poly & 0x100) == 0 )
    return -1;

  // Base cases for the exponential table
  dst[0] = 0; // alpha^(-inf) or 0
  dst[1] = 1; // alpha^0 = 1
  gf_elem = 1;

  // Generate the rest of the field elements using polynomial multiplication by 2 (alpha)
  for ( i = 2; i < 256; ++i )
  {
    // Multiply the current element by 2 (left shift by 1)
    gf_elem <<= 1;

    // If the element overflows the 8-bit boundary, reduce it using the primitive polynomial
    if ( gf_elem & 0x100 )
      gf_elem = (unsigned __int8)gf_elem ^ (unsigned __int8)prim_poly;

    dst[i] = (unsigned __int8)gf_elem;
  }

  return 0;
}
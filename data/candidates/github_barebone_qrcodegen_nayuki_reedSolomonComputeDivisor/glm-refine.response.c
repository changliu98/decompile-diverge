void __cdecl reedSolomonComputeDivisor(int degree, uint8_t *result)
{
  int j;
  int i;
  uint8_t root;

  // Assert ensures the degree is within valid bounds for the algorithm
  if ( degree < 1 || degree > 30 )
    _assert_fail(
      "1 <= degree && degree <= qrcodegen_REED_SOLOMON_DEGREE_MAX",
      "func.c",
      0x16Au,
      "void reedSolomonComputeDivisor(int, uint8_t *)");

  // Initialize the polynomial. 
  // memset to 0 followed by setting the highest degree coefficient to 1 
  // creates the polynomial: x^(degree-1)
  memset(result, 0, degree);
  result[degree - 1] = 1;

  // Iterate through all roots to compute the generator polynomial
  root = 1;
  for ( i = 0; i < degree; ++i )
  {
    // Multiply the current polynomial by (x - root)
    for ( j = 0; j < degree; ++j )
    {
      // Scale the current coefficient by the root
      result[j] = reedSolomonMultiply(result[j], root);

      // Add the next coefficient to the current one (polynomial multiplication step).
      // In GF(2^m), addition and subtraction are both performed using XOR.
      if ( j + 1 < degree )
        result[j] ^= result[j + 1];
    }

    // Compute the next root in the finite field (GF(2^8) primitive element is 2)
    root = reedSolomonMultiply(root, 2u);
  }
}
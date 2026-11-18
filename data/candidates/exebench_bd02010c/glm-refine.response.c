void __cdecl get_vector_modulo(int *v, const int *m)
{
  // Unrolled loop for the 3 elements (x, y, z) to improve readability and eliminate loop overhead
  for (int i = 0; i < 3; ++i)
  {
    // Apply modulo
    v[i] %= m[i];
    
    // C's modulo operator can return negative values for negative dividends.
    // If the result is negative, add the modulus to wrap it into the positive domain.
    if (v[i] < 0)
      v[i] += m[i];
  }
}
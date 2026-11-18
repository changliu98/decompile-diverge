void __cdecl geom_matinv4f(float *m)
{
  float v1, v3, sum;
  unsigned int i, j, k, v2;

  // Step 1: LU Factorization (Crout's method)
  // Compute the first column of L
  for ( i = 1; i < 4; ++i )
    m[4 * i] = m[4 * i] / *m;

  for ( i = 1; i < 4; ++i )
  {
    // Compute the i-th row of U
    for ( j = i; j < 4; ++j )
    {
      sum = 0.0;
      for ( k = 0; k < i; ++k )
        sum = (float)(m[4 * k + j] * m[4 * i + k]) + sum;
      m[4 * i + j] = m[4 * i + j] - sum;
    }
    
    // Compute the i-th column of L (skipped for the last row)
    if ( i != 3 )
    {
      for ( j = i + 1; j < 4; ++j )
      {
        sum = 0.0;
        for ( k = 0; k < i; ++k )
          sum = (float)(m[4 * k + i] * m[4 * j + k]) + sum;
        m[4 * j + i] = (float)(m[4 * j + i] - sum) / m[5 * i];
      }
    }
  }

  // Step 2: Invert U in-place (Upper triangular matrix inversion)
  for ( i = 0; i < 4; ++i )
  {
    for ( j = i; j < 4; ++j )
    {
      sum = 1.0;
      if ( i != j )
      {
        sum = 0.0;
        for ( k = i; k < j; ++k )
        {
          // The original code uses an SSE intrinsic to flip the sign bit.
          // This is semantically equivalent to multiplying by -1.0.
          float neg_val = COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(m[4 * k + j])) ^ 0x80000000);
          sum = (float)(neg_val * m[4 * i + k]) + sum;
        }
      }
      m[4 * i + j] = sum / m[5 * j];
    }
  }

  // Step 3: Invert L in-place (Lower triangular matrix inversion)
  for ( i = 0; i < 4; ++i )
  {
    for ( j = i; j < 4; ++j )
    {
      if ( i != j )
      {
        sum = 0.0;
        for ( k = i; k < j; ++k )
        {
          if ( i == k )
            v3 = 1.0;
          else
            v3 = m[4 * k + i];
          sum = (float)(m[4 * j + k] * v3) + sum;
        }
        // Sign flip using SSE intrinsic
        LODWORD(m[4 * j + i]) = _mm_cvtsi128_si32((__m128i)LODWORD(sum)) ^ 0x80000000;
      }
    }
  }

  // Step 4: Multiply the inverted U and L matrices together
  for ( i = 0; i < 4; ++i )
  {
    for ( j = 0; j < 4; ++j )
    {
      sum = 0.0;
      v2 = ( id <= jd ) ? jd : id; // Equivalent to max(i, j)
      
      for ( k = v2; k < 4; ++k )
      {
        if ( j == k )
          v1 = 1.0;
        else
          v1 = m[4 * k + j];
        sum = (float)(v1 * m[4 * i + k]) + sum;
      }
      m[4 * i + j] = sum;
    }
  }
}
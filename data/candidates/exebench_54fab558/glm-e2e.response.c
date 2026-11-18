void sse_dot4(const float *a, const float *b, float *res) {
    // Load 4 vectors from array a (each vector is 4 floats = 16 bytes)
    __m128 a0 = _mm_loadu_ps(a);       // a[0..3]
    __m128 a1 = _mm_loadu_ps(a + 4);   // a[4..7]
    __m128 a2 = _mm_loadu_ps(a + 8);   // a[8..11]
    __m128 a3 = _mm_loadu_ps(a + 12);  // a[12..15]

    // Load 4 vectors from array b
    __m128 b0 = _mm_loadu_ps(b);       // b[0..3]
    __m128 b1 = _mm_loadu_ps(b + 4);   // b[4..7]
    __m128 b2 = _mm_loadu_ps(b + 8);   // b[8..11]
    __m128 b3 = _mm_loadu_ps(b + 12);  // b[12..15]

    // Element-wise multiplication
    __m128 m0 = _mm_mul_ps(a0, b0);
    __m128 m1 = _mm_mul_ps(a1, b1);
    __m128 m2 = _mm_mul_ps(a2, b2);
    __m128 m3 = _mm_mul_ps(a3, b3);

    // Horizontal addition (pairwise sum) to compute dot products
    __m128 sum0 = _mm_hadd_ps(m0, m1);
    __m128 sum1 = _mm_hadd_ps(m2, m3);
    __m128 result = _mm_hadd_ps(sum0, sum1);

    // Store the 4 dot products into the result array
    _mm_storeu_ps(res, result);
}
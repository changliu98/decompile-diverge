void sse_dot4(float *v1, float *v2, float *result)
{
    __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;

    xmm0 = _mm_loadu((void*)v1);
    xmm1 = _mm_loadu((void*)v2);
    xmm2 = _mm_mul_ps(xmm0, xmm1);
    xmm3 = _mm_shuffle_ps(xmm2, xmm2, 0x55);
    xmm4 = _mm_add_ps(xmm2, xmm3);
    xmm5 = _mm_shuffle_ps(xmm4, xmm4, 0xAA);
    xmm6 = _mm_add_ps(xmm4, xmm5);
    _mm_store_ss(result, xmm6);
}
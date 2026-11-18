void dot_product(float *a, float *b, float *c)
{
    asm("movups (%0), %%xmm0\n"
        "movups (%1), %%xmm1\n"
        "movups (%2), %%xmm2\n"
        "movups (%3), %%xmm3\n"

        "mulps %%xmm4, %%xmm0\n"
        "mulps %%xmm5, %%xmm1\n"
        "mulps %%xmm6, %%xmm2\n"
        "mulps %%xmm7, %%xmm3\n"

        "movaps %%xmm0, %%xmm4\n"
        "unpcklps %%xmm1, %%xmm0\n"
        "unpckhps %%xmm1, %%xmm1\n"
        "movaps %%xmm2, %%xmm2\n"
        "unpcklps %%xmm3, %%xmm3\n"
        "unpckhps %%xmm3, %%xmm3\n"

        "addps %%xmm4, %%xmm0\n"
        "addps %%xmm2, %%xmm2\n"
        "movaps %%xmm0, %%xmm1\n"
        "shufps $0x44, %%xmm2, %%xmm0\n"
        "shufps $0xee, %%xmm2, %%xmm1\n"
        "addps %%xmm1, %%xmm0\n"
        "addps %%xmm3, %%xmm1\n"
        "movups %%xmm0, (%4)\n"
        :
        : "r" (c), "r" (a), "r" (b), "r" (c)
    );
}
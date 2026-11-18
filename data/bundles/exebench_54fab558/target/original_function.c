void sse_dot4(float* v1x4, float* v2x4, float* results) {
__asm__ volatile (

   "movups    (%0), %%xmm0                 \n"
   "movups  16(%0), %%xmm1                 \n"
   "movups  32(%0), %%xmm2                 \n"
   "movups  48(%0), %%xmm3                 \n"


   "movups    (%1), %%xmm4                 \n"
   "movups  16(%1), %%xmm5                 \n"
   "movups  32(%1), %%xmm6                 \n"
   "movups  48(%1), %%xmm7                 \n"


   "mulps   %%xmm4, %%xmm0                 \n"
   "mulps   %%xmm5, %%xmm1                 \n"
   "mulps   %%xmm6, %%xmm2                 \n"
   "mulps   %%xmm7, %%xmm3                 \n"



   "movaps   %%xmm0, %%xmm4                \n"
   "unpcklps %%xmm1, %%xmm0                \n"
   "unpckhps %%xmm1, %%xmm4                \n"
   "movaps   %%xmm2, %%xmm1                \n"
   "unpcklps %%xmm3, %%xmm2                \n"
   "unpckhps %%xmm3, %%xmm1                \n"
   "addps    %%xmm4, %%xmm0                \n"
   "addps    %%xmm1, %%xmm2                \n"

   "movaps   %%xmm0, %%xmm1                \n"
   "shufps   $0b01000100, %%xmm2, %%xmm0   \n"
   "shufps   $0b11101110, %%xmm2, %%xmm1   \n"
   "addps    %%xmm1, %%xmm0                \n"
   "movups   %%xmm0, (%2)                  \n"
   :
   : "r" (v1x4), "r" (v2x4), "r" (results)
   );
}
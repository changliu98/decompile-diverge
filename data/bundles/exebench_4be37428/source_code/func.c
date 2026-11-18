#include <assert.h>

void sseround(float vec[3]) {
 static unsigned char mask[16] = {
  0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF,
  0x00, 0x00, 0x00, 0x00
 };

 __asm__ volatile (
  "movaps (%0), %%xmm1 \n"
  "movups (%1), %%xmm0 \n"
  "movaps %%xmm0, %%xmm2 \n"
  "andps %%xmm1, %%xmm0 \n"
  "andnps %%xmm2, %%xmm1 \n"
  "cvtps2dq %%xmm0, %%xmm0 \n"
  "cvtdq2ps %%xmm0, %%xmm0 \n"
  "orps %%xmm1, %%xmm0 \n"
  "movups %%xmm0, (%1) \n"
  :
  : "r" (mask), "r" (vec)
  : "memory", "%xmm0", "%xmm1", "%xmm2"
 );
}

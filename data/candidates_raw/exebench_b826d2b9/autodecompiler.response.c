void helper_float_21_recursive(float *buf, int depth) {
  if (depth == 13) {
    for (int j = 0; j < 8192; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
          "vmovups (%4), %%ymm4\n"
          "vmovups (%5), %%ymm5\n"
          "vmovups (%6), %%ymm6\n"
          "vmovups (%7), %%ymm7\n"
          "vpermilps $160, %%ymm0, %%ymm8\n"
          "vpermilps $245, %%ymm0, %%ymm9\n"
          "vxorps %%ymm10, %%ymm10, %%ymm10\n"
          "vsubps %%ymm9, %%ymm10, %%ymm
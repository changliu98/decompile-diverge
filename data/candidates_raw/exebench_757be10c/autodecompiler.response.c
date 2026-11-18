void helper_float_19_recursive(float *buf, int depth) {
  if (depth == 13) {
    for (int j = 0; j < 8192; j += 64) {
      for (int k = 0; k < 8; k += 8) {
        __asm__ volatile (
          "vmovups (%0), %%ymm0\n"
          "vmovups (%1), %%ymm1\n"
          "vmovups (%2), %%ymm2\n"
          "vmovups (%3), %%ymm3\n"
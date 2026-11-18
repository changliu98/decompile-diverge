void computesizes(uint32_t *nums,uint32_t ntotal,uint32_t *narray,uint32_t *nhash) {
  uint32_t n,a,i;
  n = -1;
  a = nums[0];
  for (i=1; i<32; i++) {
    if (nums[i] < *narray && (1 << i) <= *narray) {
      if (nums[i] > 0 && a + nums[i] >= (1 << i)) {
        n = i;
        a += nums[i];
      }
    } else break;
  }
  *nhash = ntotal - a;
  *narray = (n == -1) ? 0 : (1 << n);
}
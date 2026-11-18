static void jpc_qmfb_split_colgrp(jpc_fix_t *blk, int ncomps, int stride,
                                  int rowgrp) {
  int ncomps1 = (ncomps + 1) >> 1;
  int i;
  jpc_fix_t *tmp;
  jpc_fix_t tmpbuf[4096];
  jpc_fix_t *tmp1 = tmpbuf;
  if (ncomps1 > 4096) {
    if (!(tmp1 = jas_alloc2(ncomps1, sizeof(jpc_fix_t)))) {
      abort();
    }
  }
  if (ncomps >= 2) {
    int ncomps1a = (ncomps + 1 - rowgrp) >> 1;
    int ncomps1b = ncomps - ncomps1a;
    int n = ncomps1b;
    jpc_fix_t *src;
    jpc_fix_t *dst;
    src = tmp1;
    dst = blk + (1 - rowgrp) * stride;
    while (n-- > 0) {
      int j;
      jpc_fix_t *src1;
      jpc_fix_t *dst1;
      src1 = src;
      dst1 = dst;
      for (j = 0; j < 16; ++j) {
        *src1 = *dst1;
        ++src1;
        ++dst1;
      }
      src += 16;
      dst += 2 * stride;
    }
    src = blk + (1 - rowgrp) * stride;
    dst = blk + (2 - rowgrp) * stride;
    n = ncomps1b;
    if (rowgrp) {
      --n;
    }
    while (n-- > 0) {
      int j;
      jpc_fix_t *src1;
      jpc_fix_t *dst1;
      src1 = src;
      dst1 = dst;
      for (j = 0; j < 16; ++j) {
        *src1 = *dst1;
        ++src1;
        ++dst1;
      }
      src += stride;
      dst += 2 * stride;
    }
    src = blk + ncomps1a * stride;
    dst = tmp1;
    n = ncomps1b;
    while (n-- > 0) {
      int j;
      jpc_fix_t *src1;
      jpc_fix_t *dst1;
      src1 = src;
      dst1 = dst;
      for (j = 0; j < 16; ++j) {
        *src1 = *dst1;
        ++src1;
        ++dst1;
      }
      src += stride;
      dst += 16;
    }
  }
  if (tmp1 != tmpbuf) {
    jas_free(tmp1);
  }
}
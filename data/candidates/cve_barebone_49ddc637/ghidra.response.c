void jpc_qmfb_split_colgrp(jpc_fix_t *a,int numrows,int stride,int parity)

{
  int iVar1;
  int iVar2;
  int hstartcol;
  int m;
  int i;
  int n;
  jpc_fix_t *dstptr2;
  jpc_fix_t *srcptr2;
  jpc_fix_t *dstptr;
  jpc_fix_t *srcptr;
  jpc_fix_t *buf;
  jpc_fix_t splitbuf [65536];
  int bufsize;
  int parity_local;
  int stride_local;
  int numrows_local;
  jpc_fix_t *a_local;
  
  iVar1 = numrows + 1 >> 1;
  buf = splitbuf;
  if ((0x1000 < iVar1) && (buf = jas_alloc2((long)iVar1,8), buf == (jpc_fix_t *)0x0)) {
                    /* WARNING: Subroutine does not return */
    abort();
  }
  if (1 < numrows) {
    iVar1 = (numrows + 1) - parity >> 1;
    iVar2 = numrows - iVar1;
    dstptr = buf;
    srcptr = a + (1 - parity) * stride;
    n = iVar2;
    while (0 < n) {
      dstptr2 = dstptr;
      srcptr2 = srcptr;
      for (i = 0; i < 0x10; i = i + 1) {
        *dstptr2 = *srcptr2;
        dstptr2 = dstptr2 + 1;
        srcptr2 = srcptr2 + 1;
      }
      dstptr = dstptr + 0x10;
      srcptr = srcptr + (stride << 1);
      n = n + -1;
    }
    dstptr = a + (1 - parity) * stride;
    srcptr = a + (2 - parity) * stride;
    n = (numrows - iVar2) - (uint)((parity != 0 ^ 0xffU) & 1);
    while (0 < n) {
      dstptr2 = dstptr;
      srcptr2 = srcptr;
      for (i = 0; i < 0x10; i = i + 1) {
        *dstptr2 = *srcptr2;
        dstptr2 = dstptr2 + 1;
        srcptr2 = srcptr2 + 1;
      }
      dstptr = dstptr + stride;
      srcptr = srcptr + (stride << 1);
      n = n + -1;
    }
    dstptr = a + iVar1 * stride;
    srcptr = buf;
    n = iVar2;
    while (0 < n) {
      dstptr2 = dstptr;
      srcptr2 = srcptr;
      for (i = 0; i < 0x10; i = i + 1) {
        *dstptr2 = *srcptr2;
        dstptr2 = dstptr2 + 1;
        srcptr2 = srcptr2 + 1;
      }
      dstptr = dstptr + stride;
      srcptr = srcptr + 0x10;
      n = n + -1;
    }
  }
  if (buf != splitbuf) {
    jas_free(buf);
  }
  return;
}
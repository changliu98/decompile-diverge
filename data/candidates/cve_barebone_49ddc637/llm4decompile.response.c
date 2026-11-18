void jpc_qmfb_split_colgrp(jpc_fix_t *a, int numrows, int stride, int parity)
{
 jpc_fix_t *buf;
 jpc_fix_t *dstptr;
 jpc_fix_t *srcptr;
 int bufsize;
 int i;
 int j;
 int n;
 int m;
 int hstartcol;
 int vstartrow;
 int vstartcol;
 jpc_fix_t splitbuf[16384];
 bufsize = (numrows + 1) >> 1;
 buf = splitbuf;
 if (bufsize > 4096) {
  buf = jas_alloc2(bufsize, sizeof(jpc_fix_t) * 8);
  if (!buf)
   abort();
 }
 if (numrows > 1) {
  vstartrow = (1 - parity);
  vstartcol = (numrows + 1 - parity) >> 1;
  hstartcol = numrows - vstartcol;
  dstptr = buf;
  srcptr = a + vstartrow * stride;
  for (i = hstartcol; i > 0; --i) {
   for (j = 0; j < 16; ++j)
    *dstptr++ = *srcptr++;
   srcptr += stride;
   srcptr += stride;
  }
  dstptr = a + vstartrow * stride;
  srcptr = a + (vstartrow + 1) * stride;
  for (i = numrows - hstartcol - (parity ? 0 : 1); i > 0; --i) {
   for (j = 0; j < 16; ++j)
    *dstptr++ = *srcptr++;
   dstptr += stride;
   srcptr += stride;
   srcptr += stride;
  }
  dstptr = a + vstartcol * stride;
  srcptr = buf;
  for (i = hstartcol; i > 0; --i) {
   for (j = 0; j < 16; ++j)
    *dstptr++ = *srcptr++;
   dstptr += stride;
  }
 }
 if (buf != splitbuf)
  jas_free(buf);
}
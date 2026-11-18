void __cdecl jpc_qmfb_split_colgrp(jpc_fix_t *a, int numrows, int stride, int parity)
{
  int hstartcol;
  int m;
  int n;
  int na;
  int nb;
  int i;
  jpc_fix_t *dstptr;
  jpc_fix_t *srcptr;
  jpc_fix_t *dstptra;
  jpc_fix_t *srcptra;
  jpc_fix_t *dstptrb;
  jpc_fix_t *srcptrb;
  jpc_fix_t *buf;
  jpc_fix_t splitbuf[65536];
  int bufsize;

  bufsize = (numrows + 1) >> 1;
  buf = splitbuf;
  if (bufsize > 4096)
  {
    buf = (jpc_fix_t *)jas_alloc2(bufsize, 8uLL);
    if (!buf)
      abort();
  }

  if (numrows >= 2)
  {
    hstartcol = (numrows + 1 - parity) >> 1;
    m = numrows - hstartcol;
    n = numrows - hstartcol;

    // Copy odd-indexed rows to buffer
    dstptr = buf;
    srcptr = &a[stride * (1 - parity)];
    while (n-- > 0)
    {
      for (i = 0; i < 16; ++i)
        *dstptr++ = *srcptr++;
      dstptr -= 16;
      srcptr -= 16;
      dstptr += 16;
      srcptr += 2 * stride;
    }

    // Shift even-indexed rows to the beginning
    dstptra = &a[stride * (1 - parity)];
    srcptra = &a[stride * (2 - parity)];
    na = (numrows - m - 1) >> 32; // Equivalent to (numrows - m - 1) < 0 ? -1 : 0
    while (na-- > 0)
    {
      for (i = 0; i < 16; ++i)
        *dstptra++ = *srcptra++;
      dstptra -= 16;
      srcptra -= 16;
      dstptra += stride;
      srcptra += 2 * stride;
    }

    // Copy buffer to the second half of the array
    dstptrb = &a[stride * hstartcol];
    srcptrb = buf;
    nb = m;
    while (nb-- > 0)
    {
      for (i = 0; i < 16; ++i)
        *dstptrb++ = *srcptrb++;
      dstptrb -= 16;
      srcptrb -= 16;
      dstptrb += stride;
      srcptrb += 16;
    }
  }

  if (buf != splitbuf)
    jas_free(buf);
}
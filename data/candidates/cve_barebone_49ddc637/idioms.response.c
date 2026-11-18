void jpc_qmfb_split_colgrp(jpc_fix_t *in, int numrows, int stride, int parity)
{
  int numrowsa; int stridea; int paritya;
  int bufsize;
  jpc_fix_t *inptr;
  jpc_fix_t *bufptr;
  jpc_fix_t *buf;
  jpc_fix_t *inptr1;
  jpc_fix_t *inptr2;
  jpc_fix_t *bufptr1;
  jpc_fix_t *bufptr2;
  int i; int j; int k;
  int hstartcol;
  int m; int n;
  bufsize = (numrows + 1) >> 1;
  buf = (jpc_fix_t *)splitbuf;
  if (bufsize > 4096)
  {
    buf = (jpc_fix_t *)get_mem(bufsize, sizeof(jpc_fix_t));
    if (buf == ((void *)0))
      out_of_memory();
  }
  if (numrows >= 2)
  {
    hstartcol = (numrows + 1 - parity) >> 1;
    m = numrows - hstartcol;
    n = numrows - hstartcol;
    bufptr = buf;
    inptr = in + (1 - parity)*stride;
    while (n-- > 0)
    {
      bufptr1 = bufptr;
      inptr1 = inptr;
      for (i = 0; i < 16; i++)
      {
        *bufptr1 = *inptr1;
        bufptr1++;
        inptr1++;
      }
      bufptr += 16;
      inptr += 2*stride;
    }
    inptr1 = in + (1 - parity)*stride;
    inptr2 = in + (2 - parity)*stride;
    numrowsa = numrows - m;
    while (numrowsa-- > 0)
    {
      bufptr1 = inptr1;
      inptr2 = inptr2;
      for (i = 0; i < 16; i++)
      {
        *bufptr1 = *inptr2;
        bufptr1++;
        inptr2++;
      }
      inptr1 += stride;
      inptr2 += 2*stride;
    }
    inptr1 = in + hstartcol*stride;
    inptr2 = buf;
    numrowsa = m;
    while (numrowsa-- > 0)
    {
      bufptr1 = inptr1;
      inptr2 = inptr2;
      for (i = 0; i < 16; i++)
      {
        *bufptr1 = *inptr2;
        bufptr1++;
        inptr2++;
      }
      inptr1 += stride;
      inptr2 += 16;
    }
  }
  if (buf != (jpc_fix_t *)splitbuf)
    free_mem(buf);
}
int ras_putdatastd(jas_stream_t *out,ras_hdr_t *hdr,jas_image_t *image,int numcmpts,int *cmpts)

{
  long lVar1;
  long lVar2;
  int iVar3;
  int iVar4;
  jas_matrix_t *pjVar5;
  uint local_e0;
  uint local_d0;
  uint local_c8;
  int local_b8;
  ulong local_b0;
  ulong local_a0;
  uint local_90;
  int i;
  jas_matrix_t *data [3];
  int v;
  int y;
  int x;
  int c;
  int nz;
  uint z;
  int pad;
  int rowsize;
  int *cmpts_local;
  int numcmpts_local;
  jas_image_t *image_local;
  ras_hdr_t *hdr_local;
  jas_stream_t *out_local;
  
  for (i = 0; i < numcmpts; i = i + 1) {
    pjVar5 = jas_matrix_create((int)image->bry_ - (int)image->tly_,
                               (int)image->brx_ - (int)image->tlx_);
    data[i] = pjVar5;
    if (data[i] == (jas_matrix_t *)0x0) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("data[i]","/work/harness.c",0xf6,
                    "int ras_putdatastd(jas_stream_t *, ras_hdr_t *, jas_image_t *, int, int *)");
    }
  }
  iVar3 = (int)((hdr->width * hdr->depth + 0xf) / 0x10 << 1);
  lVar1 = hdr->width;
  lVar2 = hdr->depth;
  hdr->length = hdr->height * (long)iVar3;
  y = 0;
  do {
    if (hdr->height <= (long)y) {
      for (i = 0; i < numcmpts; i = i + 1) {
        jas_matrix_destroy(data[i]);
      }
      return 0;
    }
    for (i = 0; i < numcmpts; i = i + 1) {
      iVar4 = jas_image_readcmpt(image,cmpts[i],0,(long)y,image->brx_ - image->tlx_,1,data[i]);
      if (iVar4 != 0) {
        return -1;
      }
    }
    z = 0;
    nz = 0;
    for (x = 0; (long)x < hdr->width; x = x + 1) {
      if ((hdr->depth == 0x18) || (hdr->depth == 0x20)) {
        if (data[0]->numrows_ == 1) {
          local_90 = (uint)(*data[0]->rows_)[x];
        }
        else {
          local_90 = (uint)*data[0]->rows_[x];
        }
        if (data[1]->numrows_ == 1) {
          local_a0 = (*data[1]->rows_)[x];
        }
        else {
          local_a0 = *data[1]->rows_[x];
        }
        if (data[2]->numrows_ == 1) {
          local_b0 = (*data[2]->rows_)[x];
        }
        else {
          local_b0 = *data[2]->rows_[x];
        }
        v = local_90 & 0xff | (uint)((local_a0 & 0xff) << 8) | (uint)((local_b0 & 0xff) << 0x10);
      }
      else {
        if (data[0]->numrows_ == 1) {
          local_b8 = (int)(*data[0]->rows_)[x];
        }
        else {
          local_b8 = (int)*data[0]->rows_[x];
        }
        v = local_b8;
      }
      if (hdr->depth == 0x20) {
        local_c8 = 0xffffffff;
      }
      else {
        local_c8 = (int)(1L << ((byte)hdr->depth & 0x3f)) - 1;
      }
      z = z << ((byte)hdr->depth & 0x1f) | v & local_c8;
      nz = nz + (int)hdr->depth;
      while (7 < nz) {
        iVar4 = jas_stream_putc(out,z >> ((char)nz - 8U & 0x1f) & 0xff);
        if (iVar4 == -1) {
          return -1;
        }
        nz = nz + -8;
        if (nz == 0x20) {
          local_d0 = 0xffffffff;
        }
        else {
          local_d0 = (int)(1L << ((byte)nz & 0x3f)) - 1;
        }
        z = z & local_d0;
      }
    }
    if (0 < nz) {
      if (nz == 0x20) {
        local_e0 = 0xffffffff;
      }
      else {
        local_e0 = (int)(1L << ((byte)nz & 0x3f)) - 1;
      }
      iVar4 = jas_stream_putc(out,z >> (8 - (byte)nz & 0x1f) & local_e0);
      if (iVar4 == -1) {
        return -1;
      }
    }
    if (((iVar3 - (int)((lVar1 * lVar2 + 7) / 8)) % 2 != 0) &&
       (iVar4 = jas_stream_putc(out,0), iVar4 == -1)) {
      return -1;
    }
    y = y + 1;
  } while( true );
}
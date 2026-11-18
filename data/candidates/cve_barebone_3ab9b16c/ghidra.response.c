void sycc420_to_rgb(opj_image_t *img)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  int offset_00;
  int upb_00;
  uint uVar4;
  OPJ_INT32 *__ptr;
  OPJ_INT32 *__ptr_00;
  OPJ_INT32 *__ptr_01;
  uint j;
  uint i;
  int upb;
  int offset;
  uint max;
  uint maxh;
  uint maxw;
  int *ny;
  int *cr;
  int *cb;
  int *y;
  int *nb;
  int *ng;
  int *nr;
  int *b;
  int *g;
  int *r;
  int *d2;
  int *d1;
  int *d0;
  opj_image_t *img_local;
  
  bVar3 = (byte)img->comps->prec;
  offset_00 = 1 << (bVar3 - 1 & 0x1f);
  upb_00 = (1 << (bVar3 & 0x1f)) + -1;
  uVar1 = img->comps->w;
  uVar2 = img->comps->h;
  uVar4 = uVar1 * uVar2;
  y = img->comps->data;
  cb = img->comps[1].data;
  cr = img->comps[2].data;
  __ptr = malloc((ulong)uVar4 << 2);
  __ptr_00 = malloc((ulong)uVar4 << 2);
  __ptr_01 = malloc((ulong)uVar4 << 2);
  if (((__ptr == (OPJ_INT32 *)0x0) || (__ptr_00 == (OPJ_INT32 *)0x0)) ||
     (__ptr_01 == (OPJ_INT32 *)0x0)) {
    if (__ptr != (OPJ_INT32 *)0x0) {
      free(__ptr);
    }
    if (__ptr_00 != (OPJ_INT32 *)0x0) {
      free(__ptr_00);
    }
    if (__ptr_01 != (OPJ_INT32 *)0x0) {
      free(__ptr_01);
    }
  }
  else {
    b = __ptr_01;
    g = __ptr_00;
    r = __ptr;
    for (i = 0; i < (uVar2 & 0xfffffffe); i = i + 2) {
      ny = y + uVar1;
      nr = r + uVar1;
      ng = g + uVar1;
      nb = b + uVar1;
      for (j = 0; j < (uVar1 & 0xfffffffe); j = j + 2) {
        sycc_to_rgb(offset_00,upb_00,*y,*cb,*cr,r,g,b);
        sycc_to_rgb(offset_00,upb_00,y[1],*cb,*cr,r + 1,g + 1,b + 1);
        y = y + 2;
        r = r + 2;
        g = g + 2;
        b = b + 2;
        sycc_to_rgb(offset_00,upb_00,*ny,*cb,*cr,nr,ng,nb);
        sycc_to_rgb(offset_00,upb_00,ny[1],*cb,*cr,nr + 1,ng + 1,nb + 1);
        ny = ny + 2;
        nr = nr + 2;
        ng = ng + 2;
        nb = nb + 2;
        cb = cb + 1;
        cr = cr + 1;
      }
      if (j < uVar1) {
        sycc_to_rgb(offset_00,upb_00,*y,*cb,*cr,r,g,b);
        y = y + 1;
        r = r + 1;
        g = g + 1;
        b = b + 1;
        sycc_to_rgb(offset_00,upb_00,*ny,*cb,*cr,nr,ng,nb);
        cb = cb + 1;
        cr = cr + 1;
      }
      y = y + uVar1;
      r = r + uVar1;
      g = g + uVar1;
      b = b + uVar1;
    }
    if (i < uVar2) {
      for (j = 0; j < (uVar1 & 0xfffffffe); j = j + 2) {
        sycc_to_rgb(offset_00,upb_00,*y,*cb,*cr,r,g,b);
        sycc_to_rgb(offset_00,upb_00,y[1],*cb,*cr,r + 1,g + 1,b + 1);
        y = y + 2;
        r = r + 2;
        g = g + 2;
        b = b + 2;
        cb = cb + 1;
        cr = cr + 1;
      }
      if (j < uVar1) {
        sycc_to_rgb(offset_00,upb_00,*y,*cb,*cr,r,g,b);
      }
    }
    free(img->comps->data);
    img->comps->data = __ptr;
    free(img->comps[1].data);
    img->comps[1].data = __ptr_00;
    free(img->comps[2].data);
    img->comps[2].data = __ptr_01;
    img->comps[1].w = uVar1;
    img->comps[1].h = uVar2;
    img->comps[2].w = uVar1;
    img->comps[2].h = uVar2;
    img->comps[1].dx = img->comps->dx;
    img->comps[2].dx = img->comps->dx;
    img->comps[1].dy = img->comps->dy;
    img->comps[2].dy = img->comps->dy;
  }
  return;
}